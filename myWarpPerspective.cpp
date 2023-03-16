#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	͸�ӱ任
	͸��ǰͼ���͸�Ӻ�ͼ��֮��ı任��ϵ����3*3�任�����ʾ����ͨ������ͼ��4����Ӧ��������ȡ��

	getPerspectiveTransform(Point2f src[], Point2f dst[],DECOMP_LU);
	�������������Ǵ��4��������������飬 ���ص���һ��3*3�ı任����   ���Ԫ�صĸ�˹��Ԫ��DECOMP_LU


	warpPerspective(InputArray src,
					outputArray dst,
					M,						// 3*3�任����
					Size dsize,
					flags,
					borderMode��
	
*/


int main1314(int argc, char* argv[])
{
	Mat img = imread("E:\\data\\6087.jpg");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
		return -1;
	}
	imshow("img", img);
	waitKey();

	// ͨ��Image watch�鿴�Ķ�ά��4���ǵ�����
	Point2f src_point[4] = { Point(120,81), Point(219,81), Point(122,178), Point(223,173) };
	// ����͸�ӱ任��Ķ�ά��4���ǵ������
	Point2f dst_point[4] = { Point(0, 0), Point(50,200),Point(200,200),Point(200,200) };

	Mat trans_Matirx, img_warp;
	trans_Matirx = getPerspectiveTransform(src_point, dst_point, DECOMP_LU);		// ����͸�ӱ任����

	warpPerspective(img, img_warp, trans_Matirx, img.size());						// ͸�ӱ任ͶӰ
	imshow("img_warp", img_warp);
	waitKey();



}