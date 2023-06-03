#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	�ҵ�ͼ���еı궨�����̱궨��Ľǵ�
*/

int main(int argc, char* argv[])
{
	Mat img1 = imread("D:\\ͼ������ͼƬ\\images\\chessboard.png");
	Mat img2 = imread("D:\\ͼ������ͼƬ\\images\\1.png");
	
	if (img1.empty() || img2.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}
	Mat gray1, gray2;
	cvtColor(img1, gray1, COLOR_BGR2GRAY);
	cvtColor(img2, gray2, COLOR_BGR2GRAY);

	// �ж�ͼ���Ƿ�������̱궨��
	Size board_size1 = Size(7, 7);			// ���α궨���ڽǵ���Ŀ���У��У�
	Size board_size2 = Size(7, 7);			// Բ�α궨��Բ����Ŀ���У��У�

	
	// ���ǵ�
	vector<Point2f> img1_points, img2_points;
	int ret1 = findChessboardCorners(gray1, board_size1, img1_points);			// ���㷽��궨��ǵ�
	int ret2 = findCirclesGrid(gray2, board_size2, img2_points);				// ����Բ�α궨��ǵ�
	if (ret1 == 0 || ret2 == 0)
	{
		cout << "���α궨���ж������������룺" << ret1 << endl;
		cout << "Բ�α궨���ж�������������:" << ret2 << endl;
	}

	// ϸ���ǵ�����
	find4QuadCornerSubpix(gray1, img1_points, Size(5, 5));			// ϸ������궨��ǵ�����
	find4QuadCornerSubpix(gray2, img2_points, Size(5, 5));			// ϸ��Բ�α궨��ǵ�����

	// ���ƽǵ�������
	drawChessboardCorners(img1, board_size1, img1_points, true);
	drawChessboardCorners(img2, board_size2, img2_points, true);

	// ��ʾ���
	imshow("���α궨��ǵ�������", img1);
	imshow("Բ�α궨��ǵ�������", img2);
	waitKey();
	destroyAllWindows();
	return 0;


}