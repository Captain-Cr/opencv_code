#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	高斯滤波：
	GaussianBlur(src, dst, ksize, sigmaX, sigmaY, borderType=BORDER_DEFAULT);
	getGaussianKernel(int ksize, double sigma, int ktype=CV_64F);   用于生成标准尺寸的高斯滤波器,要生成二维高斯滤波器需要调用两次getGaussianKernel()，将X方向的一维高斯滤波器和Y方向的一维高斯滤波器相乘，得到最终的二维高斯滤波器；

*/


int mainaff(int argc, char* argv[])
{
	Mat image = imread("D:\\图片\\1.jpg", 0);
	Mat gauss = imread("D:\\图片\\gauss.jpg");
	Mat salt = imread("D:\\图片\\salt.jpg");
	if (image.empty() || gauss.empty() || salt.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}


	Mat result;			// 存放不含噪声的滤波结果
	Mat result_gauss;
	Mat result_salt;

	// 调用GaussianBlur()
	GaussianBlur(image, result, Size(3, 3), 10, 20);
	GaussianBlur(gauss, result_gauss, Size(3, 3), 10, 20);
	GaussianBlur(salt, result_salt, Size(3, 3), 10, 20);

	// 显示
	imshow("image", result);
	imshow("gauss", result_gauss);
	imshow("salt", result_gauss);
	waitKey();

	Mat x, y;
	x = getGaussianKernel(3, -1, CV_64F);				// 用于生成指定尺寸的高斯滤波器，  滤波器尺寸和标准偏差存在的关系
	y = getGaussianKernel(3, -1, CV_64F);				// 返回的是ksize * 1的Mat类矩阵
	cout << x << "  " << y;
	Mat union_filter = x * y.t();							// 联合滤波器，等于X方向和Y方向上的滤波器相乘
	
	cout << union_filter << endl;

	return 0;


}