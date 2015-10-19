#ifndef CONSTANTS
#define CONSTANTS

#include <QFont>

//0 - white
//1 - red
//2 - green
//3 - yellow
//4 - orange
//5 - blue

const int WHITE= 0, UP = 0;
const int RED = 1, LEFT = 1;
const int GREEN = 2, BACK = 2;
const int YELLOW = 3, DOWN = 3;
const int ORANGE = 4, RIGHT = 4;
const int BLUE = 5, FRONT = 5;
const char intToColor[] = {'w', 'r', 'g', 'y', 'o', 'b'};
const int faceOrder[] = {UP, LEFT, FRONT, RIGHT, BACK, DOWN};
const int edges[] = {719, 528, 137, 310, 4625, 5034, 5243, 4816, 2330, 2114, 3932, 4112};
const int corners[] = {82027, 22936, 3809, 61118, 473326, 452417, 511544, 534235};
const QFont timerFont( "Arial", 28, QFont::Bold);


#endif // CONSTANTS

