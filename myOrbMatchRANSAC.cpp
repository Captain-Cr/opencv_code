#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	ʹ��RANSAC��orb������ƥ������Ż�
*/

void match_min(vector<DMatch> &matches, vector<DMatch> &good_min)
{
	// �ҵ�����������С��ƥ������
	double min_dist = 1000, max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		min_dist = matches[i].distance < min_dist ? matches[i].distance : min_dist;
		max_dist = matches[i].distance > max_dist ? matches[i].distance : max_dist;
	}
	cout << "min_dist = " << min_dist << endl;
	cout << "max_dist = " << max_dist << endl;

	for (int j = 0; j < matches.size(); j++)
	{
		if (matches[j].distance <= max(2 * min_dist, 20.0))
		{
			good_min.push_back(matches[j]);
		}
	}

}

void orb_feature(Mat &img, vector<KeyPoint> &keypoints, Mat &descriptor)
{
	// Ѱ��orb�����ͼ���������
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(img, keypoints, Mat());
	orb->compute(img, keypoints, descriptor);
}

void ransac(vector<DMatch> matches, vector<KeyPoint> queryKeypoint, vector<KeyPoint> trainKeypoint, vector<DMatch> &matches_ransac)
{
	// ���屣��ƥ��������
	vector<Point2f> srcPoints(matches.size());
	vector<Point2f> dstPoints(matches.size());

	// ����ӹؼ�������ȡ����ƥ���Ե�����
	for (int i = 0; i < matches.size(); i++)
	{
		srcPoints[i] = queryKeypoint[matches[i].queryIdx].pt;		// ƥ��Ĳ�ѯ�����ӵ���������
		dstPoints[i] = trainKeypoint[matches[i].trainIdx].pt;		// ƥ���ѵ�������ӵ���������
	}

	// ƥ���Խ���RANSAC����
	vector<int> inliersMask(srcPoints.size());
	// ���㵥Ӧ����
	findHomography(srcPoints, dstPoints, RANSAC, 5, inliersMask);
	// �ֶ�����RANSAC���˺��ƥ����
	for (int i = 0; i < inliersMask.size(); i++)
		if (inliersMask[i])					// ����Ԫ�ر�ʾ������ͶӰ���
			matches_ransac.push_back(matches[i]);

}

int mainOrbMatchRANSAC(int argc, char* argv[])
{
	Mat img1 = imread("D:\\ͼ������ͼƬ\\images\\box.png");		// ��ѯ����������ͼ��
	Mat img2 = imread("D:\\ͼ������ͼƬ\\images\\box_in_scene.png");			// ѵ������������ͼ��
	if (img1.empty() || img2.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// Ѱ��ORB������
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;

	orb_feature(img1, keypoints1, descriptor1);
	orb_feature(img2, keypoints2, descriptor2);

	// ������ƥ��
	vector<DMatch> matches, good_min, good_ransac;
	// ����һ��ƥ����
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptor1, descriptor2, matches);
	cout << "matches = " << matches.size() << endl;

	// ��С��������
	match_min(matches, good_min);
	cout << "good_min = " << good_min.size() << endl;

	// ��RANSAC�㷨�Ż�ƥ����
	ransac(good_min, keypoints1, keypoints2, good_ransac);
	cout << "good_matches.size = " << good_ransac.size() << endl;

	// ����ƥ����
	Mat outimg, outimg1, outimg2;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, outimg);
	drawMatches(img1, keypoints1, img2, keypoints2, good_min, outimg1);
	drawMatches(img1, keypoints1, img2, keypoints2, good_ransac, outimg2);

	imshow("δɸѡ���", outimg);
	imshow("��С��������ɸѡ", outimg1);
	imshow("RANSACɸѡ", outimg2);
	
	waitKey();
	destroyAllWindows();
	return 0;

}
