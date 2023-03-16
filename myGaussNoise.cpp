#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	cv::RNG rng;
	rng.fill(mat, distType, a, b, bool saturateRange=false);
		mat: 用于存放随机数的矩阵，支持低于5通道的矩阵；
		distType： 随机数分布形式选择标志，(RNG::UNIFORM,0;   RNG::NORMAL,1)
		a： 该参数表示高斯分布的均值；
		b： 该参数表示高斯分布的标准差；
		saturateRange: 预饱和标志，仅用于均匀分布。
	
*/

int mainzzf()
{
	Mat gray = imread("D:\\图片\\1.jpg", 0);
	Mat image = imread("D:\\图片\\1.jpg");
	if (gray.empty() || image.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}

	imshow("gray", gray);
	imshow("img", image);

	// 生成与原始图像尺寸、数据类型和通道数相同的矩阵
	Mat lena_noise = Mat::zeros(image.rows, image.cols, image.type());
	Mat equalLena = Mat::zeros(gray.rows, gray.cols, gray.type());

	// 创建一个rng类
	RNG rng;
	rng.fill(lena_noise, RNG::NORMAL, 10, 20);		// 生成三通道的高斯分布随机数
	rng.fill(equalLena, RNG::NORMAL, 15, 30);		// 生成单通道的高斯分布随机数
	imshow("三通道高斯噪声", lena_noise);
	imshow("单通道高斯噪声", equalLena);		
	
	image = image + lena_noise;				// 在彩色图添加噪声
	gray = gray + equalLena;				// 在灰度图添加噪声
	imshow("彩色图添加高斯噪声", image);
	imshow("在灰度图添加高斯噪声", gray);
	imwrite("E:\\data\\gauss.jpg", image);
	waitKey();
	return 0;
	

}