#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	����ԭ�ͣ�
		HoughLines(input img, Output lines, rho, theta, threshold, srn, stn, min_theta, max_theta);
	������
		image: ����ͼ�񣬱�����CV_8U�ĵ�ͨ����ֵͼ��
		lines: ����任��⵽��ֱ�߼�����������ϵ������һ��N*2��Vector<Vec2f>����ÿһ���е�һ��Ԫ����ֱ�߾�������ԭ��ľ��룬�ڶ���Ԫ���Ǹ�ֱ�߹�����ԭ��Ĵ�����x��ļн�
		rho: ������Ϊ��λ�ľ���ֱ��ʣ�������r��ɢ��ʱ�ĵ�λ���ȣ�
		theta: �Ի���Ϊ��λ�ĽǶȷֱ��ʣ����н���ɢ��ʱ�ĵ�λ�Ƕȣ�
		threshold���ۼ�������ֵ���������ռ�����ɢ����ÿ������ͨ�����ۼƴ������ڸ���ֵʱ��ʶ��Ϊֱ�ߣ�
		srn�����ڶ�߶Ȼ���任���ò�����ʾ����ֱ��ʵĳ��������Ե��ۼ�������ֱ����ǵ���������rho����ȷ���ۼ����ֱ�����rho/srn��������������ǷǸ�����Ĭ��Ϊ0��
		stn:���ڶ�߶Ȼ���任���ò�����ʾ�Ƕȷֱ��ʵĳ��������Ե��ۼ����Ƕȷֱ����ǵ��ĸ�����theta����ȷ���ۼ����ֱ�����theta/stn���Ǹ���Ĭ��0����srn��stnͬʱΪ0����Ϊ��׼����任��
		min_theta:���ֱ�ߵ���С�Ƕȣ�Ĭ�ϲ���0��
		max_theta:���ֱ�ߵ����Ƕȣ�Ĭ��CV_PI��

	�ú���Ѱ��ͼ���ֱ�ߣ����Լ��������ʽ��ͼ���еļ�����������
*/

void drawLine(Mat &img,		// Ҫ���ֱ�ߵ�ͼ��
	vector<Vec2f> lines,	// ����ֱ������
	double rows,			// ԭͼ��ĸ�
	double cols,			// ԭͼ��Ŀ�
	Scalar scalar,			// ����ֱ�ߵ���ɫ
	int n)				// ����ֱ�ߵ��߿�
{
	Point pt1, pt2;
	// ����vector����
	for (int i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];			// ֱ�߾�������ԭ��ľ���
		float theta = lines[i][1];			// ֱ��������ԭ��Ĵ�����x��ļн�
		double a = cos(theta);				// �нǵ�����
		double b = sin(theta);				// �нǵ�����
		double x0 = a * rho, y0 = b * rho;		// ֱ���������ԭ��Ĵ��ߵĽ���
		double length = max(rows, cols);			// ͼ���ߵ����ֵ
		// ����ֱ���ϵ�һ��
		pt1.x = cvRound(x0 + length * (-b));
		pt1.y = cvRound(y0 + length * (a));
		// ��������һ��
		pt2.x = cvRound(x0 - length * (-b));
		pt2.y = cvRound(y0 - length * (a));
		// ����ֱ��
		line(img, pt1, pt2, scalar, n);
	}
}
				


int mainafev(int argc, char *argv[])
{
	Mat img = imread("D:\\ͼƬ\\12.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	Mat gray, edge;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Canny(gray, edge, 100, 200, 3, false);
	//threshold(gray, edge, 150, 255, THRESH_BINARY_INV);
	imshow("edge", edge);

	// ����ֱ�߼��
	vector<Vec2f> lines1, lines2;		// �������vector<Vec2f>
	HoughLines(edge, lines1, 1, CV_PI / 180, 110, 0, 0);
	
	// ��ԭͼ�����ֱ��
	Mat img1;
	img.copyTo(img1);
	drawLine(img1, lines1, edge.rows, edge.cols, Scalar(0,255,0), 2);

	// ��ʾ
	imshow("line", img1);
	waitKey();
}