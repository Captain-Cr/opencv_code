#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description: 直线拟合，利用最小二乘法拟合出距离所有点最近的直线，直线的描述形式可以转化为点斜式。
	函数： fitLine(points, line, distType, param, reps, aeps);
	Args:
		- points: 输入待拟合直线的二维或者三维点集，可以存放在vector<>或Mat中
		- line: 输出描述直线的参数，二维点描述参数为vec4f类型，三维点描述参数为Vec6f类型。输出量vec4f类型的（vx, vy, x0, y0)，其中（vx，vy）是与直线共线的归一化参数，（x0，y0）是拟合直线上的任意一点。表示形式为： y=vy/vx*(x-x0)+y0
		- distType: M-estimator算法使用的距离类型标志，有L1、L2、L12
		- param: 某些距离类型的数值参数（C）。如果数值为0，那么自动选择最佳值；
		- reps： 坐标原点与拟合直线之间的距离精度，数值0表示选择自适应参数，一般选择0.01；
		- aeps： 拟合直线的角度精度， 数值为0表示选择自适应参数，一般选择0.01；
*/

int mainafz(int argc, char* argv[])
{
	Vec4f lines;		// 存放描述直线参数，二维的为（vx，vy，x0，y0）
	vector<Point2f> point;		// 存放用于拟合的点
	const static float Points[20][2] = {
		{0.0f, 0.0f},{10.0f, 11.0f},{21.0f, 20.0f},{30.0f, 30.0f},
		{40.0f, 42.0f},{50.0f, 50.0f},{60.0f, 60.0f},{70.0f, 70.0f},
		{80.0f, 80.0f},{90.0f, 92.0f},{100.0f, 100.0f},{110.0f, 110.0f},
		{120.0f, 120.0f},{136.0f, 130.0f},{138.0f, 140.0f},{150.0f, 150.0f},
		{160.0f, 163.0f},{175.0f, 170.0f},{181.0f, 180.0f},{200.0f, 190.0f}
	};

	// 将所有点放到vector中，用于输入函数
	for (int i = 0; i < 20; i++) {
		point.push_back(Point2f(Points[i][0], Points[i][1]));
	}

	// 参数设置
	double param = 0;		// 距离类型中的参数C
	double reps = 0;		// 坐标原点与直线之间的距离精度
	double aeps = 0;		// 角度精度
	
	// 直线拟合
	fitLine(point, lines, DIST_L1, param, reps, aeps);

	double k = lines[1] / lines[0];		// 斜率, vy / vx
	cout << "直线斜率：" << k << endl;
	cout << "直线上一点坐标x：" << lines[2] << ", y:" << lines[3] << endl;
	cout << "直线解析式： y=" << k << "(x - " << lines[2] << ")" << "+" << lines[3] << endl;

	Mat test = Mat::zeros(Size(512, 512), CV_8UC3);
	line(test, Point(0, 0), Point(lines[2],lines[3]), Scalar(0, 255, 0), 5);
	imshow("test", test);
	waitKey();
	return 0;


}