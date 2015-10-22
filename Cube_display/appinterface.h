#ifndef APPINTERFACE_H
#define APPINTERFACE_H

#include <vector>
#include <string>

using namespace std;

class AppInterface
{
public:
    AppInterface();
    void startTimer();
    void endTimer();
    string solve(vector<string> input);
    void setModel(string colorString);
    void setModel(int cubeInput[6][3][3]);
    vector<string> getColorString();
    vector<string> getCubeString();




signals:

public slots:

private:

};

#endif // APPINTERFACE_H
