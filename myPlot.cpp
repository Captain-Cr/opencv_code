#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>

using namespace std;
using namespace cv;

/*
	绘制多边形
	1、圆形： circle(img, Point center, int radius, color, thickness, lineType, shift=0);
	2、直线： line(img, point pt1, point pt2, color, thickness, linetype, shift=0);
	3、椭圆： ellipse(img, point center, Size axes, double angle, startAngle, endAngle, color, lineType, shift);
	4、保存椭圆的坐标（不输出）: ellipse2Poly(center, axes, angle, arcStart, arcEnd, delta, vector<Point> &pts);
	5、绘制多边形： fillPoly(img, Point pts[], int *npts, ncontours, color, lineType, shift, offset=Point());
	6、正方形： rectangle(img, Point pt1, Point pt2, color, thickness, lineType, shift);
				retangle(img, Rect rec, color, thickness, lineType, shift);			Rect rect(left_top_x, left_top_y, h, w)

	7、文字生成： putText(img,string text, Point org, fontFace, fontScale, color,thickness, lineType)
*/
RNG rng(1234);

int main35()
{
	Mat img = Mat::zeros(Size(600, 800),CV_8UC3);
	// 画圆
	circle(img, Point(50, 50), 25, Scalar(0, 255, 0),2);

	// 绘制直线
	line(img, Point(0, 0), Point(img.cols, img.rows), Scalar(255, 0, 0), 2);

	// 绘制椭圆
	ellipse(img, Point(400, 255), Size(110, 70), 0, 0, 100, Scalar(125, 125, 0),2);
	ellipse(img, RotatedRect(Point2f(150, 100), Size2f(30, 20), 0), Scalar(0, 0, 155), 2);
	vector<Point> points;
	// 用一些点近似一个椭圆
	ellipse2Poly(Point(200, 400), Size(100, 70), 0, 0, 360, 2, points);
	for (int i = 0; i < points.size() - 1; i++)
	{
		// 遍历椭圆的每个点， 用直线把这个椭圆画出来
		if (i == points.size() - 2)
		{
			// 椭圆的最后一个点与第一个点连线
			line(img, points[0], points[i], Scalar(0, 0, 255), 2);
			break;
		}
		// 当前点和后一个点连线
		line(img, points[i], points[i + 1], Scalar(125, 125, 125), 2);
	}

	// 绘制矩形
	rectangle(img, Point(200, 400), Point(300, 450), Scalar(0, 124, 123), -1);

	// 绘制多边形
	Point pp[2][6];
	pp[0][0] = Point(72, 200);
	pp[0][1] = Point(142, 204);
	pp[0][2] = Point(226, 263);
	pp[0][3] = Point(172, 310);
	pp[0][4] = Point(117, 319);
	pp[0][5] = Point(15, 260);

	pp[1][0] = Point(359, 339);
	pp[1][1] = Point(447, 351);
	pp[1][2] = Point(504, 349);
	pp[1][3] = Point(484, 433);
	pp[1][4] = Point(418, 449);
	pp[1][5] = Point(354, 402);

	Point pp2[5];
	pp2[0] = Point(350, 83);
	pp2[1] = Point(463, 90);
	pp2[2] = Point(500, 171);
	pp2[3] = Point(421, 194);
	pp2[4] = Point(338, 141);
	
	const Point* pts[3] = { pp[0], pp[1], pp2 };			// pts变量生成,  这里pts是存放3个多边形的数组
	int npts[] = { 6, 6, 5 };								// 顶点个数数组生成，   pp[0]有6个顶点，   pp[1]有6个顶点， pp2有5个顶点
	fillPoly(img, pts, npts, 3, Scalar(100, 230, 43), 8);		// 绘制3个多边形

	// 生成文字
	putText(img, "Learn Opencv", Point(100, 400), 2, 1, Scalar(rng.uniform(1, 200), rng.uniform(1, 200), rng.uniform(1, 200)));

	imshow("img", img);
	waitKey();

	return 0;
}