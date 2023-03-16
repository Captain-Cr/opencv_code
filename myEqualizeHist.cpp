#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



void drawHist2(Mat &hist, int type, string name)		// ��һ��������ֱ��ͼ����
{
	/*
		Mat &hist:  ͳ�Ƶ�ֱ��ͼ��
		int type: normalize()������һ��ѡ���norm_type
		string name: ��������
	*/
	int hist_w = 512;			// ����ֱ��ͼ��ͼƬ�Ŀ�
	int hist_h = 400;			// ����ֱ��ͼ��ͼƬ�ĸ�
	int weight = 2;				// Ȩ��
	Mat histImage = Mat::zeros(hist_w, hist_h, CV_8UC3);
	normalize(hist, hist, 1, 0, type, -1, Mat());		// ��һ��
	
	for (int i = 1; i <= hist.rows; i++)
	{
		// hist.rows == 256, ��1��256
		rectangle(histImage, Point(weight * (i - 1), hist_h - 1),
			Point(weight * i - 1, hist_h - cvRound(hist_h * hist.at<float>(i - 1)) - 1),
			Scalar(255,255,255), -1	);
	}
	
	imshow(name, histImage);

}


int main123()
{
	Mat img = imread("D:\\ͼƬ\\1.jpg");
	if (img.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}
	Mat gray;
	Mat hist, hist2;		// ����ֱ��ͼͳ�Ƶ�ͼ
	Mat equlizeImg;		// ���⻯���ͼƬ
	cvtColor(img, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);

	equalizeHist(gray, equlizeImg);		// ͼ����о��⻯��ע��ֻ���ǵ�ͨ��ͼ��ſ���
	imshow("equalize", equlizeImg);

	// ͳ��ֱ��ͼ
	const int channels[1] = { 0 };		// ��0��ͨ��
	float inRangle[2] = { 0, 255 };		// ��Χ
	const float* ranges[1] = { inRangle };		// ���淶Χ�����ָ��
	const int bins[1] = { 256 };

	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);		// ͳ��ԭ���Ҷ�ͼ��ֱ��ͼ
	calcHist(&equlizeImg, 1, channels, Mat(), hist2, 1, bins, ranges);		// ͳ�ƾ��⻯���ͼ���ֱ��ͼ
	
	drawHist2(hist, NORM_INF, "hist");		// ����ԭ��ͼ���ֱ��ͼ
	drawHist2(hist2, NORM_INF, "equalImg");		// ���ƾ��⻯��ͼ��ֱ��ͼ
	waitKey();
	return 0;




}