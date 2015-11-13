#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QtWidgets>
#include <QObject>
#include "motorinterface.h"

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
    void on_pushButtonStepDefer_clicked();
    void on_pushButtonExeDef_clicked();
    void displayRead(QString in);
    void on_pushButtonInterSolution_clicked();

private:
    Ui::Dialog *ui;

    MotorOpInterface* motorOps;
    // functions
    QList<int> fetchMotorControlArgs();
    QString QByteArrayToString(QByteArray inArray);
};

#endif // DIALOG_H
