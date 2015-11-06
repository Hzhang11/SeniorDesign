#include "appinterface.h"

AppInterface::AppInterface()
{

}

AppInterface::AppInterface(QLabel *label)
{
    this->setTimerLabel(label);
}

void AppInterface::setTimerLabel(QLabel *label)
{
    timer.setLabel(label);
}

void AppInterface::startTimer()
{
    timer.start();
}

void AppInterface::endTimer()
{
    timer.end();
}

string AppInterface::solve(string input[])
{
    return solver.solve(input);
}

string AppInterface::solve(vector<string> input)
{

    string tempInput[20];
    for(int i = 0; i < input.size(); i++)
        tempInput[i] = input[i];
    return solver.solve(tempInput);
}

void AppInterface::setModel(int cubeInput[6][3][3], int cubeOutput[6][9])
{
    processor.setCubeArray(cubeInput, cubeOutput);
}

void AppInterface::setModel(string colorString, int cubeOutput[6][9])
{
    processor.setColorString(colorString, cubeOutput);
}

string AppInterface::getColorString()
{
    return processor.getColorString();
}

vector<string> AppInterface::getCubeStringVector()
{
    return processor.getCubeString();
}

