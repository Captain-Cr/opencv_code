#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	Description:�����ؼ���ǵ㣬��Ҫԭ��Ѱ��һ�㣬��ָ������Χ��ÿһ�����ص������������ص���ݶ������ĳ˻�֮����С��

	Function:
		void cornerSubPix(InputArray image, InputOutputArray corners, Size winSize, Size zeroZone, TermCriteria criteria);
*/


int mainCornerSubPix(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\contours.png");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}
	Mat img2;
	img.copyTo(img2);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// Ѱ��Shi-Tomas�ǵ�
	vector<Point2f> corners;
	int maxCorners = 100;					// ���ǵ�����
	double quality_level = 0.01;			// �����ȼ�����ָ��ֵ����ѽǵ�ı�����ϵ
	double minDistance = 0.04;				// �����ǵ����Сŷʽ����
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);
	// �ú�ɫ���ƽǵ�
	vector<KeyPoint> keypoints;
	for (int i = 0; i < corners.size(); i++)
	{
		KeyPoint keypoint;
		keypoint.pt = corners[i];
		keypoints.push_back(keypoint);
	}
	drawKeypoints(img, keypoints, img, Scalar(0, 0, 255), DrawMatchesFlags::DEFAULT);

	// ���������ؽǵ���
	vector<Point2f> cornerSub = corners;				// �ǵ㱸�ݣ���ֹ�������޸�
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 80, 0.001);
	cornerSubPix(gray, cornerSub, winSize, zeroZone, criteria);

	// �����ȷ����
	vector<KeyPoint> keypointsBySub;
	for (int j = 0; j < cornerSub.size(); j++)
	{
		KeyPoint keypoint;
		keypoint.pt = cornerSub[j];
		keypointsBySub.push_back(keypoint);
	}
	drawKeypoints(img, keypointsBySub, img, Scalar(0, 255, 0), DrawMatchesFlags::DEFAULT);


	imshow("img", img);
	waitKey();
	destroyAllWindows();
	return 0;
}