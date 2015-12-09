#include "motorinterface.h"

MotorOpInterface::MotorOpInterface(QObject *parent) : QObject(parent)
{
    ;
}

void MotorOpInterface::connectToTeensy() {
    // set up serialport object for accessing device & assume device is not present
    teensyPort = new QSerialPort;
    teensy_isAvaiable = false;
    teensy_portName = "";

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

    QMessageBox* temp = new QMessageBox;
    // attempt to open communications to teensy serial port
    // <!> needs some more error checking
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
            qDebug() << "An exception occurred while attempting to open communicatinos with Teensy device." << e.what();
        }
    }
    else QMessageBox::warning(temp, "Port Error", "Can't find prespecified Teensy device.");
}

/* constructs and returns the motor command packet for sending to the Teensy microcontroller
 * operates under 4 modes, the packet structure is detailed below
 --- packet structure ------------------------
[start][packet size][op mode][payload][checksum]
 * -- functional purpose
 - parameter set: for setting motor parameters (acceleration, max velocity, step dir, steps) to all motors
 - immediate & deferred: for driving motors immediately or set for driving later (deferred)
 - deferred execute: for driving deferred motors
 - position reset: request all motors to rotate to home position
 - last command:
 * -- payload structure
 - parameter set: [accel]*3bytes[velocity]*3bytes[step dir][steps]*2bytes
 - immediate & deferred motor commands: [motor id]
 - deferred execute motor commands: []
 - position reset: []
 - last command: []
*/
QByteArray MotorOpInterface::buildPacket(char mode, QList<int> motorControlArgs) {
    int packetSize = packetWrapperSize;

    QByteArray packet(3, 0x00);
    packet[0] = (byte)'S'; // set start byte, same as 53H or dec 83

    if(mode == 'P') { // mode P: parameter set: [accel]*3bytes[velocity]*3bytes[step dir][steps]*2bytes
        packetSize += parameterPayloadSize;
        packet[1] = (byte)packetSize;
        packet[2] = (byte)'P';
        // pull values related to stepper config from received parameter list
        int stepperArgs[3] = {};
        stepperArgs[0] = motorControlArgs[0]; // acceleration
        stepperArgs[1] = motorControlArgs[1]; // max velocity

        // byte shift to set [accel] & [velocity] vals into corresponding bytes
        packet[3] = (byte)(stepperArgs[0] >> 2*8);
        packet[4] = (byte)(stepperArgs[0] >> 8);
        packet[5] = (byte)stepperArgs[0];
        packet[6] = (byte)(stepperArgs[1] >> 2*8);
        packet[7] = (byte)(stepperArgs[1] >> 8);
        packet[8] = (byte)stepperArgs[1];
    }
    else if(mode == 'R') { // mode R: position reset: []
        packet[1] = (byte)packetSize;
        packet[2] = (byte)'R';
    }
    else if(mode == 'D' || mode == 'I') { // mode I or D: immediate & deferred: [motor id]
        packetSize += 4;
        packet[1] = (byte)packetSize;
        if(mode == 'I')
            packet[2] = (byte)'I';
        else
            packet[2] = (byte)'D';

        packet[3] = motorControlArgs[0]; // set [motor id][step dir][steps]*2bytes
        if(motorControlArgs[1] > 0) // check sign of steps to set [step dir]
            packet[4] = 1;
        else
            packet[4] = 0;
        // byte shift to set [steps] vals into corresponding bytes
        packet[5] = (byte)(abs(motorControlArgs[1]) >> 8);
        packet[6] = (byte)abs(motorControlArgs[1]);
    }
    else if(mode == 'E') { // mode E: deferred execution mode: []
        packet[1] = (byte)packetSize;
        packet[2] = (byte)'E';
    }
    else if(mode == 'L') { // mode L: last command mode: []
        packet[1] = (byte)packetSize;
        packet[2] = (byte)'L';
    }

    // compute checksum for packet & append checksum value
    byte checksum = 0x00;
    for(int i = 0; i < packetSize; i++) {
        checksum ^= packet[i];
    }
    packet.append(checksum);
    return packet;
}

// returns built motor parameter packet based on given accelerataion & max velocity
QByteArray MotorOpInterface::setParameters(int accel, int maxVel) {
    QByteArray parameterCmd;
    QList<int> motorControlArgs;

    motorControlArgs << accel;
    motorControlArgs << maxVel;

    parameterCmd = buildPacket('P', motorControlArgs);
    return parameterCmd;
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
                motorControlArgs = decodeStep(solution[i], solution[i+1].digitValue());
                motorCmdList.append(buildPacket('D', motorControlArgs));
                motorControlArgs = decodeStep(solution[i+2], solution[i+3].digitValue());
                motorCmdList.append(buildPacket('D', motorControlArgs));
                motorCmdList.append(buildPacket('E', motorControlArgs));
                i += 2; // adjust index to skip next already issued step due to opposite side detection
            }
            else {
                motorControlArgs = decodeStep(solution[i], solution[i+1].digitValue());
                motorCmdList.append(buildPacket('I', motorControlArgs));
            }
        }
        else {
            motorControlArgs = decodeStep(solution[i], solution[i+1].digitValue());
            motorCmdList.append(buildPacket('I', motorControlArgs));
        }
    }
    motorCmdList.append(buildPacket('L', motorControlArgs));

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
//  - 3 = 90 degrees counterclockwise
QList<int> MotorOpInterface::decodeStep(QChar side, int stepMode) {
    QList<int> motorControlArgs;

    // assign motor ID based on side given
    if(side == 'U')
        motorControlArgs << sideVals::U;
    else if(side == 'L')
        motorControlArgs << sideVals::L;
    else if(side == 'F')
        motorControlArgs << sideVals::F;
    else if(side == 'R')
        motorControlArgs << sideVals::R;
    else if(side == 'B')
        motorControlArgs << sideVals::B;
    else
        motorControlArgs << sideVals::D;
    // assign steps based on rotation mode
    if(stepMode == 1)
        motorControlArgs << 50;
    else if(stepMode == 2)
        motorControlArgs << 100;
    else {
        if(singleDirectionOpMode) motorControlArgs << 150;
        else motorControlArgs << -50;
    }
    return motorControlArgs;
}

// assigns side indentification character based on the motor ID given
QChar MotorOpInterface::encodeSides(int val) {
    QChar side;
    if(val == sideVals::U)
        side = 'U';
    else if(val == sideVals::L)
        side = 'L';
    else if(val == sideVals::F)
        side = 'F';
    else if(val == sideVals::R)
        side = 'R';
    else if(val == sideVals::B)
        side = 'B';
    else
        side = 'D';
    return side;
}

// reads entire message sent from the Teensy device & converts message to displayable string whenever a message is received
void MotorOpInterface::readSerial()
{
    QByteArray serialData = teensyPort->readAll();
    QString message = "";
    int val, modeIndex = 2;

    for(int i = 0; i < serialData.size(); i++) {
        val = (unsigned char)serialData[i];
        if(i == modeIndex) {
            if(val == 'L')
                emit lastPacket();
            else if(val == 'M')
                emit stopPacket();
        }
        message.append(QString::number(val) + " ");
    }
    emit readyRead(message);
    qDebug() << message;
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

// toggles single direction motor driving flag
void MotorOpInterface::toggleSingleSideOp() {
    singleDirectionOpMode = !singleDirectionOpMode;
    //qDebug() << "direction mode: " << singleDirectionOpMode;
}


