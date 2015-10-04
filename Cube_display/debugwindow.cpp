#include "debugwindow.h"
#include "ui_debugwindow.h"
#include <iostream>

DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);
    this->initializeLabels();

}

DebugWindow::~DebugWindow()
{
    delete ui;
}

void DebugWindow::on_leftButton_clicked()
{
    qDebug("Left Button Clicked, set Red, White, Blue");
}

void DebugWindow::on_centerButton_clicked()
{
    qDebug("Center Button Clicked, set White, Red, Blue");
}

void DebugWindow::on_rightButton_clicked()
{
    qDebug("Right Button Clicked, set Blue, Red, White");
}


void DebugWindow::on_solveButton_clicked()
{
    qDebug("Solve Button Clicked, try to get original stuff");
    QString str = ui->textEdit->toPlainText();
    std::cout << str.toStdString();
}

void DebugWindow::initializeLabels()
{
    pixTop.load("red.png");
    pixLeft.load("white.png");
    pixFront.load("blue.png");
    // And other colors
    this->initializeTop();
    this->initializeFront();
    this->initializeLeft();
}

void DebugWindow::initializeTop()
{
    topLabelGroup.append(ui->cubie_top_1);
    topLabelGroup.append(ui->cubie_top_2);
    topLabelGroup.append(ui->cubie_top_3);
    topLabelGroup.append(ui->cubie_top_4);
    topLabelGroup.append(ui->cubie_top_5);
    topLabelGroup.append(ui->cubie_top_6);
    topLabelGroup.append(ui->cubie_top_7);
    topLabelGroup.append(ui->cubie_top_8);
    topLabelGroup.append(ui->cubie_top_9);
    foreach (QLabel *each, topLabelGroup)
        each->setPixmap(pixTop);
}

void DebugWindow::initializeLeft()
{
    leftLabelGroup.append(ui->cubie_left_1);
    leftLabelGroup.append(ui->cubie_left_2);
    leftLabelGroup.append(ui->cubie_left_3);
    leftLabelGroup.append(ui->cubie_left_4);
    leftLabelGroup.append(ui->cubie_left_5);
    leftLabelGroup.append(ui->cubie_left_6);
    leftLabelGroup.append(ui->cubie_left_7);
    leftLabelGroup.append(ui->cubie_left_8);
    leftLabelGroup.append(ui->cubie_left_9);
    foreach (QLabel *each, leftLabelGroup)
        each->setPixmap(pixLeft);
}

void DebugWindow::initializeFront()
{
    frontLabelGroup.append(ui->cubie_front_1);
    frontLabelGroup.append(ui->cubie_front_2);
    frontLabelGroup.append(ui->cubie_front_3);
    frontLabelGroup.append(ui->cubie_front_4);
    frontLabelGroup.append(ui->cubie_front_5);
    frontLabelGroup.append(ui->cubie_front_6);
    frontLabelGroup.append(ui->cubie_front_7);
    frontLabelGroup.append(ui->cubie_front_8);
    frontLabelGroup.append(ui->cubie_front_9);
    foreach (QLabel *each, frontLabelGroup)
        each->setPixmap(pixFront);
}

void DebugWindow::initializeRight()
{

}

void DebugWindow::initializeBack()
{

}

void DebugWindow::initializeDown()
{

}
