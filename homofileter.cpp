#include <iostream>
#include<time.h>
#include <math.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	����������ø�˹�˲����ݺ��������а�����˹��ָ�����˲������ڻ����Ӿ�����111ҳ��������̬ͬ�˲���
	˼�룺����˲�����Ҫ�Ե�Ƶ��������ѹ�ƣ��Խ��Ͷ�̬��Χ��ͬʱҪ�Ը�Ƶ������ߣ�����ǿͼ��Աȶ�
	��������ʹ��Y����,������UV��������̬ͬ�˲�������������ǲ�ɫͼ��
*/


Mat HomoFilter(Mat srcImg);				// ̬ͬ�˲�����
Mat HomoFilter2(Mat inputImg);
Mat HomoFilter3(Mat inputImg);

int mainfaef(int argc, char* argv[])
{
	// ��ȡͼ��ת��ΪYUV��ʽ�ͽ�YUV����������ֿ�
	Mat img = imread("F:\\camera\\resize\\trainResize\\13.bmp");
	// Mat img = imread("F:\\1.jpeg");
	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);			// �������Ĳ�ɫͼ��
	if (!img.data)
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}
	Mat img1;
	img.copyTo(img1);
	cvtColor(img, img, COLOR_BGR2YUV);
	vector<Mat> yuv;
	split(img, yuv);
	Mat owY = yuv[0];			// ��ȡy����

	// ��Y��������̬ͬ�˲�
	Mat newY = HomoFilter(owY);
	imshow("srcY", owY);
	imshow("newY", newY);

	// �ϲ��ָ���ɫͼ��
	Mat tempY(img.rows, img.cols, CV_8UC1);		// ��Ϊ�����Y�п��ܳߴ�������1,����Ҫһ����ʱMat���»���,��֤y�Ĵ�С��ԭ����һ��
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			tempY.at<uchar>(i, j) = newY.at<uchar>(i, j);
		}
	}
	yuv[0] = tempY;
	merge(yuv, dst);
	cvtColor(dst, dst, COLOR_YUV2BGR);			//	���bgrͼ��
	imshow("src_bgr", img1);
	imshow("dst", dst);
	waitKey();




}



