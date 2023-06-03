#include <iostream>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace xfeatures2d;		


/*
（1）SIFT特征点
	SIFT特征点的SIFT类及其相关函数封装在opencv_contrib扩展模块中（要安装opencv_contrib扩展模块才能使用）
	SIFT类在opencv_contrib扩展模块下的<xfeature2ds.hpp>头文件中。其继承Features2D类，因此可以使用detect（）计算特征点和compute（）计算描述子。
	并在此之前需要定义SIFT类变量，SIFT类中提供了create()函数用于创建SFIT类变量。

	函数原型：
		static Ptr<SIFT> cv::xfeatures2d::SIFT::create(int nfeatures = 0, int nOctaveLayers = 3, double contrastThreshold = 0.04, double edgeThreshold = 10, double sigma = 1.6);
	该函数可以创建一个SIFT类的变量，之后利用类里的方法计算图像中的SIFT特征点。其中：nfeatures是计算SIFT特征点的数目,nOctaveLayers是金字塔中每组的层数,contrastThreshold是过滤较差特征点的阈值，该值越大
	返回的特征点越少。edgeThreshold是过滤边缘效应的阈值，该值越大，返回的特征点越多,sigma是金字塔第0层图像高斯滤波的系数。

（2）SURF特征点
	SURF特征点的SURF类及其相关函数同样封装在opencv_contrib扩展模块中。
	SURF类在opencv_contrib扩展模块下的<xfeatures2d.hpp>头文件中。其继承Features2D类，因此可以使用detect()和compute（）计算关键点和描述子。
	在此之前需要定义SURF类变量，SURF类提供create()函数用于创建SURF类变量。

	函数原型：
		static Ptr<SURF> cv::xfeatures2d::SURF::create(double hessianThreshold = 100, int nOctaves = 4, int nOctaveLayers = 3, bool extended = false, bool upright = false);
	该函数可以创建一个SURF类的变量，之后利用类里的方法计算图像中的SURF特征点。
*/



int mainSURF(int argc, char* argv[])
{
	
	Mat img = imread("D:\\360极速浏览器下载\\2.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 创建SURF特征点类变量
	Ptr<SURF> sufr = SURF::create(500,		// 关键点数量
		4,				// 4组金字塔
		3,				// 每组金字塔有3层
		true,			// 使用128维描述子
		false			// 计算关键点方向
	);

	// 计算SURF关键点
	vector<KeyPoint> Keypoints;
	sufr->detect(img, Keypoints);		// 确定关键点
	// 计算描述子
	Mat descriptions;
	sufr->compute(img, Keypoints, descriptions);	

	// 绘制关键点
	Mat img1;
	img.copyTo(img1);
	// 绘制不含角度和大小的结果
	drawKeypoints(img, Keypoints, img, Scalar(255, 255, 255));
	// 绘制含有角度和大小的结果
	drawKeypoints(img, Keypoints, img1, Scalar(255, 255, 255),
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// 进行显示
	//imshow("img", img);
	imshow("不含角度和大小的结果", img);
	imshow("含有角度和大小的结果", img1);
	waitKey();
	return 0;
}