#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include "constants.h"
#include "appinterface.h"
#include "motorinterface.h"
#include "dialog.h"
#include "vision.h"
#include <QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_generateButton_clicked();
    void on_scanButton_clicked();
    void on_rotateButton_clicked();
    void endTimer();
    void emergencyStopNotification();
    void on_pushButtonLaunchDebugger_clicked();

    void on_fixButton_clicked();

private:
    Ui::MainWindow *ui;

    AppInterface application;
    string cubeSolution;
    MotorOpInterface motorOps;
    Vision visionApp;
    QPixmap pixImages[6];
    QList<QLabel *> topLabelGroup, leftLabelGroup, frontLabelGroup, rightLabelGroup, backLabelGroup, downLabelGroup;
    void initializeOnStartup();
    void resetCubeDisplay();
    void initializeTop();
    void initializeLeft();
    void initializeFront();
    void initializeRight();
    void initializeBack();
    void initializeDown();
    void updateLabels(int cubeIn[6][9]);
    void updateTop(int top[9]);
    void updateLeft(int left[9]);
    void updateFront(int front[9]);
    void updateRight(int right[9]);
    void updateBack(int back[9]);
    void updateDown(int down[9]);
    // Cube model used to store cube data
    int cubeModel[6][9];

    // For internal testing only
    void testScan();
    void testSolve();
    void testRotate();
};

#endif // MAINWINDOW_H
