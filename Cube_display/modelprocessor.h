#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

#include <string>

using namespace std;

class ModelProcessor
{

private:
    int cube[6][9];
    string cubeString;

public:
    ModelProcessor();
    ModelProcessor(int cubeIn[6][3][3]);
    string cubeToString();



};

#endif // MODELPROCESSOR_H