Mat HomoFilter(Mat inputImg)
{
	// ̬ͬ�˲�ʵ�ַ���
	Mat homoImg = inputImg.clone();			// �˲������ͼ�񣬽������
	Mat orginalImg = inputImg.clone();		// �˲�ǰ��ͼ��

	// ת����������
	homoImg.convertTo(homoImg, CV_64FC1);

	// ����ͼ�������߽�
	int rows = homoImg.rows;		// ��
	int cols = homoImg.cols;		// ��
	int m = rows % 2 == 1 ? rows + 1 : rows;	// �ж�ͼ�����������������ż���������������+1
	int n = cols % 2 == 1 ? cols + 1 : cols;
	copyMakeBorder(homoImg, homoImg, 0, m - rows, 0, n - cols, BORDER_CONSTANT, Scalar::all(0));	// �����߽�
	rows = homoImg.rows;			// ����ͼƬ������
	cols = homoImg.cols;			// ����ͼƬ������
	Mat homo_result_Img(rows, cols, CV_64FC1);			//�����������ͼ��


	// 1����ԭͼ��f(x,y) = i(x, y) * r(x,y)ȡ����.(ÿ�����أ�
	for (int i = 0; i < rows; i++) {
		double* srcImgPtr = homoImg.ptr<double>(i);			// ԭʼͼ���е�ָ��
		double* logImgPtr = homoImg.ptr<double>(i);			// ����ͼ���е�ָ��
		for (int j = 0; j < cols; j++) {
			logImgPtr[j] = log(srcImgPtr[j] + 0.0001);	
		}
	}


	// 2����ɢ����Ҷ�任��or ��ɢ���ұ任���� Ƶ����
	Mat mat_dft = Mat::zeros(Size(rows, cols), CV_64FC1);
	// dft(homoImg, mat_dft);
	dct(homoImg, mat_dft);

	// 3������˲������ݺ���H(u,v), ����˲�����Ҫ�Ե�Ƶ��������ѹ�ƣ��Խ��Ͷ�̬��Χ��ͬʱҪ�Ը�Ƶ������ߣ�����ǿͼ��Աȶ�
	// �����Ǹ�˹̬ͬ�˲���
	Mat H_u_v = Mat::zeros(rows, cols, CV_64FC1);		// �˲�Ƶ��
	double gammaH = 3;			// ��Ƶ����
	double gammaL = 0.1;		// ��Ƶ����
	double C = 0.6;				// б���񻯳����� б��
	//double D0 = pow((homoImg.rows / 2), 2.0) + pow((homoImg.cols / 2), 2.0);		// ��ֹƵ�ʣ�ֵԽ��Խ��
	double D0 = (homoImg.rows / 2) * (homoImg.rows / 2) + (homoImg.cols / 2) * (homoImg.cols / 2);//��ֹƵ��;
	//double D0 = 200;						//5 - 200  ��ֹƵ�� Խ��Խ��
	double D = 0;
	for (int i = 0; i < rows; i++) {
		double* data_H_u_v = H_u_v.ptr<double>(i);			// �˲�Ƶ�׵���ָ��
		for (int j = 0; j < cols; j++) {
			D = pow((i - homoImg.rows / 2), 2.0) + pow((j - homoImg.cols / 2), 2.0);
			data_H_u_v[j] = (gammaH - gammaL) * (1 - exp(-C * (D / D0))) + gammaL;		// ����ʽ
		}
	}
	H_u_v.ptr<double>(0)[0] = 1.1;			// ����һ�����ظ�ֵ

	// 4���˲�Ƶ�׺�Ƶ��ͼ���Ӧλ�����(mul)�õ�Ƶ���˲�ͼƬ
	mat_dft = mat_dft.mul(H_u_v);			

	// 5��������Ҷ�任��or ����ɢ���ұ任���� ͼ����
	// idft(mat_dft, homo_result_Img);
	idct(mat_dft, homo_result_Img);

	// 6��������, �õ�ԭʼͼ��
	for (int i = 0; i < rows; i++) {
		double* srcdata = homo_result_Img.ptr<double>(i);		// ���任��ͼ�����ָ��
		double* dstdata = homo_result_Img.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			dstdata[j] = exp(srcdata[j]);					// ��ÿ�����ط�����
		}
	}
	homo_result_Img.convertTo(homo_result_Img, CV_8UC1);		// ת��ͼ���ʽ
	return homo_result_Img;

}



