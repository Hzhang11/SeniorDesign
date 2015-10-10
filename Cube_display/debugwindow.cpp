#include "debugwindow.h"
#include "ui_debugwindow.h"
#include <iostream>
#include <time.h>

DebugWindow::DebugWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);
    this->initializeOnStartup();

}

DebugWindow::~DebugWindow()
{
    delete ui;
}


void DebugWindow::initializeOnStartup()
{
    pixImages[RED].load("red.png");
    pixImages[WHITE].load("white.png");
    pixImages[BLUE].load("blue.png");
    pixImages[ORANGE].load("orange.png");
    pixImages[YELLOW].load("yellow.png");
    pixImages[GREEN].load("green.png");
    // And other colors
    this->initializeTop();
    this->initializeFront();
    this->initializeLeft();
    this->initializeBack();
    this->initializeDown();
    this->initializeRight();
}

void DebugWindow::resetCubeDisplay()
{
    foreach (QLabel *each, topLabelGroup)
        each->setPixmap(pixImages[TOP]);
    foreach (QLabel *each, leftLabelGroup)
        each->setPixmap(pixImages[LEFT]);
    foreach (QLabel *each, frontLabelGroup)
        each->setPixmap(pixImages[FRONT]);
    foreach (QLabel *each, rightLabelGroup)
        each->setPixmap(pixImages[RIGHT]);
    foreach (QLabel *each, backLabelGroup)
        each->setPixmap(pixImages[BACK]);
    foreach (QLabel *each, downLabelGroup)
        each->setPixmap(pixImages[DOWN]);
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
        each->setPixmap(pixImages[TOP]);
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
        each->setPixmap(pixImages[LEFT]);
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
        each->setPixmap(pixImages[FRONT]);
}

void DebugWindow::initializeRight()
{
    rightLabelGroup.append(ui->cubie_right_1);
    rightLabelGroup.append(ui->cubie_right_2);
    rightLabelGroup.append(ui->cubie_right_3);
    rightLabelGroup.append(ui->cubie_right_4);
    rightLabelGroup.append(ui->cubie_right_5);
    rightLabelGroup.append(ui->cubie_right_6);
    rightLabelGroup.append(ui->cubie_right_7);
    rightLabelGroup.append(ui->cubie_right_8);
    rightLabelGroup.append(ui->cubie_right_9);
    foreach (QLabel *each, rightLabelGroup)
        each->setPixmap(pixImages[RIGHT]);

}

void DebugWindow::initializeBack()
{
    backLabelGroup.append(ui->cubie_back_1);
    backLabelGroup.append(ui->cubie_back_2);
    backLabelGroup.append(ui->cubie_back_3);
    backLabelGroup.append(ui->cubie_back_4);
    backLabelGroup.append(ui->cubie_back_5);
    backLabelGroup.append(ui->cubie_back_6);
    backLabelGroup.append(ui->cubie_back_7);
    backLabelGroup.append(ui->cubie_back_8);
    backLabelGroup.append(ui->cubie_back_9);
    foreach (QLabel *each, backLabelGroup)
        each->setPixmap(pixImages[BACK]);
}

void DebugWindow::initializeDown()
{
    downLabelGroup.append(ui->cubie_down_1);
    downLabelGroup.append(ui->cubie_down_2);
    downLabelGroup.append(ui->cubie_down_3);
    downLabelGroup.append(ui->cubie_down_4);
    downLabelGroup.append(ui->cubie_down_5);
    downLabelGroup.append(ui->cubie_down_6);
    downLabelGroup.append(ui->cubie_down_7);
    downLabelGroup.append(ui->cubie_down_8);
    downLabelGroup.append(ui->cubie_down_9);
    foreach (QLabel *each, downLabelGroup)
        each->setPixmap(pixImages[DOWN]);
}


void DebugWindow::on_scanButton_clicked()
{
    qDebug("Scan Button Clicked, reset to default");
    this->resetCubeDisplay();
}

void DebugWindow::on_generateButton_clicked()
{
    qDebug("Generate Solution Button Clicked, try to get original stuff");
    QString str = ui->textEdit->toPlainText();
}

void DebugWindow::on_rotateButton_clicked()
{
    qDebug("Rotate Button Clicked, set to random");
    this->randomize();
}

void DebugWindow::updateLabels(int cubeData[6][9])
{
    this->updateTop(cubeData[TOP]);
    this->updateLeft(cubeData[LEFT]);
    this->updateFront(cubeData[FRONT]);
    this->updateRight(cubeData[RIGHT]);
    this->updateBack(cubeData[BACK]);
    this->updateDown(cubeData[DOWN]);
}

void DebugWindow::updateTop(int input[])
{
    int i = 0;
    foreach (QLabel *each, topLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void DebugWindow::updateLeft(int input[])
{
    int i = 0;
    foreach (QLabel *each, leftLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void DebugWindow::updateFront(int input[])
{
    int i = 0;
    foreach (QLabel *each, frontLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void DebugWindow::updateRight(int input[])
{
    int i = 0;
    foreach (QLabel *each, rightLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void DebugWindow::updateBack(int input[])
{
    int i = 0;
    foreach (QLabel *each, backLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void DebugWindow::updateDown(int input[])
{
    int i = 0;
    foreach (QLabel *each, downLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// For internal testing only
void DebugWindow::randomize()
{
    srand (time(NULL));
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 9; j++)
            cubeData[i][j] = rand()%6;

    this->updateLabels(cubeData);

}
