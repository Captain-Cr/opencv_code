#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	��������������ɽ�������
	int cvflann::rand();
	double cvflann::rand_double(double high = 1.0,  double low =0);
	int cvflann::rand_int(int height = RAND_MAX, int low =0);

	����0-100�������� int a= rand() % 100
*/


//������������
void saltAndPepper(Mat img, int n)
{
	// n����Ӷ��ٸ���
	for (int k = 0; k < n / 2; k++)
	{
		// ���ȷ��ͼ���е�λ��
		int i, j;
		j = std::rand() % img.rows;		// ȡ�����㣬��֤��ͼ���������
		i = std::rand() % img.cols;
		int write_black = std::rand() % 2;			// �ж��ǰ�ɫ�������Ǻ�ɫ�����ı���
		if (write_black == 0)			// ��Ӱ�ɫ����
		{
			if (img.type() == CV_8UC1)		// ����Ҷ�ͼ��
			{
				img.at<uchar>(j, i) = 255;		//��ɫ����
			}
		}
		else if (img.type() == CV_8UC3)
		{
			img.at<Vec3b>(j, i)[0] = saturate_cast<uchar>(rand() % 255);
			img.at<Vec3b>(j, i)[1] = saturate_cast<uchar>(rand() % 255);
			img.at<Vec3b>(j, i)[2] = saturate_cast<uchar>(rand() % 255);
		}
		else         // ��Ӻ�ɫ����
		{
			if (img.type() == CV_8UC1)
			{
				img.at<uchar>(j, i) = 0;
			}
			else if (img.type() == CV_8UC3)
			{
				img.at<Vec3b>(j, i)[0] = 0;			// Vec3bΪ3��ֵ����������
				img.at<Vec3b>(j, i)[1] = 0;
				img.at<Vec3b>(j, i)[2] = 0;			// [] ָ��ͨ����
			}
			
		}
	
	}
}

int mainzea()
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
	saltAndPepper(gray, 1000);
	saltAndPepper(image, 1000);
	imshow("�Ҷ�+����", gray);
	imshow("ԭͼ+����", image);
	waitKey();
	return 0;

}