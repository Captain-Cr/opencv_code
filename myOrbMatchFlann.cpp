#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	使用flann进行orb特征匹配
*/
void orb_features(Mat &img, vector<KeyPoint> &keypoints, Mat &descriptor)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(img, keypoints);
	orb->compute(img, keypoints, descriptor);
}

int mainOrbMatchFlann(int argc, char* argv[])
{
	Mat img1 = imread("D:\\图像处理案例图片\\images\\box.png");		// 查询描述特征子图像
	Mat img2 = imread("D:\\图像处理案例图片\\images\\box_in_scene.png");			// 训练描述特征子图像
	if (img1.empty() || img2.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 计算orb描述子
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	orb_features(img1,keypoints1, descriptors1);
	orb_features(img2, keypoints2, descriptors2);

	// 根据描述子的数据类型，判断是否是CV_32F
	if ((descriptors1.type() != CV_32F) && (descriptors2.type() != CV_32F))
	{
		descriptors1.convertTo(descriptors1, CV_32F);
		descriptors2.convertTo(descriptors2, CV_32F);
	}

	// 进行特征点匹配
	FlannBasedMatcher matcher;			
	vector<DMatch> matches;				// 存放匹配后的结果
	matcher.match(descriptors1, descriptors2, matches, Mat());
	cout << "matches = " << matches.size() << endl;		// 匹配成功的特征点数目

	// 寻找最大值和最小值，如果是orb特征点，那么min_dist取值要大一些
	double min_dist = 10000; double max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		min_dist = matches[i].distance < min_dist ? matches[i].distance : min_dist;
		max_dist = matches[i].distance > max_dist ? matches[i].distance : max_dist;
	}
	cout << "max dist: " << max_dist << endl;
	cout << "min dist: " << min_dist << endl;

	// 将最大值距离的0.4倍作为左右匹配的结果进行筛选
	std::vector<DMatch> good_matches;
	for (int j = 0; j < matches.size(); j++)
	{
		if (matches[j].distance <= 0.4 * max_dist)
		{
			good_matches.push_back(matches[j]);
		}
	}
	cout << "good matches = " << good_matches.size() << endl;		// 匹配成功特征点数目

	// 绘制匹配结果
	Mat out1, out2;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, out1);
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, out2);

	imshow("未优化的匹配结果：", out1);
	imshow("优化后的匹配结果：", out2);
	waitKey();
	destroyAllWindows();
	
	return 0;

}