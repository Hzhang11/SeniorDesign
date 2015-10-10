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

    int applicableMoves[];
    int affectedCubies[][8];

public:
    FastSolver();
    vi applyMove ( int move, vi state );
    int inverse ( int move );
    vi id ( vi state );
    void solve (char *cubeInput );

public:

    int phase;
};

#endif // FASTSOLVER_H
