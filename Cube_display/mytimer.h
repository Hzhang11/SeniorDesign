#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QString>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    MyTimer();
    void setLabel(QLabel* label);
   // void start();
    void start();
    //int getElapsedTime();
    //void pause();
    void end();

signals:
    void timeChanged();

public slots:
    void updateTimeLabel();

private:
    QTimer tmr;
    QTime tm;
    QLabel* lbl;
    bool running;

};

#endif // MYTIMER_H
