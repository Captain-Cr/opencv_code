#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	将直方图映射成指定分布形式的算法成为直方图匹配或直方图规则化
*/


void drawHist22(Mat &hist, int type, string name)		// 归一化并绘制直方图函数
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
			Point(weight * i - 1, hist_h - cvRound(20 * hist_h * hist.at<float>(i - 1)) - 1),
			Scalar(255, 255, 255), -1);
	}

	imshow(name, histImage);
	
}



int mainaga()
{
	Mat img1 = imread("D:\\图片\\1.jpg",0);			// 原图像，通过目标直方图图像改变图像直方图（变成目标直方图分割）
	Mat img2 = imread("D:\\图片\\12.jpg", 0);

	if (img1.empty() || img2.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}


	Mat hist1, hist2;
	// 统计两幅图的直方图
	const int channels[1] = { 0 };		// 图像通道
	float inRangle[2] = { 0, 255 };		// 范围
	const float* range[1] = { inRangle };	// 范围数组指针
	const int bins[1] = { 256 };
	calcHist(&img1, 1, channels, Mat(), hist1, 1, bins, range);
	calcHist(&img2, 1, channels, Mat(), hist2, 1, bins, range);
	// 归一化两幅图像直方图
	drawHist22(hist1, NORM_L1, "hist1");
	drawHist22(hist2, NORM_L2, "hist2");
	// 计算两幅图像直方图的累积概率
	float hist1_cdf[256] = { hist1.at<float>(0) };		// 直方图每个灰度级的概率， 上面通过normalize（NORM_L1）后变成概率分布
	float hist2_cdf[256] = { hist2.at<float>(0) };
	
	for (int i = 1; i < 256; i++)
	{
		hist1_cdf[i] = hist1_cdf[i - 1] + hist1.at<float>(i);		// 原图像直方图累积概率
		hist2_cdf[i] = hist2_cdf[i - 1] + hist2.at<float>(i);		// 目标图像直方图的累积概率
	}

	// 构建累积概率误差矩阵， 每一行是原图像每一个灰度级[0, 255]直方图累积概率和目标图像所有灰度级的累积概率的误差。然后求最小值     diff_row(i） = src(i) - [dst(0), dst(1), dst(2).....,dst(255)]
	float diff_cdf[256][256];
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			diff_cdf[i][j] = fabs(hist1_cdf[i] - hist2_cdf[j]);			// fabs():求浮点数的绝对值， 原图像每一个灰度级 - 目标图像所有的灰度级
		}
	}

	// 生成LUT
	Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; i++)
	{
		// 查找原灰度级为i的映射灰度
		// 与i的累积概率差值最小的规定化灰度
		float min = diff_cdf[i][0];
		int index = 0;
		// 寻找累积概率误差矩阵中的每一行的最小值
		for (int j = 1; j < 256; j++)
		{
			if (min > diff_cdf[i][j])
			{
				min = diff_cdf[i][j];
				index = j;
			}
		}
		lut.at<uchar>(i) = (uchar)index;		// 映射 0 --> 4
	}

	Mat result, hist3;
	LUT(img1, lut, result);
	imshow("待匹配图片", img1);
	imshow("目标图片", img2);
	imshow("直方图匹配结果", result);
	calcHist(&result, 1, channels, Mat(), hist3, 1, bins, range);
	drawHist22(hist3, NORM_L1, "hist3");
	waitKey();
	return 0;


























}

