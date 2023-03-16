#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	函数原型：
		HoughLines(input img, Output lines, rho, theta, threshold, srn, stn, min_theta, max_theta);
	参数：
		image: 输入图像，必须是CV_8U的单通道二值图像
		lines: 霍夫变换检测到的直线极坐标描述的系数，是一个N*2的Vector<Vec2f>矩阵，每一行中第一个元素是直线距离坐标原点的距离，第二个元素是该直线过坐标原点的垂线与x轴的夹角
		rho: 以像素为单位的距离分辨率，即距离r离散化时的单位长度；
		theta: 以弧度为单位的角度分辨率，即夹角离散化时的单位角度；
		threshold：累加器的阈值，即参数空间中离散化后每个方格被通过的累计次数大于该阈值时被识别为直线；
		srn：对于多尺度霍夫变换，该参数表示距离分辨率的除数，粗略的累加器距离分辨率是第三个参数rho，精确的累加器分辨率是rho/srn。这个参数必须是非负数，默认为0；
		stn:对于多尺度霍夫变换，该参数表示角度分辨率的除数，粗略的累加器角度分辨率是第四个参数theta，精确的累加器分辨率是theta/stn。非负，默认0，当srn和stn同时为0，即为标准霍夫变换；
		min_theta:检测直线的最小角度，默认参数0；
		max_theta:检测直线的最大角度，默认CV_PI。

	该函数寻找图像的直线，并以极坐标的形式将图像中的极坐标参数输出
*/

void drawLine(Mat &img,		// 要标记直线的图像
	vector<Vec2f> lines,	// 检测的直线数据
	double rows,			// 原图像的高
	double cols,			// 原图像的宽
	Scalar scalar,			// 绘制直线的颜色
	int n)				// 绘制直线的线宽
{
	Point pt1, pt2;
	// 遍历vector容器
	for (int i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];			// 直线距离坐标原点的距离
		float theta = lines[i][1];			// 直线与坐标原点的垂线与x轴的夹角
		double a = cos(theta);				// 夹角的余弦
		double b = sin(theta);				// 夹角的正弦
		double x0 = a * rho, y0 = b * rho;		// 直线与过坐标原点的垂线的交点
		double length = max(rows, cols);			// 图像宽高的最大值
		// 计算直线上的一点
		pt1.x = cvRound(x0 + length * (-b));
		pt1.y = cvRound(y0 + length * (a));
		// 计算另外一点
		pt2.x = cvRound(x0 - length * (-b));
		pt2.y = cvRound(y0 - length * (a));
		// 绘制直线
		line(img, pt1, pt2, scalar, n);
	}
}
				


int mainafev(int argc, char *argv[])
{
	Mat img = imread("D:\\图片\\12.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	Mat gray, edge;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Canny(gray, edge, 100, 200, 3, false);
	//threshold(gray, edge, 150, 255, THRESH_BINARY_INV);
	imshow("edge", edge);

	// 霍夫直线检测
	vector<Vec2f> lines1, lines2;		// 输出的是vector<Vec2f>
	HoughLines(edge, lines1, 1, CV_PI / 180, 110, 0, 0);
	
	// 在原图像绘制直线
	Mat img1;
	img.copyTo(img1);
	drawLine(img1, lines1, edge.rows, edge.cols, Scalar(0,255,0), 2);

	// 显示
	imshow("line", img1);
	waitKey();
}