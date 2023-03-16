#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/*
	像素逻辑运算：

			bitwise_and(与):  (src1, src2, dst, mask), CV_8U的像素值从0到255，此时逻辑运算需要将像素值转化成二进制后再进行；
			bitwise_or(或): (src1, src2, dst, mask), 同上
			bitwise_xor(异或）同上
			bitwise_not(非）：(src, dst, mask)  只能针对一个数值进行。

	要保证两个图像矩阵之间的尺寸、数据类型和通道数相同，多个通道进行逻辑运算时不同通道之间是相互独立的。
*/
int main2(int argc, char *argv[])
{
	// 创建两个黑白图像
	Mat img0, img1;
	img0= Mat::zeros(200, 200, CV_8UC1);
	img1 = Mat::zeros(200, 200, CV_8UC1);
	img0(Rect(50, 50, 100, 100)) = Scalar(255);
	img1(Rect(100, 100, 100, 100)) = Scalar(255);
	imshow("img0", img0);
	imshow("img1", img1);

	// 进行逻辑运算
	Mat myAnd, myOr, myXor, myNot;
	bitwise_and(img0, img1, myAnd);
	bitwise_or(img0, img1, myOr);
	bitwise_xor(img0, img1, myXor);
	bitwise_not(img0, myNot);

	imshow("与", myAnd);
	imshow("或", myOr);
	imshow("异或", myXor);
	imshow("非", myNot);
	waitKey();
	return 0;




}