#define round(dbl) dbl >= 0.0 ? (int)(dbl + 0.5) : ((dbl - (double)(int)dbl) <= -0.5 ? (int)dbl : (int)(dbl - 0.5)) ///round function

#include "image-gradients-header.h"

using namespace std;
using namespace cv;

int main(void)
{
	image_gradients iG;

	filter2D(iG.grayImg, iG.grad, CV_32FC1, iG.kern, Point(-1,-1), 0.0, BORDER_DEFAULT);  ////gradient in Y direction using custom filter
	iG.grad2 = iG.grad.clone();

	for(uint16_t i=0; i <(iG.grad.rows); i++)///i=0
	{
		for(uint16_t j=0; j<(iG.grad.cols); j++)///j=0
		{
			if(iG.grad(i,j) < 0){ iG.grad(i,j) = (float)0.0;} //positive gradient
		} 
	}
	convertScaleAbs(iG.grad, iG.posGrad);

	for(uint16_t i=0; i <(iG.grad2.rows); i++)///i=0
	{
		for(uint16_t j=0; j<(iG.grad2.cols); j++)///j=0
		{
			if(iG.grad2(i,j) > 0){ iG.grad2(i,j) = (float)0.0;} ///negative gradient
		} 
	}
	convertScaleAbs(iG.grad2, iG.negaGrad);

	cout << "Conversion complete!!!" << endl;
	cout << "Now displaying images!!!" << endl;

	////show positive gradient image in 8U data
	namedWindow("positive gradient image", CV_WINDOW_AUTOSIZE);
	imshow("positive gradient image", iG.posGrad);
	////show negative gradient image in 8U data
	namedWindow("negative gradient image", CV_WINDOW_AUTOSIZE);
	imshow("negative gradient image", iG.negaGrad);
	

	waitKey(0); //wait infinite time for a keypress
	destroyAllWindows(); //destroy all the windows
	return 0;
}