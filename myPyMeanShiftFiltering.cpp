#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:Mean-Shift���ֳ�Ϊ��ֵƯ�Ʒ�����һ�ֻ�����ɫ�ռ�ֲ���ͼ��ָ��㷨�����㷨�������һ��������ɫ�ġ���ɫ��ͼ������ɫ���ý��䣬����ϸ�������ƽ����
	��Mean-Shift���У�ÿ�����ص���һ����ά������x,y,b,g,r)��ʾ��ǰ�����������ص���ͼ���е����꣬��3������ÿ�����ص����ɫ������

	Function:
		void cv::pyrMeanShiftFiltering(InputArray src, OutputArray dst, double sp, double sr, int maxLevel=1, TermCriteria termcrit=TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 5, 1);
			-src�����ָ������ͼ�񣬱�����CV_8U���͵���ͨ����ɫͼ��
			-dst���ָ������ͼ��������ͼ�������ͬ�ĳߴ����������
			-sp���������ڵİ뾶
			-sr������������ɫ����
			-maxLevel:�ָ���������Ų���
			-termcrit�������㷨��ֹ����


		cv::TermCriteria::TermCriteria(int type, int maxCount,double epsilon);
		�ú������Ա�ʾ�����㷨����ֹ��������Ҫ��Ϊ�������������������㾫�����֡���һ����������ֹ���������ͱ�־����ѡ��־���±���ʾ����Ҫע�⣬���ڸò�����TermCriteria���У������ʹ��ʱ��Ҫ��
		����ǰ���������ǰ׺���ú����ڶ���������ʾ��������������Ԫ��������type==TermCriteria::COUNTʱ�������á�������������ʾֹͣ����ʱ��Ҫ����ļ��㾫�Ȼ�����仯����type==TermCriteria::EPSʱ
		�������á�


										TermCriteria()��������ֹ���������ͱ�־���京��
			��־����                     ���                            ����
		TermCriteria::COUNT               1                           ���������ﵽ�趨ֵʱ��ֹͣ����
		TermCriteria::MAX_ITER            1                           ͬ��
		TermCriteria::EPS				  2                           ������ľ�������Ҫ��ʱֹͣ����

*/


int mainMeanShift(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\apple.jpg");
	if (img.empty())
	{
		cout << "ͼƬ����ʧ��" << endl;
		return -1;
	}

	// �ָ��
	Mat result1, result2;
	TermCriteria T10 = TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 0.1);
	pyrMeanShiftFiltering(img, result1, 20, 40, 2, T10);				// ��һ�ηָ�
	pyrMeanShiftFiltering(result1, result2, 20, 40, 2, T10);			// �ڶ��ηָ�

	// ��ʾ�ָ���
	imshow("src", img);
	imshow("result1", result1);
	imshow("result2", result2);

	// ��ͼ����ȡcanny��Ե
	Mat imgCanny, result1Canny, result2Canny;
	Canny(img, imgCanny, 150, 200);
	Canny(result1, result1Canny, 150, 200);
	Canny(result2, result2Canny, 150, 200);

	// ��ʾ
	imshow("imgCanny", imgCanny);
	imshow("result1Canny", result1Canny);
	imshow("result2Canny", result2Canny);


	waitKey();
	destroyAllWindows();
	return 0;

}