Mat HomoFilter2(Mat inputImg)
{
	// ̬ͬ�˲�ʵ�ַ���,������˹̬ͬ�˲���
	Mat homoImg = inputImg.clone();			// �˲������ͼ�񣬽������
	Mat orginalImg = inputImg.clone();		// �˲�ǰ��ͼ��

	// ת����������
	homoImg.convertTo(homoImg, CV_64FC1);

	// ����ͼ�������߽�
	int rows = homoImg.rows;		// ��
	int cols = homoImg.cols;		// ��
	int m = rows % 2 == 1 ? rows + 1 : rows;	// �ж�ͼ�����������������ż���������������+1
	int n = cols % 2 == 1 ? cols + 1 : cols;
	copyMakeBorder(homoImg, homoImg, 0, m - rows, 0, n - cols, BORDER_CONSTANT, Scalar::all(0));	// �����߽�
	rows = homoImg.rows;			// ����ͼƬ������
	cols = homoImg.cols;			// ����ͼƬ������
	Mat homo_result_Img(rows, cols, CV_64FC1);			//�����������ͼ��


	// 1����ԭͼ��f(x,y) = i(x, y) * r(x,y)ȡ����.(ÿ�����أ�
	for (int i = 0; i < rows; i++) {
		double* srcImgPtr = homoImg.ptr<double>(i);			// ԭʼͼ���е�ָ��
		double* logImgPtr = homoImg.ptr<double>(i);			// ����ͼ���е�ָ��
		for (int j = 0; j < cols; j++) {
			logImgPtr[j] = log(srcImgPtr[j] + 0.0001);
		}
	}


	// 2����ɢ����Ҷ�任��or ��ɢ���ұ任���� Ƶ����
	Mat mat_dft = Mat::zeros(Size(rows, cols), CV_64FC1);
	// dft(homoImg, mat_dft);
	dct(homoImg, mat_dft);

	// 3������˲������ݺ���H(u,v), ����˲�����Ҫ�Ե�Ƶ��������ѹ�ƣ��Խ��Ͷ�̬��Χ��ͬʱҪ�Ը�Ƶ������ߣ�����ǿͼ��Աȶ�
	// �����ǰ�����˹̬ͬ�˲���
	Mat H_u_v = Mat::zeros(rows, cols, CV_64FC1);		// �˲�Ƶ��
	double gammaH = 3;			// ��Ƶ����
	double gammaL = 0.1;		// ��Ƶ����
	double C = 0.5;				// б���񻯳����� б��
	//double D0 = pow((homoImg.rows / 2), 2.0) + pow((homoImg.cols / 2), 2.0);		// ��ֹƵ�ʣ�ֵԽ��Խ��
	double D0 = (homoImg.rows / 2) * (homoImg.rows / 2) + (homoImg.cols / 2) * (homoImg.cols / 2);//��ֹƵ��;
	//double D0 = 200;						//5 - 200  ��ֹƵ�� Խ��Խ��
	double D = 0;
	for (int i = 0; i < rows; i++) {
		double* data_H_u_v = H_u_v.ptr<double>(i);			// �˲�Ƶ�׵���ָ��
		for (int j = 0; j < cols; j++) {
			D = pow((i - homoImg.rows / 2), 2.0) + pow((j - homoImg.cols / 2), 2.0);
			data_H_u_v[j] = (gammaH - gammaL) * (1 /(1 + D0 / (C * D))) + gammaL;		// ����ʽ
		}
	}
	H_u_v.ptr<double>(0)[0] = 1.1;			// ����һ�����ظ�ֵ

	// 4���˲�Ƶ�׺�Ƶ��ͼ���Ӧλ�����(mul)�õ�Ƶ���˲�ͼƬ
	mat_dft = mat_dft.mul(H_u_v);

	// 5��������Ҷ�任��or ����ɢ���ұ任���� ͼ����
	// idft(mat_dft, homo_result_Img);
	idct(mat_dft, homo_result_Img);

	// 6��������, �õ�ԭʼͼ��
	for (int i = 0; i < rows; i++) {
		double* srcdata = homo_result_Img.ptr<double>(i);		// ���任��ͼ�����ָ��
		double* dstdata = homo_result_Img.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			dstdata[j] = exp(srcdata[j]);					// ��ÿ�����ط�����
		}
	}
	homo_result_Img.convertTo(homo_result_Img, CV_8UC1);		// ת��ͼ���ʽ
	return homo_result_Img;

}



