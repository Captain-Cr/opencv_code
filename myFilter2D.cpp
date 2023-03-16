#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	filter2D��ͼ������ע�����ģ�岻�����ĶԳƣ���Ҫ�����ģ�������ת180��

	void filter2D(src,  dst, ddepth,  kernel, anchor,  delta, bordertype);
	�����ΪCV_32FC1���͵ľ���
	�����Ҫ�ò�ͬ�ľ��ģ��Բ�ͬͨ�����о�����㣬��Ҫ��ʹ��split()������ͼ����ͨ������֮�󵥶���ÿһ��ͨ���������㡣
	���ĵ�λ�ÿ����ھ��ģ��������ָ����  ���ƫֵ��ʾ�ھ������ļ������Ļ����ϼ���ƫֵdelta��Ϊ���ս����
*/

int mainAZ()
{
	// ���������
	uchar points[25] = { 1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25 };
	Mat img = Mat(5, 5, CV_8UC1, points);

	// ���ģ��
	Mat kernel = (Mat_<float>(3, 3) << 1, 2, 1, 2, 0, 2, 1, 2, 1);
	Mat kernel_norm = kernel / 12;				// ���ģ���һ��

	Mat result, result_norm;					// δ��һ���������͹�һ��������
	filter2D(img, result, CV_32F, kernel, Point(-1, -1), 2, BORDER_CONSTANT);
	filter2D(img, result_norm, CV_32F, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
	cout << "result:" << endl << result << endl;
	cout << "result_norm:" << endl << result_norm << endl;
	

	// ͼ����
	Mat image = imread("D:\\ͼƬ\\1.jpg",0);
	if (image.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}
	Mat filter;
	filter2D(image, filter, -1, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
	imshow("filter", filter);
	imshow("image", image);
	waitKey();
	return 0;

	

}