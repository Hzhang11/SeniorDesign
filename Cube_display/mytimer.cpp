#include "mytimer.h"

MyTimer::MyTimer()
{

}

void MyTimer::setLabel(QLabel *label)
{
    lbl = label;
}

// Start timer, if already running, do nothing
void MyTimer::start()
{
    if (!running) {
        tm.start();
        connect(&tmr, SIGNAL(timeout()), this, SLOT(updateTimeLabel()));
        tmr.start(1);
        running = true;
    }
}

// Update label
void MyTimer::updateTimeLabel()
{
    double elapsed = tm.elapsed()/1000.0;
    lbl->setNum(elapsed);
}

// End timer, if not running, clear timer
void MyTimer::end()
{
    if (running) {
        tmr.stop();
        running = false;
    }
    else
        lbl->setNum(0.000);
}
