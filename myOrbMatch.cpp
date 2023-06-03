#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* 
	特征点匹配：在不同图像中寻找同一物体的同一特征点
*/

void orb_features1(Mat &img, vector<KeyPoint> &keypoints, Mat &descriptors)
{
	// 创建ORB类
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	// 寻找关键点
	orb->detect(img, keypoints);
	// 计算描述子
	orb->compute(img, keypoints, descriptors);
}


int mainOrb()
{
	Mat img1 = imread("D:\\图像处理案例图片\\images\\box.png");		// 查询描述特征子图像
	Mat img2 = imread("D:\\图像处理案例图片\\images\\box_in_scene.png");			// 训练描述特征子图像
	if (img1.empty() || img2.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}
	
	// 提取orb特征点和描述子
	vector<KeyPoint> keypoints11, keypoints22;
	Mat descriptors11, descriptors22;
	
	// 对两幅图找关键点和描述子
	orb_features1(img1, keypoints11, descriptors11);
	orb_features1(img2, keypoints22, descriptors22);

	// 特征点匹配
	vector<DMatch> matches1;			// 存放匹配结果的变量
	BFMatcher matcher(NORM_HAMMING);		// 特征点匹配的类，使用汉明距离
	matcher.match(descriptors11, descriptors22, matches1);
	cout << "matches = " << matches1.size() << endl;		// 匹配成功特征点数目

	// 通过汉明距离筛选匹配结果
	double min_dist = 10000, max_dist = 0;
	for (int i = 0; i < matches1.size(); i++)
	{
		double dist = matches1[i].distance;			// 距离
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	// 输出所有匹配结果中最大汉明距离和最小汉明距离
	cout << "min_dist = " << min_dist << endl;
	cout << "max_dist = " << max_dist << endl;

	// 将汉明距离较大的匹配点对删除
	vector<DMatch> good_matches1;
	for (int i = 0; i < matches1.size(); i++)
	{
		if (matches1[i].distance <= max(2 * min_dist, 20.0))
		{
			good_matches1.push_back(matches1[i]);
		}
	}
	cout << "good_min = " << good_matches1.size() << endl;		// 剩余特征点数目

	// 绘制匹配结果
	Mat OutImg, OutImg1;
	drawMatches(img1, keypoints11, img2, keypoints22, matches1, OutImg);
	drawMatches(img1, keypoints11, img2, keypoints22, good_matches1, OutImg1);
	imshow("未筛选结果", OutImg);
	imshow("最小汉明距离筛选", OutImg1);


	waitKey();
	destroyAllWindows();
	return 0;

}