#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	LUT: 阈值比较方法都只有一个阈值， 如果需要与多个阈值进行比较，就需要用到显示查找表（Look-Up-Table)
	LUT就是一个像素灰度值的映射表， 它以像素灰度值作为索引， 以灰度值映射后的数值作为表的内容。
*/

int main4(int argc, char * argv[])
{
	// LUT 第一层
	uchar lutFirst[256];
	for (int i = 0; i < 256; i++)
	{
		if (i <= 100)
			lutFirst[i] = 0;			// 映射， 像素值低于100的置0
		if (i > 100 && i <= 200)
			lutFirst[i] = 100;
		if (i > 200)
			lutFirst[i] = 255;
	}
	Mat lutOne(1, 256, CV_8UC1, lutFirst);


	// LUT 第二层
	uchar lutSecond[256];
	for (int i = 0; i < 256; i++)
	{
		if (i <= 100)
			lutSecond[i] = 0;
		if (i > 100 && i < 150)
			lutSecond[i] = 100;
		if (i > 150 && i <= 200)
			lutSecond[i] = 150;
		if (i > 200)
			lutSecond[i] = 255;
	}
	Mat lutTwo(1, 256, CV_8UC1, lutSecond);



	// LUT 第三层
	uchar lutThird[256];
	for (int i = 0; i < 256; i++)
	{
		if (i <= 100)
			lutThird[i] = 100;
		if (i > 100 && i <= 200)
			lutThird[i] = 200;
		if (i > 200)
			lutThird[i] = 255;
	}
	Mat lutThree(1, 256, CV_8UC1, lutThird);


	// 拥有三通道的LUT矩阵
	vector<Mat> mergeMats;
	mergeMats.push_back(lutOne);
	mergeMats.push_back(lutTwo);
	mergeMats.push_back(lutThree);
	Mat LutTree;
	merge(mergeMats, LutTree);			// 将三个通道进行合并

	// 计算图像的查找表
	Mat img = imread("E:\\XIUGOU.png");
	if (img.empty())
	{
		cout << "图像加载错误！！！" << endl;
		return -1;
	}
	Mat gray, out0, out1, out2;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	LUT(gray, lutOne, out0);
	LUT(img, lutOne, out1);
	LUT(img, LutTree, out2);
	imshow("out0", out0);
	imshow("out1", out1);
	imshow("out2", out2);
	waitKey();
	return 0;

}