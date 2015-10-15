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
    string cubeString, colorString;
    string colorNum2ColorStr(int colorNum);

public:
    ModelProcessor();
    void setCubeArray(int cubeIn[6][3][3]);
    void setColorString(string colorIn);
    string cubeToCubeString();
    string cubeToColorString();
    int* colorStringToCube();


// ----------------------------
public:
    void setCube(int cubeIn[6][9]);

};

#endif // MODELPROCESSOR_H
