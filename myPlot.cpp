#include <iostream>
#include <opencv2/opencv.hpp>
#include <random>

using namespace std;
using namespace cv;

/*
	���ƶ����
	1��Բ�Σ� circle(img, Point center, int radius, color, thickness, lineType, shift=0);
	2��ֱ�ߣ� line(img, point pt1, point pt2, color, thickness, linetype, shift=0);
	3����Բ�� ellipse(img, point center, Size axes, double angle, startAngle, endAngle, color, lineType, shift);
	4��������Բ�����꣨�������: ellipse2Poly(center, axes, angle, arcStart, arcEnd, delta, vector<Point> &pts);
	5�����ƶ���Σ� fillPoly(img, Point pts[], int *npts, ncontours, color, lineType, shift, offset=Point());
	6�������Σ� rectangle(img, Point pt1, Point pt2, color, thickness, lineType, shift);
				retangle(img, Rect rec, color, thickness, lineType, shift);			Rect rect(left_top_x, left_top_y, h, w)

	7���������ɣ� putText(img,string text, Point org, fontFace, fontScale, color,thickness, lineType)
*/
RNG rng(1234);

int main35()
{
	Mat img = Mat::zeros(Size(600, 800),CV_8UC3);
	// ��Բ
	circle(img, Point(50, 50), 25, Scalar(0, 255, 0),2);

	// ����ֱ��
	line(img, Point(0, 0), Point(img.cols, img.rows), Scalar(255, 0, 0), 2);

	// ������Բ
	ellipse(img, Point(400, 255), Size(110, 70), 0, 0, 100, Scalar(125, 125, 0),2);
	ellipse(img, RotatedRect(Point2f(150, 100), Size2f(30, 20), 0), Scalar(0, 0, 155), 2);
	vector<Point> points;
	// ��һЩ�����һ����Բ
	ellipse2Poly(Point(200, 400), Size(100, 70), 0, 0, 360, 2, points);
	for (int i = 0; i < points.size() - 1; i++)
	{
		// ������Բ��ÿ���㣬 ��ֱ�߰������Բ������
		if (i == points.size() - 2)
		{
			// ��Բ�����һ�������һ��������
			line(img, points[0], points[i], Scalar(0, 0, 255), 2);
			break;
		}
		// ��ǰ��ͺ�һ��������
		line(img, points[i], points[i + 1], Scalar(125, 125, 125), 2);
	}

	// ���ƾ���
	rectangle(img, Point(200, 400), Point(300, 450), Scalar(0, 124, 123), -1);

	// ���ƶ����
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
	
	const Point* pts[3] = { pp[0], pp[1], pp2 };			// pts��������,  ����pts�Ǵ��3������ε�����
	int npts[] = { 6, 6, 5 };								// ��������������ɣ�   pp[0]��6�����㣬   pp[1]��6�����㣬 pp2��5������
	fillPoly(img, pts, npts, 3, Scalar(100, 230, 43), 8);		// ����3�������

	// ��������
	putText(img, "Learn Opencv", Point(100, 400), 2, 1, Scalar(rng.uniform(1, 200), rng.uniform(1, 200), rng.uniform(1, 200)));

	imshow("img", img);
	waitKey();

	return 0;
}