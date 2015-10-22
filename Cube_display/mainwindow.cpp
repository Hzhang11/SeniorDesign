#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initializeOnStartup();
    ui->timerLabel->setFont(timerFont);
    tmr.setLabel(ui->timerLabel);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeOnStartup()
{
    pixImages[RED].load("red.png");
    pixImages[WHITE].load("white.png");
    pixImages[BLUE].load("blue.png");
    pixImages[ORANGE].load("orange.png");
    pixImages[YELLOW].load("yellow.png");
    pixImages[GREEN].load("green.png");
    this->initializeTop();
    this->initializeFront();
    this->initializeLeft();
    this->initializeBack();
    this->initializeDown();
    this->initializeRight();
}


void MainWindow::resetCubeDisplay()
{
    foreach (QLabel *each, topLabelGroup)
        each->setPixmap(pixImages[UP]);
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



void MainWindow::initializeTop()
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
        each->setPixmap(pixImages[UP]);
}

void MainWindow::initializeLeft()
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

void MainWindow::initializeFront()
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

void MainWindow::initializeRight()
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

void MainWindow::initializeBack()
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

void MainWindow::initializeDown()
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


void MainWindow::on_scanButton_clicked()
{
    qDebug("Scan Button Clicked, reset to default, start the timer");
    tmr.start();
    this->resetCubeDisplay();
}

void MainWindow::on_generateButton_clicked()
{
    qDebug("Generate Solution Button Clicked, try to get original stuff, end the timer");
    //QString str = ui->textEdit->toPlainText();
    tmr.end();
}

void MainWindow::on_rotateButton_clicked()
{
    qDebug("Rotate Button Clicked, set to random");
    this->randomize();
}

void MainWindow::updateLabels(int cubeData[6][9])
{
    this->updateTop(cubeData[UP]);
    this->updateLeft(cubeData[LEFT]);
    this->updateFront(cubeData[FRONT]);
    this->updateRight(cubeData[RIGHT]);
    this->updateBack(cubeData[BACK]);
    this->updateDown(cubeData[DOWN]);
}

void MainWindow::updateTop(int input[])
{
    int i = 0;
    foreach (QLabel *each, topLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void MainWindow::updateLeft(int input[])
{
    int i = 0;
    foreach (QLabel *each, leftLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void MainWindow::updateFront(int input[])
{
    int i = 0;
    foreach (QLabel *each, frontLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void MainWindow::updateRight(int input[])
{
    int i = 0;
    foreach (QLabel *each, rightLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void MainWindow::updateBack(int input[])
{
    int i = 0;
    foreach (QLabel *each, backLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

void MainWindow::updateDown(int input[])
{
    int i = 0;
    foreach (QLabel *each, downLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// For internal testing only
void MainWindow::randomize()
{
    srand (time(NULL));
    int cubeData[6][3][3];
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
            cubeData[i][j][k] = rand()%6;
    processor.setCubeArray(cubeData, cube);
    this->updateLabels(cube);
    string colorStr = processor.cubeToColorString();
    vector<string> positionStr = processor.colorToCubeString();
    QString posStr, clcStr;
    for (int i = 0; i < positionStr.size(); ++i)
    {
        if (i > 0)
            posStr += " ";
        posStr += QString::fromStdString(positionStr[i]);
    }
    clcStr = QString::fromStdString(colorStr);
   // solver.solve();
    ui->positionText->setText(posStr);
    ui->colorText->setText(clcStr);
}
