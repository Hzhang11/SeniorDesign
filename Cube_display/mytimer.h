#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include <QTime>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    MyTimer();
    void start();
    int getElapsedTime();
    //void pause();
    void end();

signals:
    void timeChanged();

public slots:

private:
    QTimer tmr;
    QTime tm;

};

#endif // MYTIMER_H
