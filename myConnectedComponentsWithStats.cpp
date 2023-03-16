/*

	connectedComponentsWithStats(InputArray img, OutputArray labels, OutputArray stats, OutputArray centroids, connectivity, ltype, ccltype)
		-img: ����ǲ�ͬ��ͨ��ĵ�ͨ��ͼ���������ͱ���ΪCV_8U
		-labels: ��ǲ�ͬ��ͨ�������ͼ��������ͼ�������ͬ�ĳߴ�
		-stats�� ���в�ͬ��ͨ��ͳ����Ϣ�ľ��󣬾������������ΪCV_32S�������е�i���Ǳ�ǩΪi����ͨ���ͳ������.���ͼ����N����ͨ����ô�ò�������ľ���ߴ�ΪN*5
		-centroids: ÿ����ͨ�����ĵ����꣬��������ΪCV_64F�����ͼ����N����ͨ����ô�ò����������״ΪN*2
		-connectivity: ͳ����ͨ��ʱʹ�õ��������࣬4����4����8����8����
		-ltype: ���ͼ����������ͣ�Ŀǰ֧��CV_32S��CV_16U������������
		-ccltype: �����ͨ��ʹ�õ��㷨���ͱ�־

	�ú����ܹ���ͼ���в�ͬ��ͨ���Ǳ�ǩ��ͬʱͳ��ÿ����ͨ�������λ�á����������С�������������Ϣ��
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int mainAAE(int argc, char* argv[])
{
	RNG rng(10086);   // ���������

	Mat img = imread("D:\\ͼƬ\\123.jpg");
	resize(img, img, Size(600, 800));
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// �Ҷ�ͼ+��ֵ��
	Mat gray, thresh;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 60, 255, THRESH_BINARY);
	// ����
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
	dilate(thresh, thresh, kernel, Point(-1, -1), 3);
	imshow("thresh", thresh);
	
	// ���������ɫ
	vector<Vec3b> colors;
	Mat out, stats, centeriods;
	// ͳ��ͼ���е���������
	int num = connectedComponentsWithStats(thresh, out, stats, centeriods, 8, CV_16U);
	for (int i = 0; i < num; i++)
	{
		Vec3b vec3b = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3b);
	}

	// �Բ�ͬ����ɫ��ǳ���ͬ����ͨ��
	Mat result = Mat::zeros(thresh.size(), thresh.type());
	int w = result.cols;
	int h = result.rows;
	for (int i = 1; i < num; i++)
	{
		// ����λ��
		int center_x = centeriods.at<double>(i, 0);		// ��i������������x����
		int center_y = centeriods.at<double>(i, 1);		// ��i������������y����

		// ���α߿�
		int x = stats.at<int>(i, CC_STAT_LEFT);			// ��i�����������������
		int y = stats.at<int>(i, CC_STAT_TOP);
		int w = stats.at<int>(i, CC_STAT_WIDTH);
		int h = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		// ���ĵ����
		circle(img, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
		// ��Ӿ���
		Rect rect(x, y, w, h);
		rectangle(img, rect, colors[i], 1, 8, 0);
		putText(img, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		cout << "number:" << i << ",area" << area << endl;
	}

	// ��ʾ���
	imshow("��Ǻ��ͼ��", img);
	
	
	
	
	
	waitKey();
	return 0;

}