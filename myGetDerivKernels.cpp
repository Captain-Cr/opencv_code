#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	getDerivKernels(OutputArray kx, OutputArray ky, dx, dy, ksize, normalize=false, ktype=CV_32F);
	其中， kx：行滤波器系数的输出矩阵，尺寸ksize*1, ky:列滤波器系数的输出矩阵。
	dx: X方向导数的阶次，     dy：Y方向导数的阶次
	ksize： 滤波器的大小，有FILTER_SCHARR, 1,3,5,7

	该函数可用于生成sobel算子和Scharr算子，默认生成CV_32F
*/


int mainAAF()
{
	Mat sobel_x1, sobel_y1, sobel_x2, sobel_y2, sobel_x3, sobel_y3;			// 存放分离的sobel算子
	Mat scharr_x, scharr_y;			// 存放分离的scharr算子
	Mat sobelX1, sobelX2, sobelX3, scharrX;		// 存放最终算子

	// 一阶x方向的sobel算子
	getDerivKernels(sobel_x1, sobel_y1, 1, 0, 3);
	sobel_x1 = sobel_x1.reshape(CV_8U, 1);
	cout << sobel_y1 << endl;
	sobelX1 = sobel_y1 * sobel_x1;			// 计算过滤器,  这里要注意是y * x 即（行 * 列）矩阵乘法

	// 二阶x方向的sobel算子
	getDerivKernels(sobel_x2, sobel_y2, 2, 0, 5);
	sobel_x2 = sobel_x2.reshape(CV_8U, 1);
	sobelX2 = sobel_y2 * sobel_x2;			// 计算过滤器

	// 三阶x方向的sobel算子
	getDerivKernels(sobel_x3, sobel_y3, 3, 0, 7);
	sobel_x3 = sobel_x3.reshape(CV_8U, 1);
	sobelX3 =  sobel_y3 * sobel_x3;			// 计算过滤器

	// X方向scharr算子
	getDerivKernels(scharr_x, scharr_y, 1, 0, FILTER_SCHARR);
	scharr_x = scharr_x.reshape(CV_8U, 1);
	scharrX = scharr_y * scharr_x;			// 计算过滤器

	// 输出结果
	cout << "x方向一阶sobel算子为：" << endl << sobelX1 << endl;
	cout << "x方向二阶sobel算子为：" << endl << sobelX2 << endl;
	cout << "x方向三阶sobel算子为：" << endl << sobelX3 << endl;

	cout << "X方向的scharr算子：" << endl << scharrX << endl;
	waitKey();
	return 0;





}