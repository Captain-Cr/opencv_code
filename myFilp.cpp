#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main1111(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	if (img.empty())
	{
		cout << "Í¼Ïñ¼ÓÔØ´íÎó£¡£¡£¡" << endl;
		return -1;
	}
	imshow("src", img);


	Mat img_x, img_y, img_x_y;
	flip(img, img_x, 0);			// ÈÆxÖá·­×ª,    ÉÏÏÂ
	flip(img, img_y, 1);			// ÈÆyÖá·­×ª£¬   ×óÓÒ
	flip(img, img_x_y, -1);			// ÈÆxyÖá·­×ª£¬  ÉÏÏÂ×óÓÒ

	imshow("xÖá·­×ª", img_x);
	imshow("yÖá·­×ª", img_y);
	imshow("Á½Öá·­×ª", img_x_y);
	waitKey();
	return 0;



}