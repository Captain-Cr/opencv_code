#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	使用RANSAC对orb特征点匹配进行优化
*/

void match_min(vector<DMatch> &matches, vector<DMatch> &good_min)
{
	// 找到汉明距离最小的匹配特征
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
	// 寻找orb特征和计算描述子
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(img, keypoints, Mat());
	orb->compute(img, keypoints, descriptor);
}

void ransac(vector<DMatch> matches, vector<KeyPoint> queryKeypoint, vector<KeyPoint> trainKeypoint, vector<DMatch> &matches_ransac)
{
	// 定义保存匹配点对坐标
	vector<Point2f> srcPoints(matches.size());
	vector<Point2f> dstPoints(matches.size());

	// 保存从关键点中提取到的匹配点对的坐标
	for (int i = 0; i < matches.size(); i++)
	{
		srcPoints[i] = queryKeypoint[matches[i].queryIdx].pt;		// 匹配的查询描述子的坐标数组
		dstPoints[i] = trainKeypoint[matches[i].trainIdx].pt;		// 匹配的训练描述子的坐标数组
	}

	// 匹配点对进行RANSAC过滤
	vector<int> inliersMask(srcPoints.size());
	// 计算单应矩阵
	findHomography(srcPoints, dstPoints, RANSAC, 5, inliersMask);
	// 手动保存RANSAC过滤后的匹配点对
	for (int i = 0; i < inliersMask.size(); i++)
		if (inliersMask[i])					// 非零元素表示满足重投影误差
			matches_ransac.push_back(matches[i]);

}

int mainOrbMatchRANSAC(int argc, char* argv[])
{
	Mat img1 = imread("D:\\图像处理案例图片\\images\\box.png");		// 查询描述特征子图像
	Mat img2 = imread("D:\\图像处理案例图片\\images\\box_in_scene.png");			// 训练描述特征子图像
	if (img1.empty() || img2.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 寻找ORB特征点
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptor1, descriptor2;

	orb_feature(img1, keypoints1, descriptor1);
	orb_feature(img2, keypoints2, descriptor2);

	// 特征点匹配
	vector<DMatch> matches, good_min, good_ransac;
	// 创建一个匹配类
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptor1, descriptor2, matches);
	cout << "matches = " << matches.size() << endl;

	// 最小汉明距离
	match_min(matches, good_min);
	cout << "good_min = " << good_min.size() << endl;

	// 用RANSAC算法优化匹配结果
	ransac(good_min, keypoints1, keypoints2, good_ransac);
	cout << "good_matches.size = " << good_ransac.size() << endl;

	// 绘制匹配结果
	Mat outimg, outimg1, outimg2;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, outimg);
	drawMatches(img1, keypoints1, img2, keypoints2, good_min, outimg1);
	drawMatches(img1, keypoints1, img2, keypoints2, good_ransac, outimg2);

	imshow("未筛选结果", outimg);
	imshow("最小汉明距离筛选", outimg1);
	imshow("RANSAC筛选", outimg2);
	
	waitKey();
	destroyAllWindows();
	return 0;

}
