#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	ͨ���������ڻ�����trackbar�ı�ͼ�������
*/


int value;				// ����ֵ
Mat img, img2;			// ȫ��
void callback(int, void*);			// �����ص�����
char win[] = "�ı�����";




int mainA()
{
	img = imread("D:\\ͼƬ\\lena.jpg");
	if (img.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	
	namedWindow(win, WINDOW_AUTOSIZE);
	createTrackbar("val", win, &value, 600, callback);
	waitKey();
	return 0;

}

static void callback(int, void*)
{
	float a = value / 100.0;
	img2 = img * a;
	imshow(win, img2);
}