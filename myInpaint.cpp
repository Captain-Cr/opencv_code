#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:ͼ���޸�������������ͼ�����������Ե�����أ�����������ֵ��Ľṹ��ϵ�����Ƴ���������ܵ��������У��Ӷ�ȥ��ͼ��������Ⱦ�����򡣿���ȥ��ͼ���л��ۡ�ˮӡ������

	Function:
		void cv::inpaint(InputArray src, InputArray inpainMask, OutputArray dst, double inpainRadius, int flags);
	�ú�������ͼ���޸��㷨��ͼ����ָ������������޸��������޷��ж���Щ������Ҫ�޸��������ʹ�ù�������Ҫ��ȷָ����Ҫ�޸������򡣸ú����ĵ�һ������Ϊ��Ҫ�޸���ͼ�񣬸ú������ԶԻҶ�ͼ��Ͳ�ɫͼ��
	�����޸����޸��Ҷ�ͼ��ʱ���������Ϳ�����CV_8U,CV_16U��CV_32U�ĵ�ͨ��ͼ�����޸���ɫͼ��ʱ��ͼ�����������ֻ��ΪCV_8U���ڶ�������Ϊ�޸����룬��ָ��ͼ������Ҫ�޸������򣬸ò�������������һ����
	���޸�ͼ����ͬ�ߴ�����͵�CV_8U��ͨ��ͼ��ͼ���з������ر�ʾ��Ҫ�޸������򡣵������������޸������ͼ�񣻵��ĸ�������ʾ�޸��㷨���ǵ�ÿ�����ص��Բ������뾶�����һ��������ʾ�޸�ͼ��ķ���
	��־������ѡ��ı�־���京��������ʾ��
													inpaint()�����޸�ͼ�񷽷���ѡ��־
	             ��־����                   ���                               ����
			    INPAINT_NS                   0                               ����Navier-Stokes�㷨�޸�ͼ��
				INPAINT_TELEA                1                               ����Alexandru-Telea�㷨�޸�ͼ��
									
*/




int maininpaint(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\lenaInpaint.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return 0;
	}
	imshow("img", img);

	// ͨ����ֵ�����ȡҪ�޸�ͼ�������
	Mat gray, thresh;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 20, 255, THRESH_BINARY_INV);		// ��ֵͼ�����mask
	imshow("thresh", thresh);
	// ��̬ѧ����
	Mat mask; 
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
	dilate(thresh, mask, kernel, Point(-1,-1),2);
	imshow("dilate", mask);
	/*Mat mask;
	Mat kernel = (Mat_<uchar>(3, 1) << 1,1,1);
	morphologyEx(thresh, mask, MORPH_OPEN, kernel);
	imshow("morphology", mask);*/

	// ����ͼ���޸�
	Mat imgInpaint;
	inpaint(img, mask, imgInpaint, 5, INPAINT_NS);
	imshow("imgInpaint", imgInpaint);

	

	waitKey();
	destroyAllWindows();
	return 0;
}