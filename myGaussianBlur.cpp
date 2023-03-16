#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	��˹�˲���
	GaussianBlur(src, dst, ksize, sigmaX, sigmaY, borderType=BORDER_DEFAULT);
	getGaussianKernel(int ksize, double sigma, int ktype=CV_64F);   �������ɱ�׼�ߴ�ĸ�˹�˲���,Ҫ���ɶ�ά��˹�˲�����Ҫ��������getGaussianKernel()����X�����һά��˹�˲�����Y�����һά��˹�˲�����ˣ��õ����յĶ�ά��˹�˲�����

*/


int mainaff(int argc, char* argv[])
{
	Mat image = imread("D:\\ͼƬ\\1.jpg", 0);
	Mat gauss = imread("D:\\ͼƬ\\gauss.jpg");
	Mat salt = imread("D:\\ͼƬ\\salt.jpg");
	if (image.empty() || gauss.empty() || salt.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}


	Mat result;			// ��Ų����������˲����
	Mat result_gauss;
	Mat result_salt;

	// ����GaussianBlur()
	GaussianBlur(image, result, Size(3, 3), 10, 20);
	GaussianBlur(gauss, result_gauss, Size(3, 3), 10, 20);
	GaussianBlur(salt, result_salt, Size(3, 3), 10, 20);

	// ��ʾ
	imshow("image", result);
	imshow("gauss", result_gauss);
	imshow("salt", result_gauss);
	waitKey();

	Mat x, y;
	x = getGaussianKernel(3, -1, CV_64F);				// ��������ָ���ߴ�ĸ�˹�˲�����  �˲����ߴ�ͱ�׼ƫ����ڵĹ�ϵ
	y = getGaussianKernel(3, -1, CV_64F);				// ���ص���ksize * 1��Mat�����
	cout << x << "  " << y;
	Mat union_filter = x * y.t();							// �����˲���������X�����Y�����ϵ��˲������
	
	cout << union_filter << endl;

	return 0;


}