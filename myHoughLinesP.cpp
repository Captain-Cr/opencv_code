#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	名称： 渐进概率式霍夫变换
	功能：寻找图像中满足条件的直线或者线段两个端点的坐标。
	函数：HoughLinesP(Image, lines, rho, theta, threshold, minLineLength=0, maxLineGap=0);
		- image: 输入图像，必须是CV_8C的单通道二值图像；
		- line：检测到的直线或者线段两个端点的坐标，是一个Nx4的vector<Vec4i>矩阵，每一条直线都由4个参数描述，分别是（x1, y1, x2, y2)；
		- rho: 以像素为单位的距离分辨率，即距离r离散化时的单位长度；
		- theta: 以弧度为单位的角度分辨率，即夹角离散化时的单位角度；
		- threshold： 累加器的阈值，即参数空间中离散化后每个方格被通过的累计次数大于阈值时被认为是直线，否则不被识别为直线；这个数值越大，对应在原图像的直线越长，反之越短
		- minLineLength: 直线的最小长度，当检测直线的长度小于该数值时将被剔除；
		- maxLineGap： 同一直线上相邻两个点之间的最大距离，这个参数主要能控制倾斜直线的检测长度，当提取较长的倾斜直线的时候，该参数应该具有较大取值。
*/

int mainGEAF(int argc, char* argv[])
{
	//system("color F0");

	Mat img = imread("D:\\图片\\12.jpg");
	if (img.empty())
	{
		cout << "图片加载失败" << endl;
		return -1;
	}

	Mat gray,edge;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Canny(gray, edge, 50,150,3,false);
	threshold(edge, edge, 100, 255, THRESH_BINARY);

	// 利用渐进概率式霍夫变换提取直线
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 80, 30, 100);		// 两个点连接最大距离10

	// 绘制两个点连接最大距离10直线检测结果
	Mat img1;
	img.copyTo(img1);
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(img1, Point(lines[i][0], lines[i][1]),
			Point(lines[i][2], lines[i][3]), Scalar(0, 255, 0), 2);
	}

	imshow("edge", edge);
	imshow("HoughLIneP", img1);
	waitKey();
	return 0;



}