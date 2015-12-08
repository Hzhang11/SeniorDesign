#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //motorOps = new MotorOpInterface();
    // set connection for serial reads from motor op interface & display the data in UI as received packet
    //QObject::connect(motorOps, SIGNAL(readyRead(QString)), this, SLOT(displayRead(QString)));
}

// functions tied to Qt button events
void Dialog::on_pushButtonStepImm_clicked()
{
    QList<int> motorControlArgs;
    motorControlArgs << ui->spinBoxStepper->value();
    motorControlArgs << ui->spinBoxPos->value();

    QByteArray ba = motorOps->buildPacket('I', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
void Dialog::on_pushButtonStepDefer_clicked()
{
    QList<int> motorControlArgs;
    motorControlArgs << ui->spinBoxStepper->value();
    motorControlArgs << ui->spinBoxPos->value();

    QByteArray ba = motorOps->buildPacket('D', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
void Dialog::on_pushButtonExeDef_clicked()
{
    QList<int> motorControlArgs;
    QByteArray ba = motorOps->buildPacket('E', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
void Dialog::on_pushButtonSetParam_clicked()
{
    QList<int> motorControlArgs;
    motorControlArgs << ui->spinBoxAccel->value();
    motorControlArgs << ui->spinBoxVelo->value();

    QByteArray ba = motorOps->buildPacket('P', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
void Dialog::on_pushButtonInterSolution_clicked()
{
    QString solution = ui->lineEditSolution->text();
    QList<QByteArray> motorCmdList = motorOps->interpretSolution(solution);
    for(int i = 0; i < motorCmdList.size(); i++) {
        motorOps->sendPacket(motorCmdList[i]);
    }
}

// converts QByteArray of values into corresponding number characters
// each value is appended onto the resulting string with a space
QString Dialog::QByteArrayToString(QByteArray inputArray) {
    QString resultString;
    // <!> probably a better way to do this....
    for(int i = 0; i < inputArray.size(); i++) {
        int val = (unsigned char)inputArray[i];
        resultString.append(QString::number(val) + " ");
    }
    return resultString;
}

void Dialog::displayRead(QString input) {
    ui->lineEditReceived->setText(input);
    qDebug() << input;
}

Dialog::~Dialog() {
    // closes serial communication with Teensy when dialog window is closed
    motorOps->closeConnection();
    delete ui;
}

// sets motor operations interface object from parent to this dialog
void Dialog::setMotorOpInterface(MotorOpInterface *motorOpsIn) {
    motorOps = motorOpsIn;
}


