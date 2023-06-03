#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:特征点由关键点和描述子构成，常见有SIFT、SUFT和ORB
	Opencv4中搭建了features2D虚类，类中定义了检测特征点时需要的关键点检测函数、描述子计算函数、描述子类数据类型及读写操作等函数，只要其他某个特征点继承了Features2D类，就可以通过其中的函数
	计算关键点和描述子。事实上，Opencv4中所有的特征点都继承了Features2D类。

	相关函数：
		（1）virtual void Features2D::detect(InputArray image, std::vector<KeyPoint>& keypoints, InputArray mask = noArray());
	该函数能够根据需要计算不同种特征点的关键点。第一个参数是需要计算关键点的图像，图像的类型与继承Features2D类的特征点相关。第二个参数是检测到的关键点，存放在数据类型为vector<KeyPoint>的向量中，
	此时关键点变量不仅有关键点的坐标，还有关键点方向、半径尺寸等，具体内容与特征点的种类相关。最后一个参数是计算关键点时的掩码图像，用于表示需要在哪些区域计算关键点，掩码矩阵需要与输入图像具有
	相同的尺寸并且数据类型为CV_8U，需要计算关键点的区域在掩码中用非零元素表示。

		（2）virtual void Features2D::compute(InputArray image, std::vector<KeyPoint>& keypoints, OutputArray descriptors);
	该函数能够根据输入的图像和指定图像中的关键点坐标计算得到每个关键点的描述子。描述子：用来唯一确定关键点的一串数字，可以通过描述子区分两个不同的关键点，也可以在不同图像寻找同一个关键点

		（3）virtual void Features2D::detectAndCompute(InputArray image, InputArray mask, std::vector<KeyPoint>& keypoints, OutputArray descriptor, bool useProvideKeyPoints =false);
	该函数将计算关键点和描述子的功能集成在一起，可以根据输入图像直接计算出关键点和关键点对应的描述子。

	注意：上面的函数都需要被其它类继承之后才能使用，例如在ORB特征点的ORB类中，可以通过ORB::detect()函数计算ORB特征点的关键点；在SIFT特征点的SIFT类中，通过SIFT::detect()函数计算SiFT特征的关键点。

	
		（4）static Ptr<ORB> cv::ORB::create(int nfeatures = 500, float scaleFactor = 1.2f, int nLevel = 8, int edgeThreshold = 31, int firstLevel = 0, int WTA_K =2, 
												ORB::ScoreType scoreType = ORB::HARRIS_SCORE, int patchSize = 31, int fastThreshold = 20);
	该函数可以创建一个ORB类的变量，之后利用类中的方法计算图像中的ORB特征点。

	*/




int mainORB(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\lena.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 创建ORB特征点类变量
	Ptr<ORB> orb = ORB::create(500,					// 特征点数目
		1.2f,					// 金字塔之间的缩放比例
		8,						// 金字塔图像层数系数
		31,						// 边缘阈值
		0,						// 原图在金字塔的层数（原图是金字塔的第几层）
		2,						// 生成描述子时需要用的像素点数目
		ORB::HARRIS_SCORE,			// 使用Harris方法评价特征点
		31,						// 生成描述子时关键点周围的邻域尺寸
		20  					// 计算FAST角点时像素值差值的阈值
		);
	// 计算ORB关键点
	vector<KeyPoint> keypoints;
	orb->detect(img, keypoints, Mat());

	// 计算ORB描述子
	Mat descriptions;
	orb->compute(img, keypoints, descriptions);

	// 绘制特征点
	Mat imgAngel;
	img.copyTo(imgAngel);
	// 绘制不含角度和大小的结果
	drawKeypoints(img, keypoints, img, Scalar(255, 255, 255));
	// 绘制含有角度和大小的结果
	drawKeypoints(img, keypoints, imgAngel, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// 显示结果
	imshow("不含角度和大小的结果", img);
	imshow("含有角度和大小的结果", imgAngel);
	waitKey();
	destroyAllWindows();
	return 0;

}