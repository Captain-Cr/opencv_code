#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:Grabcut����Ҫ��ͼ��ָ��㷨����ʹ�ø�˹���ģ�͹���Ŀ������ı�����ǰ������ͨ�������ķ������������������С�������⡣

	Function��
		void cv::grabcut(InputArray img, InputOutputArray mask, Rect rect, InputOutputArray bgdModel, InputOutputArray fgdModel, int iterCount, int mode=GC_EVAL);
	Paramenets:
		img:����Ĵ��ָ�ͼ��ΪCV_8U�������͵���ͨ��ͼ��
		mask���������롢�����CV_8U��ͨ������ͼ��ͼ��������ֵ��ȡֵ��Χ���京���ڱ�1�и���
		rect�����������ROI���򣬸ò�������mode=GC_INIT_WITH_RECTʱʹ��
		bgdModel:����ģ�͵���ʱ����
		fgdModel��ǰ��ģ�͵���ʱ����
		iterCount:�㷨��Ҫ���еĵ�������
		mode:�ָ�ģʽ��־���ò����Ŀ�ѡ��Χ���京���ڱ�2�и���

							grabcut()����������ͼ������ֵ��Χ�ͺ���
		��־����						���							����
		GC_BGD							 0                            ����Ϊ����������
		GC_FGD							 1                            ����Ϊǰ�������󣩵�����
		GC_PR_BGD						 2							  ����Ϊ����������
		GC_PR_FGD						 3							  ����Ϊǰ�������󣩵�����


							grabcut���������зָ�ģʽ��־ȡֵ��Χ�ͺ���
		��־����						 ���							����
	GC_INIT_WITH_RECT					  0                          ʹ���ṩ�ľ��γ�ʼ��״̬�����룬֮������㷨���е�������
	GC_INIT_WITH_MASK				      1                          ʹ���ṩ�������ʼ��״̬���������GC_INIT_WITH_RECT��GC_INIT_WITH_MASK��Ȼ��ʹ��GC_BGD�Զ���ʼ��ROI�ⲿ��������
	GC_EVAL								  2                          �㷨Ӧ�ûָ�
	GC_EVAL_FREEZE_MODEL                  3                          ֻʹ�ù̶�ģ������Grabcut�㷨�����ε�����


*/


int mainGrabcut(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼƬ\\lena2.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ���ƾ���
	Mat imgRect;
	img.copyTo(imgRect);
	Rect rect(50, 20, 150, 180);
	rectangle(imgRect, rect, Scalar(255, 255, 255), 2);
	imshow("ѡ��ľ�������", imgRect);

	// ���зָ�
	Mat bgdmodel = Mat::zeros(1, 65, CV_64FC1);
	Mat fgdmodel = Mat::zeros(1, 65, CV_64FC1);
	Mat mask = Mat::zeros(img.size(), CV_8UC1);
	grabCut(img, mask, rect, bgdmodel, fgdmodel, 5, GC_INIT_WITH_RECT);

	// ���ָ����ǰ�����»���
	Mat result;
	for (int row = 0; row < mask.rows; row++)
	{
		for (int col = 0; col < mask.cols; col++)
		{
			int n = mask.at<uchar>(row, col);
			// ��������ǰ���Ϳ�����ǰ�������򶼱���
			if (n == 1 || n == 3)
			{
				mask.at<uchar>(row, col) = 255;
			}
			// �������Ǳ����Ϳ����Ǳ���������ɾ��
			else
			{
				mask.at<uchar>(row, col) = 0;
			}
		}
	}
	bitwise_and(img, img, result, mask);
	imshow("�ָ���", result);



	waitKey();
	destroyAllWindows();
	return 0;
}