Mat HomoFilter3(Mat inputImg)
{
	// ̬ͬ�˲�ʵ�ַ���,������˹̬ͬ�˲���
	Mat homoImg = inputImg.clone();			// �˲������ͼ�񣬽������
	Mat orginalImg = inputImg.clone();		// �˲�ǰ��ͼ��

	// ת����������
	homoImg.convertTo(homoImg, CV_64FC1);

	// ����ͼ�������߽�
	int rows = homoImg.rows;		// ��
	int cols = homoImg.cols;		// ��
	int m = rows % 2 == 1 ? rows + 1 : rows;	// �ж�ͼ�����������������ż���������������+1
	int n = cols % 2 == 1 ? cols + 1 : cols;
	copyMakeBorder(homoImg, homoImg, 0, m - rows, 0, n - cols, BORDER_CONSTANT, Scalar::all(0));	// �����߽�
	rows = homoImg.rows;			// ����ͼƬ������
	cols = homoImg.cols;			// ����ͼƬ������
	Mat homo_result_Img(rows, cols, CV_64FC1);			//�����������ͼ��


	// 1����ԭͼ��f(x,y) = i(x, y) * r(x,y)ȡ����.(ÿ�����أ�
	for (int i = 0; i < rows; i++) {
		double* srcImgPtr = homoImg.ptr<double>(i);			// ԭʼͼ���е�ָ��
		double* logImgPtr = homoImg.ptr<double>(i);			// ����ͼ���е�ָ��
		for (int j = 0; j < cols; j++) {
			logImgPtr[j] = log(srcImgPtr[j] + 0.0001);
		}
	}


	// 2����ɢ����Ҷ�任��or ��ɢ���ұ任���� Ƶ����
	Mat mat_dft = Mat::zeros(Size(rows, cols), CV_64FC1);
	// dft(homoImg, mat_dft);
	dct(homoImg, mat_dft);

	// 3������˲������ݺ���H(u,v), ����˲�����Ҫ�Ե�Ƶ��������ѹ�ƣ��Խ��Ͷ�̬��Χ��ͬʱҪ�Ը�Ƶ������ߣ�����ǿͼ��Աȶ�
	// �����ǰ�����˹̬ͬ�˲���
	Mat H_u_v = Mat::zeros(rows, cols, CV_64FC1);		// �˲�Ƶ��
	double gammaH = 1.7;			// ��Ƶ����
	double gammaL = 0.5;		// ��Ƶ����
	double C = 1.2;				// б���񻯳����� б��
	//double D0 = pow((homoImg.rows / 2), 2.0) + pow((homoImg.cols / 2), 2.0);		// ��ֹƵ�ʣ�ֵԽ��Խ��
	//double D0 = (homoImg.rows / 2) * (homoImg.rows / 2) + (homoImg.cols / 2) * (homoImg.cols / 2);//��ֹƵ��;
	double D0 = 5;						//5 - 200  ��ֹƵ�� Խ��Խ��
	double D = 0;
	double alpha = 0.001;
	for (int i = 0; i < rows; i++) {
		double* data_H_u_v = H_u_v.ptr<double>(i);			// �˲�Ƶ�׵���ָ��
		for (int j = 0; j < cols; j++) {
			D = pow((i - homoImg.rows / 2), 2.0) + pow((j - homoImg.cols / 2), 2.0);
			//data_H_u_v[j] = (gammaH - gammaL) * (1 / (1 + D0 / (C * D))) + gammaL;		// ����ʽ
			data_H_u_v[j] = (gammaH - gammaL) * exp(exp(1 - alpha * D)) + gammaL;
		}
	}
	//H_u_v.ptr<double>(0)[0] = 1.1;			// ����һ�����ظ�ֵ

	// 4���˲�Ƶ�׺�Ƶ��ͼ���Ӧλ�����(mul)�õ�Ƶ���˲�ͼƬ
	mat_dft = mat_dft.mul(H_u_v);

	// 5��������Ҷ�任��or ����ɢ���ұ任���� ͼ����
	// idft(mat_dft, homo_result_Img);
	idct(mat_dft, homo_result_Img);

	// 6��������, �õ�ԭʼͼ��
	for (int i = 0; i < rows; i++) {
		double* srcdata = homo_result_Img.ptr<double>(i);		// ���任��ͼ�����ָ��
		double* dstdata = homo_result_Img.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			dstdata[j] = exp(srcdata[j]);					// ��ÿ�����ط�����
		}
	}
	homo_result_Img.convertTo(homo_result_Img, CV_8UC1);		// ת��ͼ���ʽ
	return homo_result_Img;

}