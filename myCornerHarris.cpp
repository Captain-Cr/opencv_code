#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description:����ֵ�ľֲ�����ֵ��ΪHarris�ǵ㣬��ĳһ������Ϊ���Ĺ���һ���������ڣ�ͨ�����Ե��ӵõ�������������ֵ�ĺ���ϵ���������������������ĸ������ƶ�����ֵ����ϵ������Сʱ�������������ĵ��Ӧ�����ؾ�ΪHarris�ǵ�

	Function:
		void cv::cornerHarris(InputArray src, OutputArray dst, int blockSize, int ksize, double k, int borderType=BORDER_DEFAULT);
	�������ܹ������ͼ��ÿ�����ص��Harris����ϵ����ͨ���Աȸ�ϵ����С������ȷ���õ��Ƿ�Ϊharris�ǵ㡣��һ�������Ǵ����Harris�ǵ������ͼ��ͼ�������CV_8U��CV_32F�ĵ�ͨ���Ҷ�ͼ��
	�ڶ��������Ǵ��Harris����ϵ��R�ľ���R�����Ǹ�����С������˸�ͼ��������������ΪCV_32F������������������Ĵ�С��ͨ��ѡ2.���ĸ������Ǽ�����ȡ��Ϣ��Sobel���ӵİ뾶���ò�����Ҫ��������
	��ʹ��3����5.�����������Ȩ��ϵ����һ��ȡ0.02 - 0.04�����һ�����������������㷨��־��
*/

int mainHarrisCorner(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\lena.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ת��Ϊ�Ҷ�ͼ
	Mat gray; 
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// ����harris�ǵ�����ϵ��
	Mat harris;
	int blocksize = 2;			// ����뾶
	int apertureSize = 3;
	cornerHarris(gray, harris, blocksize, apertureSize, 0.04);

	// ��һ��
	Mat harrisn;
	normalize(harris, harrisn, 0, 255, NORM_MINMAX);
	// ��ͼ�����ݱ��CV_8U
	convertScaleAbs(harrisn, harrisn);

	// Ѱ��harris�ǵ�
	vector<KeyPoint> keypoints;
	for (int i = 0; i < harrisn.rows; i++)
	{
		for (int j = 0; j < harrisn.cols; j++)
		{
			int R = harrisn.at<uchar>(i, j);
			if (R > 125)
			{
				// ���ǵ����KeyPoint��
				KeyPoint keypoint;
				keypoint.pt.y = i;
				keypoint.pt.x = j;
				keypoints.push_back(keypoint);
			}

		}
	}

	// ���ƽǵ㲢������ʾ
	drawKeypoints(img, keypoints, img);
	imshow("ϵ������", harrisn);
	imshow("harris�ǵ�", img);



	waitKey();
	destroyAllWindows();
	return 0;
}