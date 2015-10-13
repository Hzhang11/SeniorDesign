#include "modelprocessor.h"


//0 - white     U
//1 - red       L
//2 - green     B
//3 - yellow    D
//4 - orange    R
//5 - blue      F

ModelProcessor::ModelProcessor()
{
    colorToInt['w'] = 0;
    colorToInt['r'] = 1;
    colorToInt['g'] = 2;
    colorToInt['y'] = 3;
    colorToInt['o'] = 4;
    colorToInt['b'] = 5;
    colorToPosition['w'] = 'U';
    colorToPosition['r'] = 'L';
    colorToPosition['g'] = 'B';
    colorToPosition['y'] = 'D';
    colorToPosition['o'] = 'R';
    colorToPosition['b'] = 'F';
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
