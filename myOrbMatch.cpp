#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* 
	������ƥ�䣺�ڲ�ͬͼ����Ѱ��ͬһ�����ͬһ������
*/

void orb_features1(Mat &img, vector<KeyPoint> &keypoints, Mat &descriptors)
{
	// ����ORB��
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	// Ѱ�ҹؼ���
	orb->detect(img, keypoints);
	// ����������
	orb->compute(img, keypoints, descriptors);
}


int mainOrb()
{
	Mat img1 = imread("D:\\ͼ������ͼƬ\\images\\box.png");		// ��ѯ����������ͼ��
	Mat img2 = imread("D:\\ͼ������ͼƬ\\images\\box_in_scene.png");			// ѵ������������ͼ��
	if (img1.empty() || img2.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}
	
	// ��ȡorb�������������
	vector<KeyPoint> keypoints11, keypoints22;
	Mat descriptors11, descriptors22;
	
	// ������ͼ�ҹؼ����������
	orb_features1(img1, keypoints11, descriptors11);
	orb_features1(img2, keypoints22, descriptors22);

	// ������ƥ��
	vector<DMatch> matches1;			// ���ƥ�����ı���
	BFMatcher matcher(NORM_HAMMING);		// ������ƥ����࣬ʹ�ú�������
	matcher.match(descriptors11, descriptors22, matches1);
	cout << "matches = " << matches1.size() << endl;		// ƥ��ɹ���������Ŀ

	// ͨ����������ɸѡƥ����
	double min_dist = 10000, max_dist = 0;
	for (int i = 0; i < matches1.size(); i++)
	{
		double dist = matches1[i].distance;			// ����
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	// �������ƥ������������������С��������
	cout << "min_dist = " << min_dist << endl;
	cout << "max_dist = " << max_dist << endl;

	// ����������ϴ��ƥ����ɾ��
	vector<DMatch> good_matches1;
	for (int i = 0; i < matches1.size(); i++)
	{
		if (matches1[i].distance <= max(2 * min_dist, 20.0))
		{
			good_matches1.push_back(matches1[i]);
		}
	}
	cout << "good_min = " << good_matches1.size() << endl;		// ʣ����������Ŀ

	// ����ƥ����
	Mat OutImg, OutImg1;
	drawMatches(img1, keypoints11, img2, keypoints22, matches1, OutImg);
	drawMatches(img1, keypoints11, img2, keypoints22, good_matches1, OutImg1);
	imshow("δɸѡ���", OutImg);
	imshow("��С��������ɸѡ", OutImg1);


	waitKey();
	destroyAllWindows();
	return 0;

}