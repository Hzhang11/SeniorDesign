#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButtonStepImm_clicked();
    void sendPacket(QByteArray payload);
    void displayPacket(QByteArray command);
    void readSerial();
    QByteArray buildPacket(char mode);
    void on_pushButtonStepDefer_clicked();

    void on_pushButtonExeDef_clicked();

private:
    Ui::Dialog *ui;

    // set variables to indentify serial port used to access teensy device
    QSerialPort *teensyPort;
    static const quint16 teensy_vendID = 5824;
    static const quint16 teensy_prodID = 1155;
    QString teensy_portName;
    bool teensy_isAvaiable;

    QString feedbackBuffer = "";

    static const int stepperPayloadSize = 11;
    static const int packetWrapperSize = 4;
};

#endif // DIALOG_H
