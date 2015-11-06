#include "motorinterface.h"

MotorOpInterface::MotorOpInterface(QObject *parent) : QObject(parent)
{
    // set up serialport object for accessing device & assume device is not present
    teensyPort = new QSerialPort;
    teensy_isAvaiable = false;
    teensy_portName = "";

    QMessageBox* temp = new QMessageBox;

    // enumerate through available serial ports, check if they have both vendor/product indentifiers
    // if so, check if vendor/product indentifiers match with the pre-specified teensy device
    // & report that the device is present
    foreach(const QSerialPortInfo &thisSerialPort, QSerialPortInfo::availablePorts()) {
        if(thisSerialPort.hasVendorIdentifier() && thisSerialPort.hasProductIdentifier()) {
            qDebug() << "ven id:" << thisSerialPort.vendorIdentifier() << "- pro id:" << thisSerialPort.productIdentifier();;
            if(thisSerialPort.vendorIdentifier() == teensy_vendID && thisSerialPort.productIdentifier() == teensy_prodID) {
                qDebug() << "Teensy device found";
                teensy_portName = thisSerialPort.portName();
                teensy_isAvaiable = true;
            }
        }
    }

    // attempt to open communications to teensy serial port
    // <!> needs check in error checking
    if(teensy_isAvaiable) {
        try {
            teensyPort->setPortName(teensy_portName);
            teensyPort->open(QSerialPort::ReadWrite);
            teensyPort->setBaudRate(QSerialPort::Baud9600);
            teensyPort->setDataBits(QSerialPort::Data8);
            teensyPort->setParity(QSerialPort::NoParity);
            teensyPort->setStopBits(QSerialPort::OneStop);
            teensyPort->setFlowControl(QSerialPort::NoFlowControl);
            QObject::connect(teensyPort, SIGNAL(readyRead()), this, SLOT(readSerial()));
        }
        catch(std::exception &e){
            qDebug() << "An exception occurred. " << e.what();
        }
    }
    else
        QMessageBox::warning(temp, "Port Error", "Can't find prespecified Teensy device.");
}

/* constructs and returns the motor command packet for sending to the Teensy microcontroller
 * operates under 3 modes, the packet structure is detailed below
 --- packet structure ------------------------
[start][packet size][op mode][payload][checksum]
 immediate & deferred motor commands - payload : [motor id][accel]*4bytes[velocity]*4bytes[step]*2bytes
 deferred execute motor commands - payload: [motor id]

 <!> immediate & deferred motor commands could be optimized to use less space
*/
QByteArray MotorOpInterface::buildPacket(char mode, QList<int> motorControlArgs) {
    int packetSize = packetWrapperSize;

    QByteArray packet(3, 0x00);
    packet[0] = (byte)0x53; // set start byte, same as char 'S' or dec 83

    if(mode == 'D' || mode == 'I') {
        packetSize += stepperPayloadSize; //<!> fixed for intermediate commands, needs change

        packet[1] = (byte)packetSize;
        if(mode == 'I')
            packet[2] = (byte)'I';
        else
            packet[2] = (byte)'D';

        // pull values related to stepper config from spin boxes
        int stepperArgs[4] = {};
        stepperArgs[0] = motorControlArgs[0];
        stepperArgs[1] = motorControlArgs[1];
        stepperArgs[2] = motorControlArgs[2];
        stepperArgs[3] = motorControlArgs[3];

        // build payload of serial command, <!> optimize this later
        packet[3] = (byte)stepperArgs[0];
        packet[4] = (byte)(stepperArgs[1] >> 3*8);
        packet[5] = (byte)(stepperArgs[1] >> 2*8);
        packet[6] = (byte)(stepperArgs[1] >> 8);
        packet[7] = (byte)stepperArgs[1];
        packet[8] = (byte)(stepperArgs[2] >> 3*8);
        packet[9] = (byte)(stepperArgs[2] >> 2*8);
        packet[10] = (byte)(stepperArgs[2] >> 8);
        packet[11] = (byte)stepperArgs[2];
        if(stepperArgs[3] > 0)
            packet[12] = (byte)0;
        else
            packet[12] = (byte)1;
        packet[13] = (byte)abs(stepperArgs[3]);
    }
    else if(mode == 'E') { // adjust packet for deferred execution mode
        packetSize += 1;
        packet[1] = (byte)packetSize;
        packet[2] = (byte)'E';
        packet[3] = (byte)motorControlArgs[0];
    }

    // compute checksum for packet & append checksum value
    byte checksum = 0x00;
    for(int i = 0; i < packetSize; i++) {
        checksum ^= packet[i];
    }
    packet.append(checksum);
    return packet;
}

