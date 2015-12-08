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
    ui->generateButton->setEnabled(false);
    ui->rotateButton->setEnabled(false);
    motorOps.connectToTeensy();
    QObject::connect(&motorOps, SIGNAL(lastPacket()), this, SLOT(endTimer()));
}

MainWindow::~MainWindow()
{
    delete ui;
    motorOps.closeConnection();
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

// Scan button click, start the timer, and run testScan funtion simulating
// vision input
void MainWindow::on_scanButton_clicked()
{
    qDebug("Scan Button Clicked, reset to default, start the timer");
   // application.startTimer();
    this->testScan();
    ui->generateButton->setEnabled(true);
    //this->resetCubeDisplay();
}

// Generate button click, end the timer, and run testSolve function
// simulating the solving process
void MainWindow::on_generateButton_clicked()
{
    qDebug("Generate Solution Button Clicked, end the timer");
    //QString str = ui->textEdit->toPlainText();
    this->testSolve();
    ui->rotateButton->setEnabled(true);
    //application.endTimer();
}

// Rotate button click, randomize the cube, and solve a preset cube with solution printed to position string text area
void MainWindow::on_rotateButton_clicked()
{
    qDebug("Rotate Button Clicked, set to random");
    application.startTimer();
    this->testRotate();
    //application.endTimer();
}

// Launches cube debug controls
void MainWindow::on_pushButtonLaunchDebugger_clicked()
{
    Dialog *debugWindow = new Dialog();
    debugWindow->show();

    debugWindow->setMotorOpInterface(&motorOps);
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

//%%%%%%%%%% For internal testing only %%%%%%%%%%%%%%%%%%%%%%%%%

// Test scan function for manual input cube data
// Input cube using color string, in the order of: TOP, LEFT, FRONT, RIGHT, BACK, DOWN
// Each face should be input from left to right, top to bottom, and maintain orientation of the cube

void MainWindow::testScan()
{
    QString colorInput = ui->colorText->toPlainText();
    string stdColor = colorInput.toStdString();
    //ui->positionText->setText(colorInput);
    application.setModel(stdColor, cubeModel);
    this->updateLabels(cubeModel);

    // Solve and interpret solutions
    // And send packets
//    string inputStr[] = {"BL", "UF UR UB DB DF DB FL FR UL BR DL", "BLU", "UFR", "URB", "FDR", "LDF", "FUL", "DBR", "BDL"};


    /*
    QList<QByteArray> motorCmdList = motorOps.interpretSolution(QString::fromStdString(solution));
    for(int i = 0; i < motorCmdList.size(); i++) {
        motorOps.sendPacket(motorCmdList[i]);
    }*/
    //  qDebug << stdColor;
}

// Simulating solve by
void MainWindow::testSolve()
{
    QString posStr;
    vector<string> positionStr = application.getCubeStringVector();
    for (int i = 0; i < positionStr.size(); ++i)
    {
        if (i > 0)
            posStr += " ";
        posStr += QString::fromStdString(positionStr[i]);
    }
    ui->colorText->setText(posStr);
    cubeSolution = application.solve(positionStr);
    ui->positionText->setText(QString::fromStdString(cubeSolution));
}

// set motor parameters, interpret solution & send motor commands
// <!> might want to move set motor parameters to initialization only
void MainWindow::testRotate()
{
    QByteArray parameterCmd = motorOps.setParameters(stdAccel, stdMaxVel);
    QList<QByteArray> motorCmdList = motorOps.interpretSolution(QString::fromStdString(cubeSolution));

    motorOps.sendPacket(parameterCmd);
    for(int i = 0; i < motorCmdList.size(); i++) {
        motorOps.sendPacket(motorCmdList[i]);
    }
    // application.endTimer();
}

void MainWindow::endTimer()
{
    application.endTimer();
}


