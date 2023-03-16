#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	����ͶӰ���������ȼ���ĳһ������ֱ��ͼģ�ͣ�Ȼ��ʹ�ø�ģ��ȥѰ��ͼ�����Ƿ���ڸ������ķ�����

	calcBackProject(const Mat *images,		// ���ͳ��ֱ��ͼͼ�����飬 ֻ����CV_8U, CV_16U, CV_32F
					int nimages,			// ����ͼ�������
					const int *channels,	// ��Ҫͳ�Ƶ�ͨ���������飬 ��һ��ͼ���ͨ��������0��image[0].channel()-1,�ڶ���ͼ��ͨ��������images[0].channels()��images[0].channels+images[1].channels()-1... �Դ�����
					InputArray hist,		// ����ֱ��ͼ�� ����ģ��ͼ���ֱ��ͼͳ�ƽ��
					backProject,			// Ŀ��Ϊ����ͶӰͼ����images[0]������ͬ�ߴ���������͵ĵ�ͨ��ͼ��
					ranges,					// ÿ��ͼ��ͨ���лҶ�ֵ��ȡֵ��Χ
					scale,					// �������ͶӰ����ı�������
					uniform,				// ֱ��ͼ�Ƿ���ȵı�־���� Ĭ�����Ǿ��ȣ�True��
	
	�ú�������������ͼ����Ѱ�����ض�ͼ����ƥ��ĵ�����򣬼���ͼ��ֱ��ͼ����ͶӰ��

	���裺  1������img�� tempģ�壨��img�н�ȡ����
			2��������ͼƬ��BGR 2 HSV;
			3��ͳ��H-Sֱ��ͼ
			4��ֱ��ͼ��һ��������H-S��άֱ��ͼ��
			5������calcBackProject().
	
*/


void drawHist(Mat &hist, int type, string name)
{
	int hist_w = 500;
	int hist_h = 400;
	Mat histImg = Mat::zeros(hist_w, hist_h, CV_8UC3);

	// ��һ��
	normalize(hist, hist, 255, 0, type, -1, Mat());
	namedWindow(name, WINDOW_AUTOSIZE);
	imshow(name, hist);

}




int mainaacx(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼƬ\\1.jpg");
	if (img.empty())
	{
		cout << "ͼƬ���ش���!" << endl;
		return -1;
	}

	Mat temp = img(Rect(100, 100, 100, 100));		// ģ��ͼ�� Ҳ����ĳһ������ͼ��

	imshow("img", img);
	imshow("temp", temp);


	// 2����ͼƬת��Ϊhsv�ռ�
	Mat img_hsv, temp_hsv;
	cvtColor(img, img_hsv,COLOR_BGR2HSV);
	cvtColor(temp, temp_hsv, COLOR_BGR2HSV);

	// 3��ͳ��h-sֱ��ͼ
	Mat hist, hist2;
	int h_bins = 32; int s_bins = 32;			// ÿ��ͨ����ֱ��ͼά�ȣ��������ص����ֵ��  �����Ƕ�ά������Ҫ��������������
	int histSize[] = { h_bins, s_bins };		
	// Hͨ��ֵ�ķ�Χ��0-179
	float h_ranges[] = { 0, 180 };
	// Sͨ��ֵ�ķ�Χ��0-255
	float s_ranges[] = { 0, 255 };
	const float* ranges[] = { h_ranges, s_ranges };		// ��Χָ�����飬  ÿ��ͨ���ķ�Χ
	int channels[] = { 0, 1 };                  // ͳ�Ƶ�ͨ������
	calcHist(&temp, 1, channels, Mat(), hist, 2, histSize, ranges);			// ͳ��ģ���h-sֱ��ͼ
	
	// 4��ֱ��ͼ��һ��������h-s��άֱ��ͼ
	drawHist(hist, NORM_INF, "hist");

	// 5������calcBackProject()
	Mat backProject;
	calcBackProject(&img_hsv, 1, channels, hist, backProject, ranges, 1.0);		// ֱ��ͼ����ͶӰ

	imshow("����ͶӰ", backProject);
	waitKey();

	return 0;


}