// determine motor parameters & create corresponding deferred/execude deferred motor commands
// from rotation steps in given solution string
// - deferred motor commands are given to rotation steps that can be issued simultaneously if they affect opposite faces
// - immediate motor commands are given to rotation steps that can't be issued simultaneously
QList<QByteArray> MotorOpInterface::interpretSolution(QString solution) {
    QList<int> motorControlArgs;
    QList<QByteArray> motorCmdList;

    // interate through rotation steps in solution string
    for(int i = 0; i < solution.size(); i += 2) {
        // pre-emptively checks next rotation step unless the current rotation step is the last in the solution
        if(i+2 < solution.size()) {
            // detects adjecent rotation steps & builds deferred commands from motor parameters
            if(isOppositePair(solution[i], solution[i+2])) {
                motorControlArgs = buildMotorArgs(solution[i].toLatin1(), solution[i+1].digitValue());
                motorCmdList.append(buildPacket('D', motorControlArgs));
                motorControlArgs = buildMotorArgs(solution[i+2].toLatin1(), solution[i+3].digitValue());
                motorCmdList.append(buildPacket('D', motorControlArgs));
                motorCmdList.append(buildPacket('E', motorControlArgs));
                qDebug() << i << ":" << solution[i] << "-" << i+2 << ":" << solution[i+2];
                i += 2; // adjust index to skip next already issued step due to opposite side detection
            }
            else { //
                motorControlArgs = buildMotorArgs(solution[i].toLatin1(), solution[i+1].digitValue());
                motorCmdList.append(buildPacket('I', motorControlArgs));
            }
        }
        else {
            motorControlArgs = buildMotorArgs(solution[i].toLatin1(), solution[i+1].digitValue());
            motorCmdList.append(buildPacket('I', motorControlArgs));
        }
    }
    return motorCmdList;
}

// determines if side indicators are representing opposite sides of the cube
// returns true if they are representing opposite pairs, else false
bool MotorOpInterface::isOppositePair(QChar a, QChar b) {
    // add each set of side indicators ordered in correlation to representing opposite pairs (by index)
    // (e.g. U is opposite to D, L is opposite to R, etc.)
    QList<QString> facesSets; facesSets << "ULF" << "DRB";
    int setSize = 3, i;
    // interate & check through each face set if given side indicators are representing opposite pairs
    for(i = 0; i < setSize; i++) {
        if((a == facesSets[0][i] && b == facesSets[1][i]) || (a == facesSets[1][i] && b == facesSets[0][i]))
            return true;
    }
    return false;
}

// construct & return motor parameters based on solution rotation format ([face][rotation])
// motors 1~6 are assigned to Upper, Lower, Front, Down, Right & Back rotations
// stepMode format:
//  - 1 = 90 degrees clockwise (50 steps)
//  - 2 = 180 degrees (either, 100 steps)
//  - 3 = 90 degrees counterclockwise (50 steps)
QList<int> MotorOpInterface::buildMotorArgs(char side, int stepMode) {
    QList<int> motorControlArgs;

    // assign sides to proper motor id
    if(side == 'U')
        motorControlArgs << 1;
    else if(side == 'L')
        motorControlArgs << 2;
    else if(side == 'F')
        motorControlArgs << 3;
    else if(side == 'D')
        motorControlArgs << 4;
    else if(side == 'R')
        motorControlArgs << 5;
    else
        motorControlArgs << 6;

    motorControlArgs << (int) stdAccel;
    motorControlArgs << (int) stdMaxVel;

    // assign steps based on rotation mode
    if(stepMode == 1)
        motorControlArgs << 50;
    else if(stepMode == 2)
        motorControlArgs << 100;
    else
        motorControlArgs << -50;

    return motorControlArgs;
}

// reads entire message sent from the Teensy device & converts message to displayable string whenever a message is received
void MotorOpInterface::readSerial()
{
    QByteArray serialData = teensyPort->readAll();
    QString message = "";
    int val;

    for(int i = 0; i < serialData.size(); i++) {
        val = (unsigned char)serialData[i];
        message.append(QString::number(val) + " ");
    }
    // for reading byte messages and interpeting as coherent string
    //message = QString::fromStdString(serialData.toStdString());
    //feedbackBuffer += message;
    emit readyRead(message);
}

// send packet to designated port of Teensy device
void MotorOpInterface::sendPacket(QByteArray packet)
{
    if(teensyPort->isWritable())
        teensyPort->write(packet);
    else
        qDebug() << "failed to write to Teensy device";
}

// closes serial communication with Teensy if connection is present
void MotorOpInterface::closeConnection() {
    if(teensyPort->isOpen())
        teensyPort->close();
}
