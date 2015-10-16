#include "mytimer.h"

MyTimer::MyTimer()
{

}

void MyTimer::setLabel(QLabel *label)
{
    lbl = label;
}

void MyTimer::start()
{
    tm.start();
    connect(&tmr, SIGNAL(timeout()), this, SLOT(updateTimeLabel()));
    tmr.start(1);
    running = true;
}

void MyTimer::updateTimeLabel()
{
    double elapsed = tm.elapsed()/1000.0;
    lbl->setNum(elapsed);
}

/*
int MyTimer::getElapsedTime()
{
    return tm.elapsed()/10;
}*/

void MyTimer::end()
{
    if (running) {
        tmr.stop();
        running = false;
    }
    else
        lbl->setNum(0.000);
}
