#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	利用随机函数生成椒盐噪声
	int cvflann::rand();
	double cvflann::rand_double(double high = 1.0,  double low =0);
	int cvflann::rand_int(int height = RAND_MAX, int low =0);

	生成0-100的整数， int a= rand() % 100
*/


//椒盐噪声函数
void saltAndPepper(Mat img, int n)
{
	// n是添加多少个点
	for (int k = 0; k < n / 2; k++)
	{
		// 随机确定图像中的位置
		int i, j;
		j = std::rand() % img.rows;		// 取余运算，保证在图像的行数内
		i = std::rand() % img.cols;
		int write_black = std::rand() % 2;			// 判断是白色噪声还是黑色噪声的变量
		if (write_black == 0)			// 添加白色噪声
		{
			if (img.type() == CV_8UC1)		// 处理灰度图像
			{
				img.at<uchar>(j, i) = 255;		//白色噪声
			}
		}
		else if (img.type() == CV_8UC3)
		{
			img.at<Vec3b>(j, i)[0] = saturate_cast<uchar>(rand() % 255);
			img.at<Vec3b>(j, i)[1] = saturate_cast<uchar>(rand() % 255);
			img.at<Vec3b>(j, i)[2] = saturate_cast<uchar>(rand() % 255);
		}
		else         // 添加黑色噪声
		{
			if (img.type() == CV_8UC1)
			{
				img.at<uchar>(j, i) = 0;
			}
			else if (img.type() == CV_8UC3)
			{
				img.at<Vec3b>(j, i)[0] = 0;			// Vec3b为3个值的向量类型
				img.at<Vec3b>(j, i)[1] = 0;
				img.at<Vec3b>(j, i)[2] = 0;			// [] 指定通道，
			}
			
		}
	
	}
}

int mainzea()
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
	saltAndPepper(gray, 1000);
	saltAndPepper(image, 1000);
	imshow("灰度+椒盐", gray);
	imshow("原图+椒盐", image);
	waitKey();
	return 0;

}