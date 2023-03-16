#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description: ֱ����ϣ�������С���˷���ϳ��������е������ֱ�ߣ�ֱ�ߵ�������ʽ����ת��Ϊ��бʽ��
	������ fitLine(points, line, distType, param, reps, aeps);
	Args:
		- points: ��������ֱ�ߵĶ�ά������ά�㼯�����Դ����vector<>��Mat��
		- line: �������ֱ�ߵĲ�������ά����������Ϊvec4f���ͣ���ά����������ΪVec6f���͡������vec4f���͵ģ�vx, vy, x0, y0)�����У�vx��vy������ֱ�߹��ߵĹ�һ����������x0��y0�������ֱ���ϵ�����һ�㡣��ʾ��ʽΪ�� y=vy/vx*(x-x0)+y0
		- distType: M-estimator�㷨ʹ�õľ������ͱ�־����L1��L2��L12
		- param: ĳЩ�������͵���ֵ������C���������ֵΪ0����ô�Զ�ѡ�����ֵ��
		- reps�� ����ԭ�������ֱ��֮��ľ��뾫�ȣ���ֵ0��ʾѡ������Ӧ������һ��ѡ��0.01��
		- aeps�� ���ֱ�ߵĽǶȾ��ȣ� ��ֵΪ0��ʾѡ������Ӧ������һ��ѡ��0.01��
*/

int mainafz(int argc, char* argv[])
{
	Vec4f lines;		// �������ֱ�߲�������ά��Ϊ��vx��vy��x0��y0��
	vector<Point2f> point;		// ���������ϵĵ�
	const static float Points[20][2] = {
		{0.0f, 0.0f},{10.0f, 11.0f},{21.0f, 20.0f},{30.0f, 30.0f},
		{40.0f, 42.0f},{50.0f, 50.0f},{60.0f, 60.0f},{70.0f, 70.0f},
		{80.0f, 80.0f},{90.0f, 92.0f},{100.0f, 100.0f},{110.0f, 110.0f},
		{120.0f, 120.0f},{136.0f, 130.0f},{138.0f, 140.0f},{150.0f, 150.0f},
		{160.0f, 163.0f},{175.0f, 170.0f},{181.0f, 180.0f},{200.0f, 190.0f}
	};

	// �����е�ŵ�vector�У��������뺯��
	for (int i = 0; i < 20; i++) {
		point.push_back(Point2f(Points[i][0], Points[i][1]));
	}

	// ��������
	double param = 0;		// ���������еĲ���C
	double reps = 0;		// ����ԭ����ֱ��֮��ľ��뾫��
	double aeps = 0;		// �ǶȾ���
	
	// ֱ�����
	fitLine(point, lines, DIST_L1, param, reps, aeps);

	double k = lines[1] / lines[0];		// б��, vy / vx
	cout << "ֱ��б�ʣ�" << k << endl;
	cout << "ֱ����һ������x��" << lines[2] << ", y:" << lines[3] << endl;
	cout << "ֱ�߽���ʽ�� y=" << k << "(x - " << lines[2] << ")" << "+" << lines[3] << endl;

	Mat test = Mat::zeros(Size(512, 512), CV_8UC3);
	line(test, Point(0, 0), Point(lines[2],lines[3]), Scalar(0, 255, 0), 5);
	imshow("test", test);
	waitKey();
	return 0;


}