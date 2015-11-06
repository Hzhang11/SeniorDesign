#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize cube display on startup
    this->initializeOnStartup();
    ui->timerLabel->setFont(timerFont);
    application.setTimerLabel(ui->timerLabel);
}


MainWindow::~MainWindow()
{
    delete ui;
}

// Initialize initial cube display
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

// Reset cube display
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


// Initialize top face
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

// Initialize left face
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

// Initialize front face
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

// Initialize right face
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

// Initialize back face
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

// Initialize bottom face
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

// Scan button click, start the timer, and reset the cube display
void MainWindow::on_scanButton_clicked()
{
    qDebug("Scan Button Clicked, reset to default, start the timer");
    application.startTimer();
    this->resetCubeDisplay();
}

// Generate button click, clear position string text area, and end the timer
void MainWindow::on_generateButton_clicked()
{
    qDebug("Generate Solution Button Clicked, end the timer");
    //QString str = ui->textEdit->toPlainText();
    ui->colorText->clear();
    application.endTimer();
}

// Rotate button click, randomize the cube, and solve a preset cube with solution printed to position string text area
void MainWindow::on_rotateButton_clicked()
{
    qDebug("Rotate Button Clicked, set to random");
    this->test();
}

// Update labels on all faces
void MainWindow::updateLabels(int cubeData[6][9])
{
    this->updateTop(cubeData[UP]);
    this->updateLeft(cubeData[LEFT]);
    this->updateFront(cubeData[FRONT]);
    this->updateRight(cubeData[RIGHT]);
    this->updateBack(cubeData[BACK]);
    this->updateDown(cubeData[DOWN]);
}

// Update top face
void MainWindow::updateTop(int input[])
{
    int i = 0;
    foreach (QLabel *each, topLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// Update left face
void MainWindow::updateLeft(int input[])
{
    int i = 0;
    foreach (QLabel *each, leftLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// Update front face
void MainWindow::updateFront(int input[])
{
    int i = 0;
    foreach (QLabel *each, frontLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// Update right face
void MainWindow::updateRight(int input[])
{
    int i = 0;
    foreach (QLabel *each, rightLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// Update back face
void MainWindow::updateBack(int input[])
{
    int i = 0;
    foreach (QLabel *each, backLabelGroup)
        each->setPixmap(pixImages[input[i++]]);
}

// Update bottom face
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
    QString posStr, clcStr, solutionStr;
    int cubeData[6][3][3];
    // Randomize the cube
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
            cubeData[i][j][k] = rand()%6;
    // Convert cube model from 3D array to 2D array, cubeData is the input, cube is the output
    application.setModel(cubeData, cubeModel);
    // Update labels based on cube model
    this->updateLabels(cubeModel);
    // Get and display the color string corresponding to cube model
    string colorStr = application.getColorString();
    clcStr = QString::fromStdString(colorStr);
    ui->colorText->setText(clcStr);

    // Get the position string of the current cube model (most likely invalid), and convert to QString
    vector<string> positionStr = application.getCubeStringVector();
    for (int i = 0; i < positionStr.size(); ++i)
    {
        if (i > 0)
            posStr += " ";
        posStr += QString::fromStdString(positionStr[i]);
    }
    // Preset cube model for solver
    string scannedInput[] = {"RU","LF","RD","RF","FU","UL","BD","DF","RB","LB","BU","LD","LBD","URB","LUB","DRF","ULF","FLD","RDB","UFR"};
    // Solve the preset model and get solution string
    string out = application.solve(scannedInput);
    solutionStr = QString::fromStdString(out);
    // Display the solution
    ui->positionText->setText(solutionStr);
}

void MainWindow::test()
{
    QString posStr;
    QString colorInput = ui->colorText->toPlainText();
    string stdColor = colorInput.toStdString();
    ui->positionText->setText(colorInput);
    application.setModel(stdColor, cubeModel);
    vector<string> positionStr = application.getCubeStringVector();
    for (int i = 0; i < positionStr.size(); ++i)
    {
        if (i > 0)
            posStr += " ";
        posStr += QString::fromStdString(positionStr[i]);
    }
    ui->positionText->setText(posStr);
    string solution = application.solve(positionStr);
    QList<QByteArray> motorCmdList = motorOps.interpretSolution(QString::fromStdString(solution));
    for(int i = 0; i < motorCmdList.size(); i++) {
        motorOps->sendPacket(motorCmdList[i]);
    }
    //  qDebug << stdColor;
}
