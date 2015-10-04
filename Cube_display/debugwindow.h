#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QString>


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

    void on_leftButton_clicked();

    void on_centerButton_clicked();

    void on_rightButton_clicked();

    void on_solveButton_clicked();

private:
    Ui::DebugWindow *ui;
    QPixmap pixTop, pixLeft, pixFront;
    QList<QLabel *> topLabelGroup, leftLabelGroup, frontLabelGroup, rightLabelGroup, backLabelGroup, bottomLabelGroup;
    void initializeLabels();
    void initializeTop();
    void initializeLeft();
    void initializeFront();
    void initializeRight();
    void initializeBack();
    void initializeDown();
    int testData[6][9];
};

#endif // DEBUGWINDOW_H
