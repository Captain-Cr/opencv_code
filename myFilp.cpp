#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main1111(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
		return -1;
	}
	imshow("src", img);


	Mat img_x, img_y, img_x_y;
	flip(img, img_x, 0);			// ��x�ᷭת,    ����
	flip(img, img_y, 1);			// ��y�ᷭת��   ����
	flip(img, img_x_y, -1);			// ��xy�ᷭת��  ��������

	imshow("x�ᷭת", img_x);
	imshow("y�ᷭת", img_y);
	imshow("���ᷭת", img_x_y);
	waitKey();
	return 0;



}