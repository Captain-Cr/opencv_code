/*

	connectedComponentsWithStats(InputArray img, OutputArray labels, OutputArray stats, OutputArray centroids, connectivity, ltype, ccltype)
		-img: 待标记不同连通域的单通道图像，数据类型必须为CV_8U
		-labels: 标记不同连通域后的输出图像，与输入图像具有相同的尺寸
		-stats： 含有不同连通域统计信息的矩阵，矩阵的数据类型为CV_32S。矩阵中第i行是标签为i的连通域的统计特性.如果图像有N个连通域，那么该参数输出的矩阵尺寸为N*5
		-centroids: 每个连通域质心的坐标，数据类型为CV_64F。如果图像有N个连通域，那么该参数输出的形状为N*2
		-connectivity: 统计连通域时使用的邻域种类，4代表4邻域，8代表8邻域
		-ltype: 输出图像的数据类型，目前支持CV_32S和CV_16U两种数据类型
		-ccltype: 标记连通域使用的算法类型标志

	该函数能够在图像中不同连通域标记标签的同时统计每个连通域的中心位置、矩形区域大小、区域面积等信息。
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int mainAAE(int argc, char* argv[])
{
	RNG rng(10086);   // 随机数对象

	Mat img = imread("D:\\图片\\123.jpg");
	resize(img, img, Size(600, 800));
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 灰度图+二值化
	Mat gray, thresh;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 60, 255, THRESH_BINARY);
	// 膨胀
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
	dilate(thresh, thresh, kernel, Point(-1, -1), 3);
	imshow("thresh", thresh);
	
	// 生成随机颜色
	vector<Vec3b> colors;
	Mat out, stats, centeriods;
	// 统计图像中的轮廓数量
	int num = connectedComponentsWithStats(thresh, out, stats, centeriods, 8, CV_16U);
	for (int i = 0; i < num; i++)
	{
		Vec3b vec3b = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3b);
	}

	// 以不同的颜色标记出不同的连通域
	Mat result = Mat::zeros(thresh.size(), thresh.type());
	int w = result.cols;
	int h = result.rows;
	for (int i = 1; i < num; i++)
	{
		// 中心位置
		int center_x = centeriods.at<double>(i, 0);		// 第i个轮廓的质心x坐标
		int center_y = centeriods.at<double>(i, 1);		// 第i个轮廓的质心y坐标

		// 矩形边框
		int x = stats.at<int>(i, CC_STAT_LEFT);			// 第i个轮廓的最左边坐标
		int y = stats.at<int>(i, CC_STAT_TOP);
		int w = stats.at<int>(i, CC_STAT_WIDTH);
		int h = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		// 中心点绘制
		circle(img, Point(center_x, center_y), 2, Scalar(0, 255, 0), 2, 8, 0);
		// 外接矩形
		Rect rect(x, y, w, h);
		rectangle(img, rect, colors[i], 1, 8, 0);
		putText(img, format("%d", i), Point(center_x, center_y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
		cout << "number:" << i << ",area" << area << endl;
	}

	// 显示结果
	imshow("标记后的图像", img);
	
	
	
	
	
	waitKey();
	return 0;

}