#ifndef MOTOROPINTERFACE_H
#define MOTOROPINTERFACE_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QtWidgets>

typedef unsigned char byte; // define equivalent indentifier 'byte' for linux platform

class MotorOpInterface : public QObject
{
    Q_OBJECT
public:
    explicit MotorOpInterface(QObject *parent = 0);
    QByteArray buildPacket(char mode, QList<int> motorControlArgs);
    void sendPacket(QByteArray packet);
    void closeConnection();
    QList<QByteArray> interpretSolution(QString solution);

private:
    // set variables to indentify serial port used to access teensy device
    QSerialPort *teensyPort;
    static const quint16 teensy_vendID = 5824;
    static const quint16 teensy_prodID = 1155;
    bool teensy_isAvaiable;
    QString teensy_portName;

    // packet size
    static const int stepperPayloadSize = 11;
    static const int packetWrapperSize = 4;
    // default motor accel & velocity parameters
    static const int stdAccel = 40000;
    static const int stdMaxVel = 2000;

    // functions
    QList<int> buildMotorArgs(char side, int stepMode);
    bool isOppositePair(QChar a, QChar b);
signals:
    void readyRead(QString message);

public slots:
    void readSerial();
};

#endif // MOTOROPINTERFACE_H
