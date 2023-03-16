#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	透视变换
	透视前图像和透视后图像之间的变换关系可用3*3变换矩阵表示，可通过两幅图的4个对应点坐标求取。

	getPerspectiveTransform(Point2f src[], Point2f dst[],DECOMP_LU);
	两个输入量都是存放4个浮点坐标的数组， 返回的是一个3*3的变换矩阵；   最佳元素的高斯消元法DECOMP_LU


	warpPerspective(InputArray src,
					outputArray dst,
					M,						// 3*3变换矩阵
					Size dsize,
					flags,
					borderMode）
	
*/


int main1314(int argc, char* argv[])
{
	Mat img = imread("E:\\data\\6087.jpg");
	if (img.empty())
	{
		cout << "图像加载错误！！！" << endl;
		return -1;
	}
	imshow("img", img);
	waitKey();

	// 通过Image watch查看的二维码4个角点坐标
	Point2f src_point[4] = { Point(120,81), Point(219,81), Point(122,178), Point(223,173) };
	// 期望透视变换后的二维码4个角点的坐标
	Point2f dst_point[4] = { Point(0, 0), Point(50,200),Point(200,200),Point(200,200) };

	Mat trans_Matirx, img_warp;
	trans_Matirx = getPerspectiveTransform(src_point, dst_point, DECOMP_LU);		// 计算透视变换矩阵

	warpPerspective(img, img_warp, trans_Matirx, img.size());						// 透视变换投影
	imshow("img_warp", img_warp);
	waitKey();



}