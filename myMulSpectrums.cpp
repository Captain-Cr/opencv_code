#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	��������������Ҷ�任���о��

	����Ҷ�任���Խ���������ľ��ת��Ϊ��������ĸ���Ҷ�任����ĳ˻����������Ƶ��ĳ˻����ڿ���ľ������ͨ�����ַ�ʽ���Լ������߾���ļ����ٶȡ�

	����ԭ�ͣ� void cv::mulSpectrums(InputArray a, InputArray b, OutputArray c, int flag, bool conjB = false);
	  �ú����ܹ�ʵ��������ɢ����Ҷ�任��ľ����ÿ��Ԫ��֮��ĳ˷�����������ú�����ǰ�����������������Ҫ��˵ľ����������������������ͺͳߴ������ͬ������ͬʱΪ���������ʽ�ĵ�ͨ��Ƶ�׻���˫ͨ��Ƶ�ף���ֵ��ͨ��dft()��á�
	�����������Ǽ���Ƶ��˻�������������������������ͬ�ĳߴ���������͡��������������������̵Ĳ�����־�������һ������Ϊfalseʱ����ʾ�������֮��ĳ˷��������һ������Ϊtrueʱ����ʾǰһ�������Ԫ����ڶ�������ĸ���
	����ĳ˷���

	���뽲�⣺�ڸó����У�������Ҫ��ͼ��;������չ����ͬ�����Ÿ���Ҷ�任�ߴ磬֮��ֱ������ɢ����Ҷ�任�����Ա任������г˻������Գ˻����������ɢ����Ҷ�任����任����һ���õ����ս����
*/



int mainSpectrums(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼƬ\\1.jpg");
	resize(img, img, Size(512, 512));
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat grayfloat = Mat_<float>(gray);		// ����ͼ������Ϊfloat
	Mat kernel = (Mat_<float>(5, 5) << 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1);

	// �������ͼ��
	Mat result;
	int rwidth = abs(grayfloat.rows - kernel.rows) + 1;
	int rheight = abs(grayfloat.cols - kernel.cols) + 1;
	result.create(rwidth, rheight, grayfloat.type());

	// ����������ɢ����Ҷ�任�ߴ�
	int width = getOptimalDFTSize(grayfloat.cols + kernel.cols - 1);
	int height = getOptimalDFTSize(grayfloat.rows + kernel.rows - 1);

	// �ı�����ͼ��ߴ�
	Mat tempA;
	int A_T = 0;
	int A_B = width - grayfloat.rows;
	int A_L = 0;
	int A_R = height - grayfloat.cols;
	copyMakeBorder(grayfloat, tempA, 0, A_B, 0, A_R, BORDER_CONSTANT);

	// �ı��˲����ߴ�
	Mat tempB;
	int B_T = 0;
	int B_B = width - kernel.rows;
	int B_L = 0;
	int B_R = height - kernel.cols;
	copyMakeBorder(kernel, tempB, 0, B_B, 0, B_R, BORDER_CONSTANT);

	// �ֱ������ɢ����Ҷ�任
	dft(tempA, tempA, 0, grayfloat.rows);
	dft(tempB, tempB, 0, kernel.rows);

	// �������Ҷ�任�����ˣ�Ƶ����˵��ڿ�������
	mulSpectrums(tempA, tempB, tempA, DFT_COMPLEX_OUTPUT);

	// ����˵Ľ��������任
	// dft(tempA, tempA, DFT_INVERSE | DFT_SCALE, result.rows);
	idft(tempA, tempA, DFT_SCALE, result.rows);

	// ����任������й�һ��
	normalize(tempA, tempA, 0, 1, NORM_MINMAX);

	// ��ȡ���ֽ����Ϊ�˲����
	tempA(Rect(0, 0, result.cols, result.rows)).copyTo(result);

	// ��ʾ���
	imshow("ԭͼ��", gray);
	imshow("�˲����", result);
	waitKey(0);

}