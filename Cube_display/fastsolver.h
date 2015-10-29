#ifndef FASTSOLVER_H
#define FASTSOLVER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<int> vi;


class FastSolver
{

private:
    int affectedCubies[6][8] = {
      {  0,  1,  2,  3,  0,  1,  2,  3 },   // U
      {  4,  7,  6,  5,  4,  5,  6,  7 },   // D
      {  0,  9,  4,  8,  0,  3,  5,  4 },   // F
      {  2, 10,  6, 11,  2,  1,  7,  6 },   // B
      {  3, 11,  7,  9,  3,  2,  6,  5 },   // L
      {  1,  8,  5, 10,  1,  0,  4,  7 },   // R
    };
    int applicableMoves[5] = { 0, 262143, 259263, 74943, 74898 };
    int phase;

public:
    FastSolver();
    vi applyMove ( int move, vi state );
    int inverse ( int move );
    vi id ( vi state );
    string solve(string cubeInput[]);

};

#endif // FASTSOLVER_H
