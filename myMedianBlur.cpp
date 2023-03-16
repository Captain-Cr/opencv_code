#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	��ֵ�˲��㷨��
		1���Ѵ��ڷŵ�Ԫ���ϣ�
		2��ȡ�������е�Ԫ�أ�
		3���������е�Ԫ������
		4��ѡ����ЩԪ�ص���ֵ��
*/


void myMedianBlur()
{
	// �����˲��Ĵ���Ϊ3x3
	Mat image = imread("D:\\ͼƬ\\1.jpg", 0);
	Mat salt = imread("D:\\ͼƬ\\salt.jpg");

	/*uchar points[25] = { 1,2,3,4,5,
						6,7,8,9,10,
						11, 12, 13, 14,15,
						16, 17,18, 19, 20,
						21,22, 23, 24, 25 };
	Mat image(5, 5, CV_8UC1, points);*/

	if (image.empty())
	{
		cout << "ͼƬ���ش���" << endl;
	}

	Mat img;		// �������opencv��medienBlur����
	image.copyTo(img);
	Mat result;			// ���������ֵ�˲���Ľ��
	vector<int> grayv(9);		// 3x3���˲�ģ��
	for (int i = 1; i < image.rows - 1; i++)			// Ҫ��һ������
	{
		uchar *preptr = image.ptr(i - 1);			// (i,j)��Ҫ�ı�����������
		uchar *ptr = image.ptr(i);
		uchar *nextptr = image.ptr(i + 1);
		uchar *imgptr = img.ptr(i);		// ���������ֵ�˲���ͼƬ����ָ��

		for (int j = 1; j < image.cols - 1; j++)
		{
			grayv[0] = (preptr[j - 1]);			// �˲�ģ��ĵ�һ��Ԫ�أ�preptr�� ��һ�е�ָ��
			grayv[1] = (preptr[j]);
			grayv[2] = (preptr[j + 1]);
			grayv[3] = (ptr[j - 1]);			// �˲�ģ��ӵ�ǰ�п�ʼ��ptr����ǰ�е�ָ��
			grayv[4] = (ptr[j]);
			grayv[5] = (ptr[j + 1]);
			grayv[6] = (nextptr[j - 1]);		// nextptr�� ��һ�е�ָ��
			grayv[7] = (nextptr[j]);
			grayv[8] = (nextptr[j + 1]);

			sort(grayv.begin(), grayv.end());		// ��vector���������õ�����
			imgptr[j] = int(grayv[4]);			// ����ǰ��������Ϊ��ֵ��ֵ

		}
	}
	//cout << img << endl;

	medianBlur(image, result, 3);		// ����opencv��ֵ�˲�����

	Mat salt_blur;
	medianBlur(salt, salt_blur, 3);
	//cout << result << endl;

	imshow("ԭͼ", image);
	imshow("��ֵ�˲���", img);
	imshow("opencv�Դ��˲�", result);

	imshow("����", salt);
	imshow("��ֵ�˲�ȥ������", salt_blur);
	waitKey(0);
	
}












int main_fae()
{
	myMedianBlur();
	return 0;
}