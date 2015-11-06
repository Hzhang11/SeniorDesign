#include "mainwindow.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <QApplication>


using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    {
        VideoCapture cap1(1);
        Mat save_img1;
        cap1 >> save_img1;
    //    namedWindow("Display Image1", CV_WINDOW_AUTOSIZE );
        imshow("Display Image1", save_img1);
    }

    {
        VideoCapture cap2(2);
        Mat save_img2;
        cap2 >> save_img2;
      //  namedWindow("Display Image2", CV_WINDOW_AUTOSIZE );
        imshow("Display Image2", save_img2);
    }

    {
        VideoCapture cap3(3);
        Mat save_img3;
        cap3 >> save_img3;
      //  namedWindow("Display Image3", CV_WINDOW_AUTOSIZE );
        imshow("Display Image3", save_img3);
    }

    {
        VideoCapture cap4(4);
        Mat save_img4;
        cap4 >> save_img4;
      //  namedWindow("Display Image4", CV_WINDOW_AUTOSIZE );
        imshow("Display Image4", save_img4);
    }


    return a.exec();
}
