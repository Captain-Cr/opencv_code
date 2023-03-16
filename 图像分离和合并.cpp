/*
	ʵ��ͼ��Ķ�ͨ������ͺϲ�����
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main_124(int argc, char* argv[])
{
	Mat img = imread("E:\\data\\1.png");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
		return -1;
	}

	Mat HSV;								// HSVģ��
	cvtColor(img, HSV, COLOR_BGR2HSV);

	Mat imgs0, imgs1, imgs2;				// ���ڴ���������͵Ľ��
	Mat imgv0, imgv1, imgv2;				// ���ڴ��vector���͵Ľ��
	Mat result0, result1, result2;			// ��ͨ���ϲ��Ľ��


	// ������������Ķ�ͨ������ͺϲ�
	Mat imgs[3];							// ͼ������
	split(img, imgs);						// ���ͼ��
	imgs0 = imgs[0];
	imgs1 = imgs[1];
	imgs2 = imgs[2];
	imshow("BGR-Bͨ��", imgs0);				// ��ʾͼ��
	imshow("BGR-Gͨ��", imgs1);			
	imshow("BGR-Rͨ��", imgs2);
	
	
	imgs[2] = img;							// �������е�ͼ��ͨ������ɲ�һ��
	merge(imgs, 3, result0);				// �ϲ�ͼ��
	// imshow("result0",result0);			// imshow�����ʾ4��ͨ������˽����Image Watch�в鿴��  ����result��5��ͨ��
	Mat zero = Mat::zeros(img.rows, img.cols, CV_8UC1);
    // ����0�͵�2��ͨ����0
	imgs[0] = zero;
	imgs[2] = zero;
	merge(imgs, 3, result1);				// ���ڻ�ԭGͨ������ʵ������ϲ����Ϊ��ɫ
	imshow("result1", result1);

	// ����vector�����Ķ�ͨ��������ϲ�
	vector<Mat> imgv;
	split(HSV, imgv);
	imgv0 = imgv.at(0);					// ��ȡ��һ��ͨ��ͼƬ
	imgv1 = imgv.at(1);					// ��ȥ�ڶ���ͨ��ͼƬ
	imgv2 = imgv.at(2);
	imshow("HSV-Hͨ��", imgv0);				// ��ʾ�����Hͨ��������ֵ
	imshow("HSV-Sͨ��", imgv0);				// ��ʾ�����Sͨ��������ֵ
	imshow("HSV-Vͨ��", imgv0);				// ��ʾ�����Vͨ��������ֵ
	imgv.push_back(HSV);					// ��vector�е�ͼ��ͨ������ɲ�һ��
	merge(imgv, result2);					// �ϲ�ͼ��
	// imshow("result1",result1);			// imshow�����ʾ4��ͨ������˽����Image Watch�в鿴��  ����result��5��ͨ��
	
	
	
	
	
	
	
	waitKey();














}