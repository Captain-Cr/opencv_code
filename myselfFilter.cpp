#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	自定义滤波器： 只需根据需求定义一个卷积模板（滤波器），就可以实现自定义滤波，使用filter2D（）函数；
	可分离性：指的是先对X(Y)方向滤波， 再对Y(X)方向滤波的结果与两个方向的滤波器联合后的整体滤波相同。两个方向滤波器的联合就是将两个方向的滤波器相乘，得到一个矩形滤波器；
	联合滤波：假设X方向的滤波器为x=[x1,x2,x3], Y方向的滤波器为y=[y1, y2, y3]，则联合滤波为xy = ([y1, y2, y3].t()) * [x1, x2, x3]
	
	在高斯滤波中： getGaussianKernrel(ksize，sigma,ktype)函数分别得到X方向和Y方向的滤波器，如在x方向的kernel为2,则ksize_x=2;  y方向的kerenl为3，则ksize_y=3;

	输入两个方向滤波器实现滤波函数sepFilter2D(src, dst, ddepth, kernelx, kernely, Point(-1, -1), delta, borderType); 该函数将可分离的线性滤波器分离成X方向和Y方向进行处理
	和filter2D()函数不同，filter2D（）需要通过滤波器的尺寸区分操作是在x方向还是y方向；如滤波器大小为K*1时是Y方向， 1*K是X方向；
*/

int mainafzz()
{
	float points[25] = { 1,2,3,4,5,
					  6, 7, 8, 9, 10,
					  11, 12, 13, 14, 15,
					  16, 17, 18, 19, 20,
					  21, 22, 23, 24,25 };
	Mat data(5, 5, CV_32FC1, points);

	// x方向，y方向和联合滤波器的构建
	Mat a = (Mat_<float>(3, 1) << -1, -3, -1);			// y方向滤波器
	Mat b = a.reshape(1, 1);							// 可以改变矩阵的通道数，又可以对矩阵元素进行序列化. cn表示通道数，设为0表示通道数不变，否则变为设置的通道数； rows表示行数，设为0,不变，否则变为设置的行数
	Mat ab = a * b;										// 联合滤波器

	// 验证高斯滤波的可分离性
	Mat gaussian_x = getGaussianKernel(3, 1);				// 返回的是一个ksize * 1的Mat类型
	Mat gaussData, gaussData_XY;
	GaussianBlur(data, gaussData, Size(3, 3), 1, 1, BORDER_CONSTANT);
	sepFilter2D(data, gaussData_XY, -1, gaussian_x, gaussian_x, Point(-1, -1), 0, BORDER_CONSTANT);			// 分离滤波

	// 输出两种高斯滤波的计算结果
	cout << "gaussData= " << endl
		<< gaussData << endl;
	cout << "gaussianDataXY= " << endl
		<< gaussData_XY << endl;

	// 线性滤波的可分离性
	Mat dataYX, dataY, dataXY, dataXY_sep;
	filter2D(data, dataY, -1, a, Point(-1, -1), 0, BORDER_CONSTANT);		// 1 (1)、先对x方向滤波
	filter2D(dataY, dataYX, -1, b, Point(-1, -1), 0, BORDER_CONSTANT);		// 1 (2)、再对y方向滤波
	filter2D(data, dataXY, -1, ab, Point(-1, -1), 0, BORDER_CONSTANT);		// 2 联合滤波
	sepFilter2D(data, dataXY_sep, -1, b, b, Point(-1, -1), 0, BORDER_CONSTANT);		// 分离滤波
	// 输出可分离滤波和联合滤波的计算结果
	cout << "dataY = " << endl
		<<dataY << endl;
	cout << "dataYX = " << endl
		<< dataXY << endl;
	cout << "dataXY = " << endl
		<< dataXY << endl;
	cout << "dataXY_sep = " << endl
		<< dataXY_sep;


	// 对图像的分离操作
	Mat img = imread("D:\\图片\\1.jpg", 0);
	if (img.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}
	Mat imgYX, imgY, imgXY, img_sep;
	filter2D(img, imgY, -1, a, Point(-1, -1), 0, BORDER_CONSTANT);			// 1 （1）先对x方向滤波
	filter2D(imgY, imgYX, -1, b, Point(-1, -1), 0, BORDER_CONSTANT);		// 1  (2) 再对y方向滤波
	filter2D(img, imgXY, -1, ab, Point(-1, -1), 0, BORDER_CONSTANT);		// 2 联合滤波
	sepFilter2D(img, img_sep, -1, b, b, Point(-1, -1), 0, BORDER_CONSTANT);		// 分离滤波
	imshow("img", img);
	imshow("imgY", imgY);
	imshow("imgYX", imgYX);
	imshow("imgXY", imgXY);
	waitKey();
	return 0;



}