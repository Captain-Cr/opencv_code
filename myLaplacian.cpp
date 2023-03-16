#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Laplacian���Ӿ��и�����ͬ�Ե��ص㣬�ܹ������ⷽ��ı�Ե������ȡ��Laplacian������һ�ֶ��׵������ӣ����������У���Ҫ��ϸ�˹�˲�һ��ʹ�á�

	Laplacian(src, dst, ddepth, ksize, scale, delta, borderType);
	������
		ddepth: ���ͼ������ݷ�Χ,��Ҫʹ��CV_8U�������ͣ���Ϊ��ȡ��Ե��Ϣ�п���Ϊ������
		ksize:  ��ksize����1�� �ú���ͨ��sobel���Ӽ����ͼ��X�����Y����Ķ��׵���������������ĵ�����͵õ�Laplacian���ӡ�
				��ksize����1�� Laplacian�������£�  0     1     0
				                                    1    -4     1
													0     1     0

*/

int main21AD()
{
	Mat img = imread("D://ͼƬ//1.jpg");
	if (img.empty())
	{
		cout << "ͼ����ش���" << endl;
		return -1;
	}

	Mat result, result_g, result_G;

	// δ�����˲���ȡLaplacian��Ե
	Laplacian(img, result, CV_16S, 3, 1, 0);
	convertScaleAbs(result, result);

	// �˲�����ȡLaplacian��Ե
	GaussianBlur(img, result_g, Size(3, 3), 5, 0);		// ��˹�˲�
	Laplacian(result_g, result_G, CV_16S, 3, 1, 0);
	convertScaleAbs(result_G, result_G);

	// ��ʾͼ��
	imshow("result", result);
	imshow("result_G", result_G);
	waitKey();
	return 0;


}