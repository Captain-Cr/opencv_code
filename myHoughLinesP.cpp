#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	���ƣ� ��������ʽ����任
	���ܣ�Ѱ��ͼ��������������ֱ�߻����߶������˵�����ꡣ
	������HoughLinesP(Image, lines, rho, theta, threshold, minLineLength=0, maxLineGap=0);
		- image: ����ͼ�񣬱�����CV_8C�ĵ�ͨ����ֵͼ��
		- line����⵽��ֱ�߻����߶������˵�����꣬��һ��Nx4��vector<Vec4i>����ÿһ��ֱ�߶���4�������������ֱ��ǣ�x1, y1, x2, y2)��
		- rho: ������Ϊ��λ�ľ���ֱ��ʣ�������r��ɢ��ʱ�ĵ�λ���ȣ�
		- theta: �Ի���Ϊ��λ�ĽǶȷֱ��ʣ����н���ɢ��ʱ�ĵ�λ�Ƕȣ�
		- threshold�� �ۼ�������ֵ���������ռ�����ɢ����ÿ������ͨ�����ۼƴ���������ֵʱ����Ϊ��ֱ�ߣ����򲻱�ʶ��Ϊֱ�ߣ������ֵԽ�󣬶�Ӧ��ԭͼ���ֱ��Խ������֮Խ��
		- minLineLength: ֱ�ߵ���С���ȣ������ֱ�ߵĳ���С�ڸ���ֵʱ�����޳���
		- maxLineGap�� ͬһֱ��������������֮��������룬���������Ҫ�ܿ�����бֱ�ߵļ�ⳤ�ȣ�����ȡ�ϳ�����бֱ�ߵ�ʱ�򣬸ò���Ӧ�þ��нϴ�ȡֵ��
*/

int mainGEAF(int argc, char* argv[])
{
	//system("color F0");

	Mat img = imread("D:\\ͼƬ\\12.jpg");
	if (img.empty())
	{
		cout << "ͼƬ����ʧ��" << endl;
		return -1;
	}

	Mat gray,edge;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Canny(gray, edge, 50,150,3,false);
	threshold(edge, edge, 100, 255, THRESH_BINARY);

	// ���ý�������ʽ����任��ȡֱ��
	vector<Vec4i> lines;
	HoughLinesP(edge, lines, 1, CV_PI / 180, 80, 30, 100);		// ����������������10

	// ��������������������10ֱ�߼����
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