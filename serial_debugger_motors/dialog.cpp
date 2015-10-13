#include "dialog.h"
#include "ui_dialog.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>

#include <QObject>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // set up object for accessing device & assume device is not present
    teensyPort = new QSerialPort;
    teensy_isAvaiable = false;
    teensy_portName = "";

    // enumerate through available serial ports, check if they have both vendor/product indentifiers
    // if so, check if vendor/product indentifiers match with the pre-specified teensy device
    // & report that the teensy is present
    foreach(const QSerialPortInfo &thisSerialPort, QSerialPortInfo::availablePorts()) {
        if(thisSerialPort.hasVendorIdentifier() && thisSerialPort.hasProductIdentifier())
            //qDebug() << "ven id" << thisSerialPort.vendorIdentifier();
            //qDebug() << "pro id" << thisSerialPort.productIdentifier();
            if(thisSerialPort.vendorIdentifier() == teensy_vendID && thisSerialPort.productIdentifier() == teensy_prodID) {
                teensy_portName = thisSerialPort.portName();
                teensy_isAvaiable = true;
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
    else QMessageBox::warning(this, "Port Error", "Can't find teensy device");
}

Dialog::~Dialog()
{
    // close serial communication with teensy when dialog window is closed
    if(teensyPort->isOpen())
        teensyPort->close();
    delete ui;
}

// takes byte array and displays its values to the GUI
void Dialog::displayPacket(QByteArray command)
{
    QString displayString;

    // <!> probably a better way to do this....
    for(int i = 0; i < command.size(); i++) {
        int val = (unsigned char)command[i];
        displayString.append(QString::number(val) + " ");
    }
    ui->lineEdit->setText(displayString);
}

// send packet to designed serial port
void Dialog::sendPacket(QByteArray packet)
{
    if(teensyPort->isWritable())
        teensyPort->write(packet);
    else
        qDebug() << "failed to write to teensy device";
}

/*
 * function constructs and returns the motor command packet for sending to the Teensy microcontroller
 * it operates under 3 modes, the packet structure is detailed below
 --- packet structure ------------------------
[start][packet size][op mode][payload][checksum]

 immediate & deferred motor commands - payload : [motor id][accel]*4bytes[velocity]*4bytes[step]*2bytes
 deferred execute motor commands - payload: [motor id]

 <!> immediate & deferred motor commands could be optimized to use less space
*/
QByteArray Dialog::buildPacket(char mode) {
    int packetSize = packetWrapperSize;

    QByteArray packet(3, 0x00);
    packet[0] = (byte)0x53; // set start byte, same as char 'S' or dec 83

    if(mode == 'd' || mode == 'i') {
        packetSize += stepperPayloadSize; //<!> fixed for intermediate commands, needs change

        packet[1] = (byte)packetSize;
        if(mode == 'i')
            packet[2] = (byte)'I';
        else
            packet[2] = (byte)'D';

        // pull values related to stepper config from spin boxes
        int stepperArgs[4] = {};
        stepperArgs[0] = ui->spinBoxStepper->value();
        stepperArgs[1] = ui->spinBoxAccel->value();
        stepperArgs[2] = ui->spinBoxVelo->value();
        stepperArgs[3] = ui->spinBoxPos->value();

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
    else if(mode == 'e') { // adjust packet for deferred execution mode
        packetSize += 1;
        packet[1] = (byte)packetSize;
        packet[2] = (byte)'E';
        packet[3] = (byte)ui->spinBoxStepper->value();
    }

    byte checksum = 0x00;
    // compute checksum for packet
    for(int i = 0; i < packetSize; i++) {
        checksum ^= packet[i];
    }
    packet.append(checksum);

    return packet;
}

void Dialog::readSerial()
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

    qDebug() << message;
}

void Dialog::on_pushButtonStepImm_clicked()
{
    QByteArray ba = buildPacket('i');
    displayPacket(ba);
    sendPacket(ba);
}

void Dialog::on_pushButtonStepDefer_clicked()
{
    QByteArray ba = buildPacket('d');
    displayPacket(ba);
    sendPacket(ba);
}

void Dialog::on_pushButtonExeDef_clicked()
{
    QByteArray ba = buildPacket('e');
    displayPacket(ba);
    sendPacket(ba);
}
