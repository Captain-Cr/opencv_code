#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main12452(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	cout << "img: " << img.cols << " " << img.rows << endl;
	imshow("img", img);

	int row = (int)(img.rows / 2);
	int col = (int)(img.cols / 2);
	//�ü�ͼƬ
	Mat img0 = img(Rect(0, 0, col, row));
	Mat img1 = img(Rect(col, 0, col, row));
	Mat img2 = img(Rect(0, row, col, row));
	Mat img3 = img(Rect(col, row, col, row));
	imshow("img0", img0);
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	cout << "img0:" << img0.cols << "  " << img0.rows << endl;
	cout << "img1:" << img1.cols << "  " << img1.rows << endl;
	waitKey();




	// ��������ĺ���ƴ��
	Mat matArray[] = { img0, img1, img2, img3 };
	Mat vout, hout;
	hconcat(matArray, 2, hout);	
	cout << "ˮƽƴ��" << endl;
	imshow("ˮƽƴ��", hout);
	vconcat(matArray, 2, vout);
	cout << "��ֱƴ��" << endl;
	imshow("��ֱƴ��", vout);
	waitKey();



	// ͼ��ƴ��
	Mat hImg, vImg, hImg2;
	// ͼ��ˮƽ����
	hconcat(img0, img1, hImg);		// �Ƚ�������ͼˮƽƴ��
	hconcat(img2, img3, hImg2);
	vconcat(hImg, hImg2, vImg);     // Ȼ����д�ֱƴ�ӣ���ԭԭͼ
	imshow("��ԭԭͼ", vImg);
	waitKey();

	return 0;
}