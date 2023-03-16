#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	��ͼ����ǳ����
*/

int main213(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	Mat noobcv = imread("E:\\cat_and_dog.jpg");

	if (img.empty() || noobcv.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
		return -1;
	}
	
	Mat Roi1, Roi2, Roi2_copy, mask, img2, img_copy, img_copy2;
	resize(noobcv, mask, Size(200, 200));		// mask��noobcvͼƬ������
	img2 = img;		// ǳ����
	

	// ��������ַ���
	img.copyTo(img_copy2);
	copyTo(img, img_copy, img);

	// ������ͼ�н�ȡRoi�ķ�ʽ
	Roi1 = img(Rect(206, 206, 200, 200));
	Roi2 = img(Range(300, 500), Range(300, 500));

	img(Range(300, 500), Range(300, 500)).copyTo(Roi2_copy);		// ���
	mask.copyTo(Roi1);				// ��ͼ���м��벿��ͼ��

	imshow("����noobcv��ͼ��", img);
	imshow("ROi��ROi2��Ӱ��", Roi2);
	imshow("�����Roi2_copy", Roi2_copy);
	circle(img, Point(300, 300), 20, Scalar(0, 0, 255), -1);		//����һ��Բ
	imshow("�����img2", img2);
	imshow("�����img_copy", img_copy);
	imshow("�����img_copy2", img_copy2);
	imshow("��Բ��roi��Ӱ��", Roi1);
	waitKey();
	return 0;













}
