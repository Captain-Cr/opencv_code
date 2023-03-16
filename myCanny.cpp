#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Canny(src, dst, threshold1, threshold2, aperturesize=3, L2gradient=flase);
	���У� src: ����ͼ�񣬱�����CV_8U�ĵ�ͨ������ͨ��ͼ��
		   aperturesize: sobel���ӵ�ֱ��

*/

int mainazg()
{
	Mat img = imread("D://ͼƬ//1.jpg",0);
	if (img.empty())
	{
		cout << "ͼ����ش���" << endl;
		return -1;
	}
	Mat resultHigh, resultLow, resultG;

	// ����ֵ���ͼ���Ե
	Canny(img, resultHigh, 100, 200, 3);


	// ����ֵ���ͼ���Ե
	Canny(img, resultLow, 20, 40, 3);

	// ��˹ģ������ͼ��
	GaussianBlur(img, resultG, Size(3, 3), 5);
	Canny(resultG, resultG, 100, 200, 3);

	imshow("img", img);
	imshow("height", resultHigh);
	imshow("Low", resultLow);
	imshow("resultG", resultG);
	waitKey();

	return 0;



}