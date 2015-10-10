#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QTime>

class Timer : public QObject
{
    Q_OBJECT
public:
    Timer();
    void start();
    int getElapsedTime();
    void pause();
    void end();

signals:
    void updateTimer(int);

public slots:


private:
    QTimer *tmr;
};

#endif // TIMER_H
