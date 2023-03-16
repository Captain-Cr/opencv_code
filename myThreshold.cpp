#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main3(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
	}

	Mat img_b, img_b_v;		// ���������ɫͼ���ֵ��
	threshold(img, img_b, 125, 255, THRESH_BINARY);
	threshold(img, img_b_v, 125, 255, THRESH_BINARY_INV);
	imshow("img_b", img_b);
	imshow("img_b_v", img_b_v);

	// ת��Ϊ�Ҷ�ͼ
	Mat gray, gray_b, gray_b_v, gray_t, gray_t_v, gray_trunc;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);

	// �Ҷ�ͼbinary��ֵ��
	threshold(gray, gray_b, 125, 255, THRESH_BINARY);
	threshold(gray, gray_b_v, 125, 255, THRESH_BINARY_INV);
	imshow("gray_b", gray_b);
	imshow("gray_b_v", gray_b_v);

	// �Ҷ�ͼtozero�任
	threshold(gray, gray_t, 125, 255, THRESH_TOZERO);
	threshold(gray, gray_t_v, 125, 255, THRESH_TOZERO_INV);
	imshow("gray_t", gray_t);
	imshow("gray_t_v", gray_t_v);

	// �Ҷ�ͼtrunc�任
	threshold(gray, gray_trunc, 125, 255, THRESH_TRUNC);
	imshow("gray_trunc", gray_trunc);


	// �Ҷ�ͼ���򷨺������ͷ� ��������ȡ��ֵ��
	Mat img_thr_o, img_thr_t;
	threshold(gray, img_thr_o, 0, 255, THRESH_OTSU | THRESH_BINARY);		// �����ֵ
	threshold(gray, img_thr_t, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);		// �����η� TRIANGLE
	imshow("img_thr_o", img_thr_o);
	imshow("img_thr_t", img_thr_t);


	// �Ҷ�ͼ������Ӧ��ֵ��
	Mat adaptive_mean, adaptive_gauss;
	adaptiveThreshold(gray, adaptive_mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 55, 0);
	adaptiveThreshold(gray, adaptive_gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 55, 0);

	imshow("adaptive_mean", adaptive_mean);
	imshow("adaptive_gauss", adaptive_gauss);
	waitKey();
	return 0;

}