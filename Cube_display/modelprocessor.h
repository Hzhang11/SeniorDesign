#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

#include <string>
#include <map>
#include "constants.h"


using namespace std;

class ModelProcessor
{

private:
    int cube[6][9];
    map<char, int> colorToInt;
    map<char, char> colorToPosition;
    string colorString;
    vector<string> positionString;
    string colorNum2ColorStr(int colorNum);

public:
    ModelProcessor();
    void setCubeArray(int cubeIn[6][3][3], int cubeOut[6][9]);
    void setColorString(string colorIn);
    vector<string> cubeToCubeString();
    string cubeToColorString();
    vector<string> colorToCubeString();

};

#endif // MODELPROCESSOR_H
