#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main522()
{
	Mat img = imread("D:\\ͼƬ\\lena.jpg");
	if (img.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// ������ȡֱ��ͼ����ر���
	Mat hist;		// ���ڴ��ֱ��ͼ������
	const int channels[1] = {0};			// ͨ������
	float inRanges[2] = { 0, 255 };			
	const float* range[1] = { inRanges };			// ���ػҶ�ֵ��Χ
	const int bins[1] = { 256 };					// ֱ��ͼ��ά�ȣ���ʼ�������ػҶ�ֵ�����ֵ
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, range);		// ����ͼ��ֱ��ͼ
	cout << "hist.rows" << hist.rows << endl;
	

	// ׼������ֱ��ͼ
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