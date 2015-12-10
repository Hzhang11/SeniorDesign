#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include <vector>
#include <string>
#include <QLabel>
#include <QString>
#include "mytimer.h"
#include "modelprocessor.h"
#include "fastsolver.h"
#include "motorinterface.h"

using namespace std;

class AppInterface
{
public:
    // constructors
    AppInterface();
    AppInterface(QLabel* label);
    // public functions
    void setTimerLabel(QLabel* label);
    void startTimer();
    void endTimer();
    string solve(vector<string> input);
    string solve(string input[20]);
    void setModel(string colorString, int cubeOutput[6][9]);
    void setModel(int cubeInput[6][9], int cubeOutput[6][9]);
    string getColorString();
    vector<string> getCubeStringVector();
    // public

    MotorOpInterface getMotorOpInterface();


private:
    MyTimer timer;
    ModelProcessor processor;
    FastSolver solver;
    MotorOpInterface motorOps;
};

#endif // APPINTERFACE_H
