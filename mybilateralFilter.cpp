#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	˫���˲��Ը�Ƶ�ʵĲ����ź���ƽ�������ã�ͬʱ�������ֵ�仯���źŲ���������ʵ�ֶԱ���ͼ���б�Ե��Ϣ�����á�
	˫���˲����������˲����Ľ�ϣ��ֱ��ǿ����źź�ֵ���źš�

	˫���˲�����	bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType);
	���У� d��ʾ�˲�������ÿ�����������ֱ����   sigmaColor: ��ɫ�ռ��˲����ı�׼��ֵ�������ֵԽ�󣬱�����������������Խ�����ɫ�������һ�𣬲����ϴ�İ������ɫ����
	sigmaSpace:  �ռ��������˲����ı�׼��ֵ��

	�˲�����ֱ��Խ���˲�Ч��Խ���ԣ��˲���ֱ����ͬʱ�� ��׼��ֵԽ���˲�Ч��Խ���ԣ�
*/

int mainaeeaf()
{
	Mat img1 = imread("D:\\ͼƬ\\1.jpg");
	Mat img2 = imread("D:\\ͼƬ\\lena.jpg");
	if (img1.empty() || img2.empty())
	{
		cout << "ͼƬ���ش���" << endl;
		return -1;
	}

	Mat result1, result2, result3, result4;

	// ��֤��ͬ�˲���ֱ�����˲�Ч��
	bilateralFilter(img1, result1, 9, 50, 25 / 2);		// ֱ��Ϊ9
	bilateralFilter(img1, result2, 25, 50, 25 / 2);		// ֱ��Ϊ25

	// ��֤��ͬ��׼��ֵ���˲�Ч��
	bilateralFilter(img2, result3, 9, 9, 9);			// ��ͬ��׼��ֵ
	bilateralFilter(img2, result4, 9, 200, 200);

	//��ʾԭͼ
	imshow("img1", img1);
	imshow("img2", img2);
	// ��ֱͬ���˲����
	imshow("result1", result1);
	imshow("result2", result2);
	imshow("result3", result3);
	imshow("result4", result4);

	waitKey();
	return 0;


}