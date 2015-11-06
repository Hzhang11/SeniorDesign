#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include <vector>
#include <string>
#include <QLabel>
#include <QString>
#include "mytimer.h"
#include "modelprocessor.h"
#include "fastsolver.h"


using namespace std;

class AppInterface
{
public:
    AppInterface();
    AppInterface(QLabel* label);
    void setTimerLabel(QLabel* label);
    void startTimer();
    void endTimer();
    string solve(vector<string> input);
    string solve(string input[20]);
    void setModel(string colorString, int cubeOutput[6][9]);
    void setModel(int cubeInput[6][3][3], int cubeOutput[6][9]);
    string getColorString();
    vector<string> getCubeStringVector();

private:
    MyTimer timer;
    ModelProcessor processor;
    FastSolver solver;


};

#endif // APPINTERFACE_H
