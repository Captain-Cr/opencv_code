#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	�Զ����˲����� ֻ�����������һ�����ģ�壨�˲��������Ϳ���ʵ���Զ����˲���ʹ��filter2D����������
	�ɷ����ԣ�ָ�����ȶ�X(Y)�����˲��� �ٶ�Y(X)�����˲��Ľ��������������˲������Ϻ�������˲���ͬ�����������˲��������Ͼ��ǽ�����������˲�����ˣ��õ�һ�������˲�����
	�����˲�������X������˲���Ϊx=[x1,x2,x3], Y������˲���Ϊy=[y1, y2, y3]���������˲�Ϊxy = ([y1, y2, y3].t()) * [x1, x2, x3]
	
	�ڸ�˹�˲��У� getGaussianKernrel(ksize��sigma,ktype)�����ֱ�õ�X�����Y������˲���������x�����kernelΪ2,��ksize_x=2;  y�����kerenlΪ3����ksize_y=3;

	�������������˲���ʵ���˲�����sepFilter2D(src, dst, ddepth, kernelx, kernely, Point(-1, -1), delta, borderType); �ú������ɷ���������˲��������X�����Y������д���
	��filter2D()������ͬ��filter2D������Ҫͨ���˲����ĳߴ����ֲ�������x������y�������˲�����СΪK*1ʱ��Y���� 1*K��X����
*/

int mainafzz()
{
	float points[25] = { 1,2,3,4,5,
					  6, 7, 8, 9, 10,
					  11, 12, 13, 14, 15,
					  16, 17, 18, 19, 20,
					  21, 22, 23, 24,25 };
	Mat data(5, 5, CV_32FC1, points);

	// x����y����������˲����Ĺ���
	Mat a = (Mat_<float>(3, 1) << -1, -3, -1);			// y�����˲���
	Mat b = a.reshape(1, 1);							// ���Ըı�����ͨ�������ֿ��ԶԾ���Ԫ�ؽ������л�. cn��ʾͨ��������Ϊ0��ʾͨ�������䣬�����Ϊ���õ�ͨ������ rows��ʾ��������Ϊ0,���䣬�����Ϊ���õ�����
	Mat ab = a * b;										// �����˲���

	// ��֤��˹�˲��Ŀɷ�����
	Mat gaussian_x = getGaussianKernel(3, 1);				// ���ص���һ��ksize * 1��Mat����
	Mat gaussData, gaussData_XY;
	GaussianBlur(data, gaussData, Size(3, 3), 1, 1, BORDER_CONSTANT);
	sepFilter2D(data, gaussData_XY, -1, gaussian_x, gaussian_x, Point(-1, -1), 0, BORDER_CONSTANT);			// �����˲�

	// ������ָ�˹�˲��ļ�����
	cout << "gaussData= " << endl
		<< gaussData << endl;
	cout << "gaussianDataXY= " << endl
		<< gaussData_XY << endl;

	// �����˲��Ŀɷ�����
	Mat dataYX, dataY, dataXY, dataXY_sep;
	filter2D(data, dataY, -1, a, Point(-1, -1), 0, BORDER_CONSTANT);		// 1 (1)���ȶ�x�����˲�
	filter2D(dataY, dataYX, -1, b, Point(-1, -1), 0, BORDER_CONSTANT);		// 1 (2)���ٶ�y�����˲�
	filter2D(data, dataXY, -1, ab, Point(-1, -1), 0, BORDER_CONSTANT);		// 2 �����˲�
	sepFilter2D(data, dataXY_sep, -1, b, b, Point(-1, -1), 0, BORDER_CONSTANT);		// �����˲�
	// ����ɷ����˲��������˲��ļ�����
	cout << "dataY = " << endl
		<<dataY << endl;
	cout << "dataYX = " << endl
		<< dataXY << endl;
	cout << "dataXY = " << endl
		<< dataXY << endl;
	cout << "dataXY_sep = " << endl
		<< dataXY_sep;


	// ��ͼ��ķ������
	Mat img = imread("D:\\ͼƬ\\1.jpg", 0);
	if (img.empty())
	{
		cout << "ͼƬ���ش���" << endl;
		return -1;
	}
	Mat imgYX, imgY, imgXY, img_sep;
	filter2D(img, imgY, -1, a, Point(-1, -1), 0, BORDER_CONSTANT);			// 1 ��1���ȶ�x�����˲�
	filter2D(imgY, imgYX, -1, b, Point(-1, -1), 0, BORDER_CONSTANT);		// 1  (2) �ٶ�y�����˲�
	filter2D(img, imgXY, -1, ab, Point(-1, -1), 0, BORDER_CONSTANT);		// 2 �����˲�
	sepFilter2D(img, img_sep, -1, b, b, Point(-1, -1), 0, BORDER_CONSTANT);		// �����˲�
	imshow("img", img);
	imshow("imgY", imgY);
	imshow("imgYX", imgYX);
	imshow("imgXY", imgXY);
	waitKey();
	return 0;



}