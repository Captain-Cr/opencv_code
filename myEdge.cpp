#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace  cv;



/*
	ͼ���Ե��ͼ�������ػҶ�ֵͻȻ�����仯�����򡣺���ֵ�ı仯���ƿ����ú����ĵ�������������ֵ���󣬵���Ҳ��� ����ֵ��С������Ҳ��С�� ��˿���ͨ��Ѱ�ҵ���ֵ�ϴ������Ѱ�Һ�����ͻȻ�仯������

	ͼ������ɢ���źţ���˿������ٽ����������ز�ֵ����ʾ���ػҶ�ֵ�����ĵ�����  df(x, y) / dx = f(x, y) - f(x-1, y);			��x�᷽���󵼶�Ӧ���˲���Ϊ[-1, 1]

	�����Ҫ��ʾĳ�����س����ݶȣ���ӽ��ķ�ʽ����ȡǰһ�����غͺ�һ�����صĲ�ֵ��  �� df(x, y) / dx = f(x+1, y) - f(x-1, y) / 2   ��Ӧ���˲���Ϊ[-0.5, 0, 0.5]

	����45�㷽����ݶȿ�����  XY = 1  0                  YX = 0   1
                                   0  -1   	                  -1  0


	����������������ݵľ���ֵ��    convertScaleAbs(src, dst, alpha=1,  beta=0);
	�ú���������ȡ�������������ݵľ���ֵ�������������ĸ�����Ϊ���Ե����ź������ϵ�ƫ�ơ�  ���㹫ʽ��  dst(I) = |src(I)  * alpha + beta

	������ȡ��Ե�Ľ���п����Ǹ����� ����˲����ͼ���������Ͳ�Ҫ��-1�� ��Ӧ�ø�ΪCV_16S
*/

int mainafvx()
{
	// ������Ե����˲���
	Mat kernel1 = (Mat_<float>(1, 2) << 1, -1);						// x����ı�Ե����˲���
	Mat kernel2 = (Mat_<float>(1, 3) << 1, 0, -1);					// x����ı�Ե����˲���
	Mat kernel3 = (Mat_<float>(3, 1) << 1, 0, -1);					// x����ı�Ե����˲���

	Mat kernelXY = (Mat_<float>(2, 2) << 1, 0, 0, -1);					// �����ϵ����±�Ե����˲���
	Mat kernelYX = (Mat_<float>(2, 2) << 0, -1, 1, 0);					// �����ϵ����±�Ե����˲���

	// ��ȡͼ�񣬺ڰ�ͼ���Ե�������Ϊ����
	Mat img = imread("D:\\ͼƬ\\1.jpg", 0);
	if (img.empty())
	{
		cout << "ͼƬ���ش���" << endl;
		return -1;
	}
	Mat result1, result2, result3, result4, result5, result6;

	// ���ͼ���Ե
	// ��[1, -1]���ˮƽ�����Ե
	filter2D(img, result1, CV_16S, kernel1);			// ע������Ҫ��CV_16S����
	convertScaleAbs(result1, result1);				

	// ��[1, 0, -1]���ˮƽ�����Ե
	filter2D(img, result2, CV_16S, kernel2);			// ע������Ҫ��CV_16S����
	convertScaleAbs(result2, result2);

	// ��[1, 0, -1]��ⴹֱ�����Ե
	filter2D(img, result3, CV_16S, kernel3);			// ע������Ҫ��CV_16S����
	convertScaleAbs(result3, result3);

	// ��������ϵ����·���ı�Ե
	filter2D(img, result4, CV_16S, kernelXY);		  
	convertScaleAbs(result4, result4);

	// ��������ϵ����·���ı�Ե
	filter2D(img, result5, CV_16S, kernelYX);
	convertScaleAbs(result5, result5);

	// ����ͼ��ı�Ե
	result6 = result2 + result3;


	// ��ʾ��Ե�����
	imshow("result1", result1);
	imshow("result2", result2);
	imshow("result3", result3);
	imshow("result4", result4);
	imshow("result5", result5);
	imshow("result6", result6);

	waitKey();

}