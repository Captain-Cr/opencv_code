#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	Description:亚像素级别角点，主要原理：寻找一点，其指向邻域范围内每一个像素点的向量与该像素点的梯度向量的乘积之和最小。

	Function:
		void cornerSubPix(InputArray image, InputOutputArray corners, Size winSize, Size zeroZone, TermCriteria criteria);
*/


int mainCornerSubPix(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\contours.png");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}
	Mat img2;
	img.copyTo(img2);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 寻找Shi-Tomas角点
	vector<Point2f> corners;
	int maxCorners = 100;					// 最大角点数量
	double quality_level = 0.01;			// 质量等级，或指阈值与最佳角点的比例关系
	double minDistance = 0.04;				// 两个角点的最小欧式距离
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);
	// 用红色绘制角点
	vector<KeyPoint> keypoints;
	for (int i = 0; i < corners.size(); i++)
	{
		KeyPoint keypoint;
		keypoint.pt = corners[i];
		keypoints.push_back(keypoint);
	}
	drawKeypoints(img, keypoints, img, Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);

	// 进行亚像素角点检测
	vector<Point2f> cornerSub = corners;				// 角点备份，防止被函数修改
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 80, 0.001);
	cornerSubPix(gray, cornerSub, winSize, zeroZone, criteria);

	// 输出精确坐标
	vector<KeyPoint> keypointsBySub;
	for (int j = 0; j < cornerSub.size(); j++)
	{
		KeyPoint keypoint;
		keypoint.pt = cornerSub[j];
		keypointsBySub.push_back(keypoint);
	}
	drawKeypoints(img, keypointsBySub, img, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);


	imshow("img", img);
	waitKey();
	destroyAllWindows();
	return 0;
}