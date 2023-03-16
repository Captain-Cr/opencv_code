#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int mainaa(int argc, char* argv[])
{
	vector<double> positiveData = { 2.0, 8.0, 10.0 };
	vector<double> normalized_L1, normalized_L2, normalized_Inf, normalized_MINMAX;
	// 测试不同归一化方法
	normalize(positiveData, normalized_L1, 1.0, 0.0, NORM_L1);			// 绝对值求和归一化   每个元素/(∑（每个元素））  2/(2+8+10)
	cout << "normalized_L1=[" << normalized_L1[0] << "," << normalized_L1[1] << "," << normalized_L1[2] << "]" << endl;

	normalize(positiveData, normalized_L2, 1.0, 0.0, NORM_L2);			// 模长归一化    每个元素 / 根号下(∑（每个元素的平方））  2/根号(2*2+8*8+10*10)
	cout << "normalized_L2=[" << normalized_L2[0] << "," << normalized_L2[1] << "," << normalized_L2[2] << "]" << endl;

	normalize(positiveData, normalized_Inf, 1.0, 0.0, NORM_INF);			// 最大值归一化    每个元素 / 元素的最大值
	cout << "normalized_Inf=[" << normalized_Inf[0] << "," << normalized_Inf[1] << "," << normalized_Inf[2] << "]" << endl;

	normalize(positiveData, normalized_MINMAX, 1.0, 0.0, NORM_MINMAX);			// 偏移归一化    每个元素 / 元素的最大值
	cout << "normalized_MINMAX=[" << normalized_MINMAX[0] << "," << normalized_MINMAX[1] << "," << normalized_MINMAX[2] << "]" << endl;


	// 将图像归一化
	Mat img = imread("D:\\图片\\1.jpg");
	if (img.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}
	Mat gray, hist;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	const int channels[1] = { 0 };
	float inRange[2] = { 0, 255 };
	const float* range[1] = { inRange }; // 指针，只想一个数组
	const int bins[1] = { 256 };
	// 统计直方图
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, range);
	// 绘制直方图
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage_L1 = Mat::zeros(hist_h, hist_w, CV_8UC3);
	Mat histImage_Inf = Mat::zeros(hist_h, hist_w, CV_8UC3);
	Mat hist_L1, hist_Inf;
	normalize(hist, hist_L1, 1, 0, NORM_L1, -1, Mat());
	for (int i = 1; i <= hist_L1.rows; i++)
	{
		rectangle(histImage_L1, Point(width*(i - 1), hist_h - 1),
			Point(width*i - 1, hist_h - cvRound(30 * hist_h*hist_L1.at<float>(i - 1) - 1)),
			Scalar(255, 255, 255), -1);
	}

	normalize(hist, hist_Inf, 1, 0, NORM_INF, -1, Mat());
	for (int i = 1; i <= hist_Inf.rows; i++)
	{
		rectangle(histImage_Inf, Point(width*(i - 1), hist_h - 1),
			Point(width*i - 1, hist_h - cvRound(hist_h*hist_Inf.at<float>(i - 1) - 1)),
			Scalar(255, 255, 255), -1);
	}

	imshow("histImage_L1", histImage_L1);
	imshow("histImage_Inf", histImage_Inf);
	waitKey();
	return 0;

}
