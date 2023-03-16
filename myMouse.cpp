#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	�����Ӧ
	setMouseCallback(string winname, MouseCallback onMouse, userdata=0); Ϊָ��ͼ�񴰿ڴ��������Ӧ����һ�������Ǵ������ƣ��ڶ��������������Ӧ�Ļص��������ú��������״̬�����仯ʱ�����ã���һ��MouseCallback���͵ĺ�����
	
	MouseCallback���ͣ���MouseCallback���͵Ļص�������һ���޷���ֵ�ĺ�����
	typedef void(*cv::MouseCallback)(int event,			# �����Ӧ�¼���־������ΪEVENT_*
									 int x,				# ���ָ����ͼ������ϵ�е�x����
									 int y,				# ���ָ����ͼ������ϵ�е�y����
									 int flags,			# �����Ӧ��־������ΪEVENT_FLAG_*��ʽ��
									 void *userdata)	# ���ݸ��ػص������Ŀ�ѡ����

	�����Ӧ���ǵ����λ�ڶ�Ӧ��ͼ�񴰿���ʱ��ʱ�̼�����״̬�������״̬�����ı�ʱ�����ûص�������                 
*/



Mat img3, imgPoint;			// ȫ�ֵ�ͼ��
Point prePoint;				// ǰһʱ���������꣬���ڻ���ֱ��
void mouse(int event, int x, int y, int flags, void *);		// �������ص�����

int main213()
{
	img3 = imread("D:\\ͼƬ\\lena.jpg");
	if (img3.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	img3.copyTo(imgPoint);			// ���
	imshow("ͼ�񴰿�1", img3);
	imshow("ͼ�񴰿�2", imgPoint);

	// ���������Ӧ
	setMouseCallback("ͼ�񴰿�1", mouse, 0);			
	waitKey();
	return 0;

}



void mouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_RBUTTONDOWN)				// �����Ҽ�
	{
		cout << "����������ſ��Ի��ƹ켣" << endl;
	}

	if (event == EVENT_LBUTTONUP)					// ���������������� 
	{
		prePoint = Point(x, y);
		cout << "�켣��ʼ����Ϊ��" << prePoint << endl;
	}

	if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))		// ��ס�������ƶ�
	{
		// ͨ���ı�ͼ��������ʾ����ƶ��켣
		imgPoint.at<Vec3b>(y, x) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y, x - 1) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y, x + 1) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y+1, x) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y+1, x) = Vec3b(0, 0, 255);
		imshow("ͼ�񴰿�2", imgPoint);

		// ͨ������ֱ����ʾ����ƶ�����
		Point pt(x, y);
		line(img3, prePoint, pt, Scalar(0, 0, 255), 2, 5, 0);
		prePoint = pt;
		imshow("ͼ�񴰿�1", img3);

	}
	


}