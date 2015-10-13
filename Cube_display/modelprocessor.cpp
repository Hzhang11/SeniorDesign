#include "modelprocessor.h"


//0 - white     U
//1 - red       L
//2 - green     B
//3 - yellow    D
//4 - orange    R
//5 - blue      F

ModelProcessor::ModelProcessor()
{
    intColor[0] = 'U';
    intColor[1] = 'L';
    intColor[2] = 'B';
    intColor[3] = 'D';
    intColor[4] = 'R';
    intColor[5] = 'F';
}

void ModelProcessor::setCubeArray(int cubeIn[6][3][3])
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 9; j++)
            cube[i][j] = cubeIn[i][j/3][j%3];
}


void ModelProcessor::setColorString(string colorIn)
{
    colorString = colorIn;
}

string ModelProcessor::cubeToColorString()
{
    string tempColor;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 9; j++)
            tempColor += intColor[];
}

string ModelProcessor::cubeToCubeString()
{

}

int* ModelProcessor::colorStringToCube()
{

}
