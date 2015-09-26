#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cv::Mat test_image = cv::imread("lena.jpg");

    if(!test_image.data)
    {

        QMessageBox msg;
        msg.setText("Couldn't load image");
        msg.exec();

    }

    cv::namedWindow("test image", cv::WINDOW_AUTOSIZE);
    cv::imshow("test image", test_image);
}
