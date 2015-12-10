#ifndef VISION_H
#define VISION_H
#include "opencv2/highgui/highgui.hpp"


using namespace cv;

class Vision
{
public:
    Vision();
    double normSqr(double x1, double y1, double z1, double x2, double y2, double z2);
    int assign_color(Mat image, int x, int y);
    void get_array(int faces[6][9]);


};

#endif // VISION_H
