#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description: 在含有坐标的二维点的集合中查找直线，检测直线使用的方法是标准霍夫变换法；
	函数： HoughLinesPointSet(point, lines, lines_max, threshold, min_rho, max_rho, rho_step, min_theta, max_theta, theta_step);
	Args:
		- point: 输入点集合，必须是平面内的二维坐标，数据类型必须是CV_32FC2或CV_32SC2; 可将点集定义为vector<Point2f>或vector<Point2i>类型；
		- lines: 输入点集合中可能存在的直线，每一条直线有3个参数，分别是权重、直线距离坐标原点的距离r和坐标原点到直线的垂线与x轴的夹角δ；是一个1xN的矩阵，类型CV_64FC3
		- lines_max: 检测直线的最大数目；
		- threshold: 累加器的阈值，离散化后每个方格被通过的累积次数大于阈值，识别为直线，否则不被识别；
		- min_rho: 检测直线长度的最小距离，以像素为单位；
		- max_rho: 检测直线长度的最大距离，以像素为单位；
		- rho_step: 以像素为单位的距离分辨率，即距离r离散化时的单位长度；
		- min_theta: 检测直线的最小角度值，以弧度为单位；
		- max_theta: 检测直线的最大角度值，以弧度为单位；
		- theta_step: 以弧度为单位的角度分辨率，即夹角δ离散化时的单位角度
*/


int mainaevc(int argc, char* argv[])
{
	Mat lines;		// 存放检测直线结果的矩阵
	vector<Vec3d> line3d;	// 换一种结果存放
	vector<Point2f> point;		// 待检测是否存在直线的所有点集
	const static float Points[20][2] = {
		{0.0f, 369.0f},  {10.0f, 364.0f}, {20.0f, 358.0f}, {30.0f, 352.0f},
		{40.0f, 346.0f}, {50.0f, 341.0f}, {60.0f, 335.0f}, {70.0f, 329.0f},
		{80.0f, 323.0f}, {90.0f, 318.0f}, {100.0f, 312.0f}, {110.0f, 306.0f},
		{120.0f, 300.0f}, {130.0f, 295.0f}, {140.0f, 289.0f}, {150.0f, 284.0f},
		{160.0f, 277.0f}, {170.0f, 271.0f}, {180.0f, 266.0f}, {190.0f, 260.0f}
	};
	// 将所有点存放在vector中，用于输入函数
	for (int i = 0; i < 20; i++)
	{
		point.push_back(Point2f(Points[i][0], Points[i][1]));
	}
	// 参数设置
	double rhoMin = 0.0f;		// 最小距离
	double rhoMax = 360.0f;		// 最大距离
	double rhostep = 1;			// 离散化单位距离
	double thetaMin = 0.0f;		// 最小角度
	double thetaMax = CV_PI / 2.0f;		// 最大角度
	double thetaStep = CV_PI / 180.0f;		// 离散化单位角度

	HoughLinesPointSet(point, lines, 20, 1, rhoMin, rhoMax, rhostep, thetaMin, thetaMax, thetaStep);

	lines.copyTo(line3d);		// 将检测到的Mat类型直线转化为vector<Vec3d>类型

	// 输出结果
	for (int i = 0; i < line3d.size(); i++)
	{
		cout << "votes:" << (int)line3d.at(i).val[0] << ","			// 权重
			<< "rho:" << line3d.at(i).val[1] << ","					// 直线距离坐标原点的距离
			<< "theta:" << line3d.at(i).val[2] << endl;				// 坐标原点到直线的垂线与x轴的夹角
	}


	return 0;
}