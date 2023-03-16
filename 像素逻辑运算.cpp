#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/*
	�����߼����㣺

			bitwise_and(��):  (src1, src2, dst, mask), CV_8U������ֵ��0��255����ʱ�߼�������Ҫ������ֵת���ɶ����ƺ��ٽ��У�
			bitwise_or(��): (src1, src2, dst, mask), ͬ��
			bitwise_xor(���ͬ��
			bitwise_not(�ǣ���(src, dst, mask)  ֻ�����һ����ֵ���С�

	Ҫ��֤����ͼ�����֮��ĳߴ硢�������ͺ�ͨ������ͬ�����ͨ�������߼�����ʱ��ͬͨ��֮�����໥�����ġ�
*/
int main2(int argc, char *argv[])
{
	// ���������ڰ�ͼ��
	Mat img0, img1;
	img0= Mat::zeros(200, 200, CV_8UC1);
	img1 = Mat::zeros(200, 200, CV_8UC1);
	img0(Rect(50, 50, 100, 100)) = Scalar(255);
	img1(Rect(100, 100, 100, 100)) = Scalar(255);
	imshow("img0", img0);
	imshow("img1", img1);

	// �����߼�����
	Mat myAnd, myOr, myXor, myNot;
	bitwise_and(img0, img1, myAnd);
	bitwise_or(img0, img1, myOr);
	bitwise_xor(img0, img1, myXor);
	bitwise_not(img0, myNot);

	imshow("��", myAnd);
	imshow("��", myOr);
	imshow("���", myXor);
	imshow("��", myNot);
	waitKey();
	return 0;




}