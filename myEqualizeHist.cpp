#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



void drawHist2(Mat &hist, int type, string name)		// 归一化并绘制直方图函数
{
	/*
		Mat &hist:  统计的直方图；
		int type: normalize()函数归一化选择的norm_type
		string name: 窗口名称
	*/
	int hist_w = 512;			// 绘制直方图的图片的宽
	int hist_h = 400;			// 绘制直方图的图片的高
	int weight = 2;				// 权重
	Mat histImage = Mat::zeros(hist_w, hist_h, CV_8UC3);
	normalize(hist, hist, 1, 0, type, -1, Mat());		// 归一化
	
	for (int i = 1; i <= hist.rows; i++)
	{
		// hist.rows == 256, 从1到256
		rectangle(histImage, Point(weight * (i - 1), hist_h - 1),
			Point(weight * i - 1, hist_h - cvRound(hist_h * hist.at<float>(i - 1)) - 1),
			Scalar(255,255,255), -1	);
	}
	
	imshow(name, histImage);

}


int main123()
{
	Mat img = imread("D:\\图片\\1.jpg");
	if (img.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}
	Mat gray;
	Mat hist, hist2;		// 保存直方图统计的图
	Mat equlizeImg;		// 均衡化后的图片
	cvtColor(img, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);

	equalizeHist(gray, equlizeImg);		// 图像进行均衡化，注意只能是单通道图像才可以
	imshow("equalize", equlizeImg);

	// 统计直方图
	const int channels[1] = { 0 };		// 第0个通道
	float inRangle[2] = { 0, 255 };		// 范围
	const float* ranges[1] = { inRangle };		// 上面范围数组的指针
	const int bins[1] = { 256 };

	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);		// 统计原本灰度图的直方图
	calcHist(&equlizeImg, 1, channels, Mat(), hist2, 1, bins, ranges);		// 统计均衡化后的图像的直方图
	
	drawHist2(hist, NORM_INF, "hist");		// 绘制原本图像的直方图
	drawHist2(hist2, NORM_INF, "equalImg");		// 绘制均衡化的图像直方图
	waitKey();
	return 0;




}