#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

// debug window dialog constructor
Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
}
// debug window dialog destructor
Dialog::~Dialog() {
    delete ui;
}

//------------------ functions tied to Qt button events ------------------
// builds & sends immediate step command to Teensy device
void Dialog::on_pushButtonStepImm_clicked()
{
    QList<int> motorControlArgs;
    motorControlArgs << ui->spinBoxStepper->value();
    motorControlArgs << ui->spinBoxPos->value();

    QByteArray ba = motorOps->buildPacket('I', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
// builds & sends deferred step command to Teensy device
void Dialog::on_pushButtonStepDefer_clicked()
{
    QList<int> motorControlArgs;
    motorControlArgs << ui->spinBoxStepper->value();
    motorControlArgs << ui->spinBoxPos->value();

    QByteArray ba = motorOps->buildPacket('D', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
// builds & sends deferred execution command to Teensy device
void Dialog::on_pushButtonExeDef_clicked()
{
    QList<int> motorControlArgs;
    QByteArray ba = motorOps->buildPacket('E', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
// builds & sends motor paramters to Teensy device
void Dialog::on_pushButtonSetParam_clicked()
{
    QList<int> motorControlArgs;
    motorControlArgs << ui->spinBoxAccel->value();
    motorControlArgs << ui->spinBoxVelo->value();

    QByteArray ba = motorOps->buildPacket('P', motorControlArgs);
    ui->lineEdit->setText(QByteArrayToString(ba));
    motorOps->sendPacket(ba);
}
// decodes solution sequence, builds and sends corresponding control packets to Teensy device
void Dialog::on_pushButtonInterSolution_clicked()
{
    QString solution = ui->lineEditSolution->text();
    QList<QByteArray> motorCmdList = motorOps->interpretSolution(solution);
    for(int i = 0; i < motorCmdList.size(); i++) {
        motorOps->sendPacket(motorCmdList[i]);
    }
}
// generates a random solution sequence based on the # of steps given, decodes values into face sides
void Dialog::on_pushButtonRandSol_clicked()
{
    int steps = ui->spinBoxRandSteps->value();
    QString solution = "";
    for(int i = 0; i < steps; i++) {
       solution.append(motorOps->encodeSides(qrand()%6+1));
       solution.append(QString::number(qrand()%3+1));
    }
    ui->lineEditSolution->setText(solution);
}
// toggles single direction motor driving mode
void Dialog::on_checkBoxBiDirectionalMode_toggled(bool checked)
{
    motorOps->toggleSingleSideOp();
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

// displays read packets to received text field
void Dialog::displayRead(QString input) {
    ui->lineEditReceived->setText(input);
    //qDebug() << input;
}

// sets motor operations interface object from parent to this dialog
void Dialog::setMotorOpInterface(MotorOpInterface *motorOpsIn) {
    motorOps = motorOpsIn;
    // set connection for serial reads from motor op interface & display the data in UI as received packet
    QObject::connect(motorOps, SIGNAL(readyRead(QString)), this, SLOT(displayRead(QString)));

    ui->spinBoxAccel->setValue(STDACCEL);
    ui->spinBoxVelo->setValue(STDMAXVEL);
}
