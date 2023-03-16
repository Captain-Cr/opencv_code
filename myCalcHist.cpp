#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main522()
{
	Mat img = imread("D:\\图片\\lena.jpg");
	if (img.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 设置提取直方图的相关变量
	Mat hist;		// 用于存放直方图计算结果
	const int channels[1] = {0};			// 通道索引
	float inRanges[2] = { 0, 255 };			
	const float* range[1] = { inRanges };			// 像素灰度值范围
	const int bins[1] = { 256 };					// 直方图的维度，起始就是像素灰度值的最大值
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, range);		// 计算图像直方图
	cout << "hist.rows" << hist.rows << endl;
	

	// 准备绘制直方图
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);

	for (int i = 1; i <= hist.rows; i++)
	{
		rectangle(histImage, Point(width * (i - 1), hist_h - 1), Point(width * (i - 1), hist_h - cvRound(hist.at<float>(i - 1) / 15)), Scalar(255, 255, 255), -1);
	}
	imshow("histImage", histImage);
	imshow("gray", gray);
	waitKey();
	return 0;

}