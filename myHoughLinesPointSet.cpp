#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description: �ں�������Ķ�ά��ļ����в���ֱ�ߣ����ֱ��ʹ�õķ����Ǳ�׼����任����
	������ HoughLinesPointSet(point, lines, lines_max, threshold, min_rho, max_rho, rho_step, min_theta, max_theta, theta_step);
	Args:
		- point: ����㼯�ϣ�������ƽ���ڵĶ�ά���꣬�������ͱ�����CV_32FC2��CV_32SC2; �ɽ��㼯����Ϊvector<Point2f>��vector<Point2i>���ͣ�
		- lines: ����㼯���п��ܴ��ڵ�ֱ�ߣ�ÿһ��ֱ����3���������ֱ���Ȩ�ء�ֱ�߾�������ԭ��ľ���r������ԭ�㵽ֱ�ߵĴ�����x��ļнǦģ���һ��1xN�ľ�������CV_64FC3
		- lines_max: ���ֱ�ߵ������Ŀ��
		- threshold: �ۼ�������ֵ����ɢ����ÿ������ͨ�����ۻ�����������ֵ��ʶ��Ϊֱ�ߣ����򲻱�ʶ��
		- min_rho: ���ֱ�߳��ȵ���С���룬������Ϊ��λ��
		- max_rho: ���ֱ�߳��ȵ������룬������Ϊ��λ��
		- rho_step: ������Ϊ��λ�ľ���ֱ��ʣ�������r��ɢ��ʱ�ĵ�λ���ȣ�
		- min_theta: ���ֱ�ߵ���С�Ƕ�ֵ���Ի���Ϊ��λ��
		- max_theta: ���ֱ�ߵ����Ƕ�ֵ���Ի���Ϊ��λ��
		- theta_step: �Ի���Ϊ��λ�ĽǶȷֱ��ʣ����нǦ���ɢ��ʱ�ĵ�λ�Ƕ�
*/


int mainaevc(int argc, char* argv[])
{
	Mat lines;		// ��ż��ֱ�߽���ľ���
	vector<Vec3d> line3d;	// ��һ�ֽ�����
	vector<Point2f> point;		// ������Ƿ����ֱ�ߵ����е㼯
	const static float Points[20][2] = {
		{0.0f, 369.0f},  {10.0f, 364.0f}, {20.0f, 358.0f}, {30.0f, 352.0f},
		{40.0f, 346.0f}, {50.0f, 341.0f}, {60.0f, 335.0f}, {70.0f, 329.0f},
		{80.0f, 323.0f}, {90.0f, 318.0f}, {100.0f, 312.0f}, {110.0f, 306.0f},
		{120.0f, 300.0f}, {130.0f, 295.0f}, {140.0f, 289.0f}, {150.0f, 284.0f},
		{160.0f, 277.0f}, {170.0f, 271.0f}, {180.0f, 266.0f}, {190.0f, 260.0f}
	};
	// �����е�����vector�У��������뺯��
	for (int i = 0; i < 20; i++)
	{
		point.push_back(Point2f(Points[i][0], Points[i][1]));
	}
	// ��������
	double rhoMin = 0.0f;		// ��С����
	double rhoMax = 360.0f;		// ������
	double rhostep = 1;			// ��ɢ����λ����
	double thetaMin = 0.0f;		// ��С�Ƕ�
	double thetaMax = CV_PI / 2.0f;		// ���Ƕ�
	double thetaStep = CV_PI / 180.0f;		// ��ɢ����λ�Ƕ�

	HoughLinesPointSet(point, lines, 20, 1, rhoMin, rhoMax, rhostep, thetaMin, thetaMax, thetaStep);

	lines.copyTo(line3d);		// ����⵽��Mat����ֱ��ת��Ϊvector<Vec3d>����

	// ������
	for (int i = 0; i < line3d.size(); i++)
	{
		cout << "votes:" << (int)line3d.at(i).val[0] << ","			// Ȩ��
			<< "rho:" << line3d.at(i).val[1] << ","					// ֱ�߾�������ԭ��ľ���
			<< "theta:" << line3d.at(i).val[2] << endl;				// ����ԭ�㵽ֱ�ߵĴ�����x��ļн�
	}


	return 0;
}