#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Canny(src, dst, threshold1, threshold2, aperturesize=3, L2gradient=flase);
	其中： src: 输入图像，必须是CV_8U的单通道或三通道图像
		   aperturesize: sobel算子的直径

*/

int mainazg()
{
	Mat img = imread("D://图片//1.jpg",0);
	if (img.empty())
	{
		cout << "图像加载错误" << endl;
		return -1;
	}
	Mat resultHigh, resultLow, resultG;

	// 高阈值检测图像边缘
	Canny(img, resultHigh, 100, 200, 3);


	// 低阈值检测图像边缘
	Canny(img, resultLow, 20, 40, 3);

	// 高斯模糊后检测图像
	GaussianBlur(img, resultG, Size(3, 3), 5);
	Canny(resultG, resultG, 100, 200, 3);

	imshow("img", img);
	imshow("height", resultHigh);
	imshow("Low", resultLow);
	imshow("resultG", resultG);
	waitKey();

	return 0;



}