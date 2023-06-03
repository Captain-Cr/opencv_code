#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:����ͼ����Ҫ���ڿ��ټ���ĳЩ�������ص�ƽ���Ҷȡ��������ͼ���Ǳ�ԭʼͼ��ߴ��1����ͼ��
���ݻ���ͼ��ļ������Ĳ�ͬ�����Է�Ϊ3����Ҫ�Ļ���ͼ�񣬷ֱ��Ǳ�׼��ͻ���ͼ��ƽ����ͻ���ͼ���Լ���б��ͻ���ͼ��

	Function:	
			void cv::integral(InputArray src, OutputArray sum, int sdepth = -1);																    // ��׼���
			void cv::integral(InputArray src, OutputArray sum, OuputArray sqsum, int sdepth = -1, int sqdepth = -1);								// ƽ�����
			void cv::integral(InputArray src, OutputArray sum, OutputArray sqsum, OutputArray tilted, int sdepth=-1, int sqdepth=-1);				// ��б���

*/


int main_Integral(int argc, char* argv[])
{
	// ����һ��16x16������ֵȫΪ1�ľ�����Ϊ16x16=256
	Mat img = Mat::ones(16,16, CV_32FC1);

	// ��ͼ���м����������
	RNG rng(10086);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float d = rng.uniform(-0.5, 0.5);
			img.at<float>(i, j) = img.at<float>(i, j) + d;
		}
	}

	// �����׼���
	Mat sum;
	integral(img, sum);
	// Ϊ����ʾ���㣬ת��ΪCV_8U��ʽ
	Mat sum8u = Mat_<uchar>(sum);

	// ����ƽ�����
	Mat sqsum;
	integral(img, sum, sqsum);
	Mat sqsum8u = Mat_<uchar>(sqsum);

	// ������б���
	Mat tilted;
	integral(img, sum, sqsum, tilted);
	Mat tilted8u = Mat_<uchar>(tilted);

	// ������
	namedWindow("sum", WINDOW_NORMAL);
	namedWindow("sqsum", WINDOW_NORMAL);
	namedWindow("tilted", WINDOW_NORMAL);
	imshow("sum", sum);
	imshow("sqsum", sqsum);
	imshow("tilted", tilted);

	waitKey();
	destroyAllWindows();
	return 0;

}