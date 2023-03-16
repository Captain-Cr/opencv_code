#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	cv::RNG rng;
	rng.fill(mat, distType, a, b, bool saturateRange=false);
		mat: ���ڴ��������ľ���֧�ֵ���5ͨ���ľ���
		distType�� ������ֲ���ʽѡ���־��(RNG::UNIFORM,0;   RNG::NORMAL,1)
		a�� �ò�����ʾ��˹�ֲ��ľ�ֵ��
		b�� �ò�����ʾ��˹�ֲ��ı�׼�
		saturateRange: Ԥ���ͱ�־�������ھ��ȷֲ���
	
*/

int mainzzf()
{
	Mat gray = imread("D:\\ͼƬ\\1.jpg", 0);
	Mat image = imread("D:\\ͼƬ\\1.jpg");
	if (gray.empty() || image.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	imshow("gray", gray);
	imshow("img", image);

	// ������ԭʼͼ��ߴ硢�������ͺ�ͨ������ͬ�ľ���
	Mat lena_noise = Mat::zeros(image.rows, image.cols, image.type());
	Mat equalLena = Mat::zeros(gray.rows, gray.cols, gray.type());

	// ����һ��rng��
	RNG rng;
	rng.fill(lena_noise, RNG::NORMAL, 10, 20);		// ������ͨ���ĸ�˹�ֲ������
	rng.fill(equalLena, RNG::NORMAL, 15, 30);		// ���ɵ�ͨ���ĸ�˹�ֲ������
	imshow("��ͨ����˹����", lena_noise);
	imshow("��ͨ����˹����", equalLena);		
	
	image = image + lena_noise;				// �ڲ�ɫͼ�������
	gray = gray + equalLena;				// �ڻҶ�ͼ�������
	imshow("��ɫͼ��Ӹ�˹����", image);
	imshow("�ڻҶ�ͼ��Ӹ�˹����", gray);
	imwrite("E:\\data\\gauss.jpg", image);
	waitKey();
	return 0;
	

}