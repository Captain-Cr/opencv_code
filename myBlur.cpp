#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	��ֵ�˲���  cv::blur(src, dst, ksize, Point(-1,-1), borderType=BORDER_DEFAULT);
	�����˲� �� cv::boxFilter(src, dst, ddepth, ksize, Point(-1, -1), normalize, borderType);		# ddepth: ���ͼ����������ͣ���ȣ�CV_8U�� ����ֵΪ-1ʱ�����ͼ������������Զ�ѡ��
	�����˲��Ǿ�ֵ�˲���һ����ʽ���ھ�ֵ�˲��У����˲�����������ֵ��ͺ��ƽ��ֵ��Ϊ�˲������������˲�Ҳ�����˲�����������ֵ�ĺͣ����Ƿ����˲�����ѡ�񲻽��й�һ�����ǽ���������ֵ�ĺ���Ϊ�˲��������������������ֵ��ƽ��ֵ��
	
	���ṩ�� cv::sqrBoxFilter(ͬboxFilter): ʵ�ֶ��˲�����ÿ������ֵ��ƽ����ͣ�֮������������ѡ���Ƿ���й�һ��������




*/




int mainzaf()
{

	Mat gray = imread("D:\\ͼƬ\\1.jpg", 0);
	Mat image = imread("D:\\ͼƬ\\1.jpg");
	if (gray.empty() || image.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	// ��Ӹ�˹����
	RNG rng;
	Mat gauss;
	Mat gauss_noise = Mat::zeros(gray.rows, gray.cols, gray.type());;
	rng.fill(gauss_noise, RNG::NORMAL, 10, 30);			
	gauss = gray + gauss_noise;				// ��Ӹ�˹����
	imshow("gray", gray);
	imshow("gauss", gauss);


	// ��ӽ�������(���Ե�ͨ����
	Mat salt;
	copyTo(gray, salt,Mat());
	for (int i = 0; i < 2000; i++)
	{
		// ���ȷ��λ��
		int x = std::rand() % gray.rows;
		int y = std::rand() % gray.cols;
		int write_black = std::rand() % 2;
		
		if (write_black == 0)
		{
			salt.at<uchar>(x, y) = 255;
		}
		else
		{
			salt.at<uchar>(x, y) = 0;
		}
	}
	imshow("salt", salt);

	imwrite("D:\\ͼƬ\\gauss.jpg", gauss);
	imwrite("D:\\ͼƬ\\salt.jpg", salt);


	// ��ֵ�˲�
	Mat result, result_gauss, result_salt;			// ����˲����ͼ
	blur(gray, result, Size(5,5));
	blur(gauss, result_gauss, Size(5, 5));
	blur(salt, result_salt, Size(5, 5));

	imshow("�Ҷ�ͼ�˲�", gray);
	imshow("��˹�����˲�", gauss);
	imshow("���������˲�", result_salt);

	



	// �����˲�
	// ��֤�����˲��㷨�����ݾ���
	float points[25] = { 1,2,3,4,5,
						6,7,8,9,10,
						11, 12, 13, 14,15,
						16, 17,18, 19, 20,
						21,22, 23, 24, 25 };
	Mat data(5, 5, CV_32FC1, points);
	// ��CV_8U����ת����CV_32F����
	Mat Lena_copy, Lena_32F;
	gray.copyTo(Lena_copy, Mat());
	Lena_copy.convertTo(Lena_32F, CV_32F, 1.0 / 255);
	Mat resultNorm, result2, dataSqrNorm, dataSqr, equalLena_32FSqr;
	// �����˲�����boxFilter() �� sqrBoxFilter()
	boxFilter(Lena_copy, resultNorm, -1, Size(3, 3), Point(-1, -1), true);			// ���й�һ��
	boxFilter(Lena_copy, result2, -1, Size(3, 3), Point(-1, -1), false);				// �����й�һ��
	sqrBoxFilter(data, dataSqrNorm, -1, Size(3, 3), Point(-1, -1), true, BORDER_CONSTANT);			// ���й�һ��
	sqrBoxFilter(data, dataSqr, -1, Size(3, 3), Point(-1, -1), false, BORDER_CONSTANT);				// �����й�һ��
	sqrBoxFilter(Lena_32F, equalLena_32FSqr, -1, Size(3, 3), Point(-1, -1), true, BORDER_CONSTANT);
	// ��ʾ������
	imshow("resultNorm", resultNorm);
	imshow("result", result2);
	imshow("equalLena_32FSqr", equalLena_32FSqr);
	
	waitKey();
	return 0;
	
}