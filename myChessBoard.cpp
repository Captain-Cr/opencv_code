#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	找到图像中的标定的棋盘标定板的角点
*/

int main(int argc, char* argv[])
{
	Mat img1 = imread("D:\\图像处理案例图片\\images\\chessboard.png");
	Mat img2 = imread("D:\\图像处理案例图片\\images\\1.png");
	
	if (img1.empty() || img2.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}
	Mat gray1, gray2;
	cvtColor(img1, gray1, COLOR_BGR2GRAY);
	cvtColor(img2, gray2, COLOR_BGR2GRAY);

	// 判断图像是否包含棋盘标定板
	Size board_size1 = Size(7, 7);			// 方形标定板内角点数目（行，列）
	Size board_size2 = Size(7, 7);			// 圆形标定板圆心数目（行，列）

	
	// 检测角点
	vector<Point2f> img1_points, img2_points;
	int ret1 = findChessboardCorners(gray1, board_size1, img1_points);			// 计算方格标定板角点
	int ret2 = findCirclesGrid(gray2, board_size2, img2_points);				// 计算圆形标定板角点
	if (ret1 == 0 || ret2 == 0)
	{
		cout << "方形标定板判断满足条件代码：" << ret1 << endl;
		cout << "圆形标定板判断满足条件代码:" << ret2 << endl;
	}

	// 细化角点坐标
	find4QuadCornerSubpix(gray1, img1_points, Size(5, 5));			// 细化方格标定板角点坐标
	find4QuadCornerSubpix(gray2, img2_points, Size(5, 5));			// 细化圆形标定板角点坐标

	// 绘制角点检测坐标
	drawChessboardCorners(img1, board_size1, img1_points, true);
	drawChessboardCorners(img2, board_size2, img2_points, true);

	// 显示结果
	imshow("方形标定板角点检测结果：", img1);
	imshow("圆形标定板角点检测结果：", img2);
	waitKey();
	destroyAllWindows();
	return 0;


}