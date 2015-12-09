#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtWidgets>
#include <QObject>

#include "motorinterface.h"
#include "mainwindow.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setMotorOpInterface(MotorOpInterface *motorOpsIn);

private slots:
    void on_pushButtonStepImm_clicked();
    void on_pushButtonStepDefer_clicked();
    void on_pushButtonExeDef_clicked();
    void displayRead(QString in);
    void on_pushButtonInterSolution_clicked();
    void on_pushButtonSetParam_clicked();
    void on_pushButtonRandSol_clicked();
    void on_checkBoxBiDirectionalMode_toggled(bool checked);


private:
    Ui::Dialog *ui;
    MotorOpInterface *motorOps;
    // functions
    QList<int> fetchMotorControlArgs();
    QString QByteArrayToString(QByteArray inputArray);
};

#endif // DIALOG_H
