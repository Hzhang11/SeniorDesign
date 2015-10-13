#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

#include <string>
#include <map>


using namespace std;

class ModelProcessor
{

private:
    int cube[6][9];
    map<int, char> intColor;
    map<char, char> colorPosition;
    string cubeString, colorString;
    string colorNum2ColorStr(int colorNum);

public:
    ModelProcessor();
    void setCubeArray(int cubeIn[6][3][3]);
    void setColorString(string colorIn);
    string cubeToCubeString();
    string cubeToColorString();
    int* colorStringToCube();




};

#endif // MODELPROCESSOR_H
