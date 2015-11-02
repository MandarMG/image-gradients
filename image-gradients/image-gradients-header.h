#ifndef image_gradients_H
#define image_gradients_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class image_gradients
{
public:
	image_gradients::image_gradients();
	Mat readImg;
	Mat grayImg;
	Mat_<float> grad; 
	Mat_<float> grad2;
	Mat_<double> kern;// = Mat_<double>(3,1) << (-1.0, 0.0, 1.0);
	//kern(1,0) = -1.0;
	//kern(2,0) = 0.0;
	//kern(3,0) = 1.0; ///kernel definition for Filter2D
	Mat negaGrad;
	Mat posGrad;

private:

};

image_gradients::image_gradients()
{
	///constructor
	readImg = imread("test.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if(!readImg.data) {cout << "Error: Image cannot be loaded!" << endl; system("Pause");}
	grayImg = Mat::zeros(readImg.size(), CV_8U);
	//cvtColor(readImg, grayImg, CV_BGR2GRAY);
	GaussianBlur(readImg, grayImg, Size(3,3), 0,0, BORDER_DEFAULT);
	kern = (Mat_<double>(3,1) << -1, 0,  1);
	grad = Mat_<float>(grayImg.size(), CV_32FC1);
	grad2 = Mat_<float>(grayImg.size(), CV_32FC1);

	posGrad = Mat::zeros(grad.size(), CV_8U);
	negaGrad = Mat::zeros(grad.size(), CV_8U);
	namedWindow("gray image", CV_WINDOW_AUTOSIZE);
	imshow("gray image", grayImg);
}

#endif