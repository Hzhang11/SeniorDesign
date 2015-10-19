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

// Set 2D cube array
void ModelProcessor::setCubeArray(int cubeIn[6][3][3], int cubeOut[6][9])
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 9; j++) {
            cube[i][j] = cubeIn[i][j/3][j%3];
            cubeOut[i][j] = cubeIn[i][j/3][j%3];
        }
}

// Set color string
void ModelProcessor::setColorString(string colorIn)
{
    colorString = colorIn;
}

// Convert cube array to color string
string ModelProcessor::cubeToColorString()
{
    string resultStr;
    for(int face: faceOrder)
        for(int j = 0; j < 9; j++)
            resultStr += intToColor[cube[face][j]];
    colorString = resultStr;
    return resultStr;
}

// Convert color string to cube string
vector<string> ModelProcessor::colorToCubeString()
{
    int edge1Index, edge2Index, corner1Index, corner2Index, corner3Index;

    vector<string> posString;
    for(int edge: edges) {
        string temp;
        edge1Index = edge/100;
        edge2Index = edge%100;
        temp += colorToPosition[colorString[edge1Index]];
        temp += colorToPosition[colorString[edge2Index]];
        posString.push_back(temp);
    }

    for(int corner: corners) {
        string temp;
        corner1Index = corner/10000;
        corner2Index = corner%10000/100;
        corner3Index = corner%10000%100;
        temp += colorToPosition[colorString[corner1Index]];
        temp += colorToPosition[colorString[corner2Index]];
        temp += colorToPosition[colorString[corner3Index]];
        posString.push_back(temp);
    }

    positionString = posString;
    return positionString;

}

// Convert cube array to cube string
vector<string> ModelProcessor::cubeToCubeString()
{
    vector<string> resultStr;
    this->cubeToColorString();
    resultStr = this->colorToCubeString();
    return resultStr;
}

