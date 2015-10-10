#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include "constants.h"


namespace Ui {
class DebugWindow;
}

class DebugWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = 0);
    ~DebugWindow();

private slots:

    void on_generateButton_clicked();

    void on_scanButton_clicked();

    void on_rotateButton_clicked();

private:
    Ui::DebugWindow *ui;
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
    int cubeData[6][9];

    // For internal testing only
    void randomize();

};

#endif // DEBUGWINDOW_H
