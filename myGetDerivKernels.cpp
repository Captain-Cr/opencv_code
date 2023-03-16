#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	getDerivKernels(OutputArray kx, OutputArray ky, dx, dy, ksize, normalize=false, ktype=CV_32F);
	���У� kx�����˲���ϵ����������󣬳ߴ�ksize*1, ky:���˲���ϵ�����������
	dx: X�������Ľ״Σ�     dy��Y�������Ľ״�
	ksize�� �˲����Ĵ�С����FILTER_SCHARR, 1,3,5,7

	�ú�������������sobel���Ӻ�Scharr���ӣ�Ĭ������CV_32F
*/


int mainAAF()
{
	Mat sobel_x1, sobel_y1, sobel_x2, sobel_y2, sobel_x3, sobel_y3;			// ��ŷ����sobel����
	Mat scharr_x, scharr_y;			// ��ŷ����scharr����
	Mat sobelX1, sobelX2, sobelX3, scharrX;		// �����������

	// һ��x�����sobel����
	getDerivKernels(sobel_x1, sobel_y1, 1, 0, 3);
	sobel_x1 = sobel_x1.reshape(CV_8U, 1);
	cout << sobel_y1 << endl;
	sobelX1 = sobel_y1 * sobel_x1;			// ���������,  ����Ҫע����y * x ������ * �У�����˷�

	// ����x�����sobel����
	getDerivKernels(sobel_x2, sobel_y2, 2, 0, 5);
	sobel_x2 = sobel_x2.reshape(CV_8U, 1);
	sobelX2 = sobel_y2 * sobel_x2;			// ���������

	// ����x�����sobel����
	getDerivKernels(sobel_x3, sobel_y3, 3, 0, 7);
	sobel_x3 = sobel_x3.reshape(CV_8U, 1);
	sobelX3 =  sobel_y3 * sobel_x3;			// ���������

	// X����scharr����
	getDerivKernels(scharr_x, scharr_y, 1, 0, FILTER_SCHARR);
	scharr_x = scharr_x.reshape(CV_8U, 1);
	scharrX = scharr_y * scharr_x;			// ���������

	// ������
	cout << "x����һ��sobel����Ϊ��" << endl << sobelX1 << endl;
	cout << "x�������sobel����Ϊ��" << endl << sobelX2 << endl;
	cout << "x��������sobel����Ϊ��" << endl << sobelX3 << endl;

	cout << "X�����scharr���ӣ�" << endl << scharrX << endl;
	waitKey();
	return 0;





}