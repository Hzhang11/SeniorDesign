#include "mytimer.h"

MyTimer::MyTimer()
{

}

void MyTimer::start()
{
    tm.start();
    connect(&tmr, SIGNAL(timeout()), this, SIGNAL(timeChanged()));
    tmr.start(1);
}


int MyTimer::getElapsedTime()
{
    return tm.elapsed()/10;
}

void MyTimer::end()
{
    tmr.stop();
}
