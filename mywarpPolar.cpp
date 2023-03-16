#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	���������任����任
*/

int main51()
{
	Mat srcImg = imread("E:\\data\\test2.png");
	resize(srcImg, srcImg, Size(800, 680));
	if (srcImg.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	Mat img1, img2;
	Point2f center = Point2f(srcImg.cols / 2, srcImg.rows / 2);			// �任���ĵ�
	// ��������任
	warpPolar(srcImg, img1, Size(srcImg.cols , srcImg.rows ), center, center.x, INTER_LINEAR + WARP_POLAR_LINEAR);

	// �漫����任
	warpPolar(img1, img2, Size(srcImg.cols, srcImg.rows), center, center.x, INTER_LINEAR | WARP_POLAR_LOG);


	imshow("srcImg", srcImg);
	imshow("img1", img1);
	imshow("img2", img2);
	waitKey();
	return 0;
}
