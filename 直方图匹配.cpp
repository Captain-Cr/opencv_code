#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	��ֱ��ͼӳ���ָ���ֲ���ʽ���㷨��Ϊֱ��ͼƥ���ֱ��ͼ����
*/


void drawHist22(Mat &hist, int type, string name)		// ��һ��������ֱ��ͼ����
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
			Point(weight * i - 1, hist_h - cvRound(20 * hist_h * hist.at<float>(i - 1)) - 1),
			Scalar(255, 255, 255), -1);
	}

	imshow(name, histImage);
	
}



int mainaga()
{
	Mat img1 = imread("D:\\ͼƬ\\1.jpg",0);			// ԭͼ��ͨ��Ŀ��ֱ��ͼͼ��ı�ͼ��ֱ��ͼ�����Ŀ��ֱ��ͼ�ָ
	Mat img2 = imread("D:\\ͼƬ\\12.jpg", 0);

	if (img1.empty() || img2.empty())
	{
		cout << "ͼƬ���ش���" << endl;
		return -1;
	}


	Mat hist1, hist2;
	// ͳ������ͼ��ֱ��ͼ
	const int channels[1] = { 0 };		// ͼ��ͨ��
	float inRangle[2] = { 0, 255 };		// ��Χ
	const float* range[1] = { inRangle };	// ��Χ����ָ��
	const int bins[1] = { 256 };
	calcHist(&img1, 1, channels, Mat(), hist1, 1, bins, range);
	calcHist(&img2, 1, channels, Mat(), hist2, 1, bins, range);
	// ��һ������ͼ��ֱ��ͼ
	drawHist22(hist1, NORM_L1, "hist1");
	drawHist22(hist2, NORM_L2, "hist2");
	// ��������ͼ��ֱ��ͼ���ۻ�����
	float hist1_cdf[256] = { hist1.at<float>(0) };		// ֱ��ͼÿ���Ҷȼ��ĸ��ʣ� ����ͨ��normalize��NORM_L1�����ɸ��ʷֲ�
	float hist2_cdf[256] = { hist2.at<float>(0) };
	
	for (int i = 1; i < 256; i++)
	{
		hist1_cdf[i] = hist1_cdf[i - 1] + hist1.at<float>(i);		// ԭͼ��ֱ��ͼ�ۻ�����
		hist2_cdf[i] = hist2_cdf[i - 1] + hist2.at<float>(i);		// Ŀ��ͼ��ֱ��ͼ���ۻ�����
	}

	// �����ۻ����������� ÿһ����ԭͼ��ÿһ���Ҷȼ�[0, 255]ֱ��ͼ�ۻ����ʺ�Ŀ��ͼ�����лҶȼ����ۻ����ʵ���Ȼ������Сֵ     diff_row(i�� = src(i) - [dst(0), dst(1), dst(2).....,dst(255)]
	float diff_cdf[256][256];
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			diff_cdf[i][j] = fabs(hist1_cdf[i] - hist2_cdf[j]);			// fabs():�󸡵����ľ���ֵ�� ԭͼ��ÿһ���Ҷȼ� - Ŀ��ͼ�����еĻҶȼ�
		}
	}

	// ����LUT
	Mat lut(1, 256, CV_8U);
	for (int i = 0; i < 256; i++)
	{
		// ����ԭ�Ҷȼ�Ϊi��ӳ��Ҷ�
		// ��i���ۻ����ʲ�ֵ��С�Ĺ涨���Ҷ�
		float min = diff_cdf[i][0];
		int index = 0;
		// Ѱ���ۻ������������е�ÿһ�е���Сֵ
		for (int j = 1; j < 256; j++)
		{
			if (min > diff_cdf[i][j])
			{
				min = diff_cdf[i][j];
				index = j;
			}
		}
		lut.at<uchar>(i) = (uchar)index;		// ӳ�� 0 --> 4
	}

	Mat result, hist3;
	LUT(img1, lut, result);
	imshow("��ƥ��ͼƬ", img1);
	imshow("Ŀ��ͼƬ", img2);
	imshow("ֱ��ͼƥ����", result);
	calcHist(&result, 1, channels, Mat(), hist3, 1, bins, range);
	drawHist22(hist3, NORM_L1, "hist3");
	waitKey();
	return 0;


























}

