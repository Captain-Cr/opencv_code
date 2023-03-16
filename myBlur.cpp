#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	均值滤波：  cv::blur(src, dst, ksize, Point(-1,-1), borderType=BORDER_DEFAULT);
	方框滤波 ： cv::boxFilter(src, dst, ddepth, ksize, Point(-1, -1), normalize, borderType);		# ddepth: 输出图像的数据类型（深度）CV_8U， 当赋值为-1时，输出图像的数据类型自动选择
	方框滤波是均值滤波的一般形式，在均值滤波中，将滤波器所有像素值求和后的平均值作为滤波后结果；方框滤波也是求滤波器所有像素值的和，但是方框滤波可以选择不进行归一化，是将所有像素值的和作为滤波结果，而不是所有像素值的平均值。
	
	还提供了 cv::sqrBoxFilter(同boxFilter): 实现对滤波器内每个像素值的平方求和，之后根据输入参数选择是否进行归一化操作。




*/




int mainzaf()
{

	Mat gray = imread("D:\\图片\\1.jpg", 0);
	Mat image = imread("D:\\图片\\1.jpg");
	if (gray.empty() || image.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}

	// 添加高斯噪声
	RNG rng;
	Mat gauss;
	Mat gauss_noise = Mat::zeros(gray.rows, gray.cols, gray.type());;
	rng.fill(gauss_noise, RNG::NORMAL, 10, 30);			
	gauss = gray + gauss_noise;				// 添加高斯噪声
	imshow("gray", gray);
	imshow("gauss", gauss);


	// 添加椒盐噪声(仅对单通道）
	Mat salt;
	copyTo(gray, salt,Mat());
	for (int i = 0; i < 2000; i++)
	{
		// 随机确定位置
		int x = std::rand() % gray.rows;
		int y = std::rand() % gray.cols;
		int write_black = std::rand() % 2;
		
		if (write_black == 0)
		{
			salt.at<uchar>(x, y) = 255;
		}
		else
		{
			salt.at<uchar>(x, y) = 0;
		}
	}
	imshow("salt", salt);

	imwrite("D:\\图片\\gauss.jpg", gauss);
	imwrite("D:\\图片\\salt.jpg", salt);


	// 均值滤波
	Mat result, result_gauss, result_salt;			// 存放滤波后的图
	blur(gray, result, Size(5,5));
	blur(gauss, result_gauss, Size(5, 5));
	blur(salt, result_salt, Size(5, 5));

	imshow("灰度图滤波", gray);
	imshow("高斯噪声滤波", gauss);
	imshow("椒盐噪声滤波", result_salt);

	



	// 方框滤波
	// 验证方框滤波算法的数据矩阵
	float points[25] = { 1,2,3,4,5,
						6,7,8,9,10,
						11, 12, 13, 14,15,
						16, 17,18, 19, 20,
						21,22, 23, 24, 25 };
	Mat data(5, 5, CV_32FC1, points);
	// 将CV_8U类型转换成CV_32F类型
	Mat Lena_copy, Lena_32F;
	gray.copyTo(Lena_copy, Mat());
	Lena_copy.convertTo(Lena_32F, CV_32F, 1.0 / 255);
	Mat resultNorm, result2, dataSqrNorm, dataSqr, equalLena_32FSqr;
	// 方框滤波函数boxFilter() 和 sqrBoxFilter()
	boxFilter(Lena_copy, resultNorm, -1, Size(3, 3), Point(-1, -1), true);			// 进行归一化
	boxFilter(Lena_copy, result2, -1, Size(3, 3), Point(-1, -1), false);				// 不进行归一化
	sqrBoxFilter(data, dataSqrNorm, -1, Size(3, 3), Point(-1, -1), true, BORDER_CONSTANT);			// 进行归一化
	sqrBoxFilter(data, dataSqr, -1, Size(3, 3), Point(-1, -1), false, BORDER_CONSTANT);				// 不进行归一化
	sqrBoxFilter(Lena_32F, equalLena_32FSqr, -1, Size(3, 3), Point(-1, -1), true, BORDER_CONSTANT);
	// 显示处理结果
	imshow("resultNorm", resultNorm);
	imshow("result", result2);
	imshow("equalLena_32FSqr", equalLena_32FSqr);
	
	waitKey();
	return 0;
	
}