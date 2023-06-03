#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	ʹ��flann����orb����ƥ��
*/
void orb_features(Mat &img, vector<KeyPoint> &keypoints, Mat &descriptor)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(img, keypoints);
	orb->compute(img, keypoints, descriptor);
}

int mainOrbMatchFlann(int argc, char* argv[])
{
	Mat img1 = imread("D:\\ͼ������ͼƬ\\images\\box.png");		// ��ѯ����������ͼ��
	Mat img2 = imread("D:\\ͼ������ͼƬ\\images\\box_in_scene.png");			// ѵ������������ͼ��
	if (img1.empty() || img2.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ����orb������
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	orb_features(img1,keypoints1, descriptors1);
	orb_features(img2, keypoints2, descriptors2);

	// ���������ӵ��������ͣ��ж��Ƿ���CV_32F
	if ((descriptors1.type() != CV_32F) && (descriptors2.type() != CV_32F))
	{
		descriptors1.convertTo(descriptors1, CV_32F);
		descriptors2.convertTo(descriptors2, CV_32F);
	}

	// ����������ƥ��
	FlannBasedMatcher matcher;			
	vector<DMatch> matches;				// ���ƥ���Ľ��
	matcher.match(descriptors1, descriptors2, matches, Mat());
	cout << "matches = " << matches.size() << endl;		// ƥ��ɹ�����������Ŀ

	// Ѱ�����ֵ����Сֵ�������orb�����㣬��ômin_distȡֵҪ��һЩ
	double min_dist = 10000; double max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		min_dist = matches[i].distance < min_dist ? matches[i].distance : min_dist;
		max_dist = matches[i].distance > max_dist ? matches[i].distance : max_dist;
	}
	cout << "max dist: " << max_dist << endl;
	cout << "min dist: " << min_dist << endl;

	// �����ֵ�����0.4����Ϊ����ƥ��Ľ������ɸѡ
	std::vector<DMatch> good_matches;
	for (int j = 0; j < matches.size(); j++)
	{
		if (matches[j].distance <= 0.4 * max_dist)
		{
			good_matches.push_back(matches[j]);
		}
	}
	cout << "good matches = " << good_matches.size() << endl;		// ƥ��ɹ���������Ŀ

	// ����ƥ����
	Mat out1, out2;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, out1);
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, out2);

	imshow("δ�Ż���ƥ������", out1);
	imshow("�Ż����ƥ������", out2);
	waitKey();
	destroyAllWindows();
	
	return 0;

}