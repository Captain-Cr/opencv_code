#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


/*
	Description: Shi-Tomas角点检测。Harris角点评价系数的大小不能完全的概括两个特征向量之间的大小关系，因此Shi和Tomas对Harris角点的评判指标进行调整，将特征向量的最小值作为角点评价系数。
	R = min(μ1，μ2）; 当R大于某一阈值，则将该点认为是角点。

	Function：
		void  goodFeaturesToTrack(InputArray image, OutputArray corners, int maxCorners, double qualityLevel, double minDistance, InputArray mask = noArray(), int blockSize = 3, 
	bool useHarrisDetector = False, double k = 0.04);
	该函数能够寻找图像中指定区域内的Shi-Tomas角点，该函数的阈值与最佳角点向对应，避免了绝对阈值在不同图像中效果不理想的现象，另外，函数可以直接输出角点的坐标，不需要根据输出结果再次判断是否为角点
	

*/


int mainGoodFeaturesToTrack(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\lena.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}
	// 深拷贝用于第二种方法绘制角点
	Mat img2;
	img.copyTo(img2);
	Mat gray; 
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 提取角点
	int maxCorners = 100;			// 检测角点数量
	double quality_level = 0.01;		// 质量等级，或者指阈值与最佳角点的比例关系
	double minDistance = 0.04;			// 两个角点之间的最小欧式距离
	vector<Point2f> corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);

	// 绘制角点
	vector<KeyPoint> keypoints;			// 存放角点的keyPoint类
	RNG rng(10086);
	for (int i = 0; i < corners.size(); i++)
	{
		// 第一种绘制角点，用circle（）函数绘制
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int r = rng.uniform(0, 256);
		circle(img, corners[i], 2, Scalar(b, g, r), 2, 8, 0);

		// 将角点存放在KeyPoint类中
		KeyPoint keypoint;
		keypoint.pt = corners[i];
		keypoints.push_back(keypoint);
	}


	// 第二种绘制方法
	drawKeypoints(img2, keypoints, img2);
	// 输出绘制角点结果
	imshow("使用circle（）函数绘制角点结果", img);
	imshow("使用drawKeyPoint绘制角点结果", img2);
	waitKey();
	destroyAllWindows();
	return 0;

}