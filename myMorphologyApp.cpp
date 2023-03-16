#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	opencv使用morphologyEx()函数实现形态学操作；
	开操作：先腐蚀后膨胀，去掉多余小白点，消除较小连通域，保留较大连通域同时能够在两个物体纤细处将两个物体分离； 
	闭运算：先膨胀后腐蚀，去掉多余小黑点，去除连通域内小型空洞，平滑轮廓，连接两个临近的连通域；
	形态学梯度：能够描述目标边界，根据腐蚀、膨胀与原图之间的关系得到，形态学梯度可分为基本梯度、内部梯度和外部梯度；基本梯度=膨胀-腐蚀， 内部梯度=原图-腐蚀，外部梯度=膨胀-原图；
	顶帽运算：是原图像与开运算结果之间的差值，也就是得到小白点；
	黑帽运算：是对图像进行闭运算之后从闭结果中减去原图像，也就是得到小黑点；
	击中不击中变换：图像腐蚀只需图像能够将结构元素中的所有非零元素包含，但是击中不击中变换要求原图像中需要存在和结构元素一模一样的结构，即结构元素中非零元素也需要同时被考虑；

*/


int mainaef(int argc, char* argv[])
{
	// 用于验证形态学应用的二值化矩阵
	Mat src = (Mat_<uchar>(9, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	namedWindow("src", WINDOW_NORMAL);
	imshow("src", src);

	// 3x3结构元素
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	// 对二值图像进行形态学操作
	Mat open, close, gradient, tophat, blackhat, hitmiss;

	// 对二值图像进行开运算
	morphologyEx(src, open, MORPH_OPEN, kernel);
	namedWindow("open", WINDOW_NORMAL);
	imshow("open", open);

	// 对二值图像进行闭运算
	morphologyEx(src, close, MORPH_CLOSE, kernel);
	namedWindow("CLOSE", WINDOW_NORMAL);
	imshow("CLOSE", close);

	// 对图像进行形态学梯度运算
	morphologyEx(src, gradient, MORPH_GRADIENT, kernel);
	namedWindow("grad", WINDOW_NORMAL);
	imshow("grad", gradient);

	// 对图像进行顶帽运算
	morphologyEx(src, tophat, MORPH_TOPHAT, kernel);
	namedWindow("tophat", WINDOW_NORMAL);
	imshow("tophat", tophat);

	// 图像图进行黑帽运算
	morphologyEx(src, blackhat, MORPH_BLACKHAT, kernel);
	namedWindow("BLACKHAT", WINDOW_NORMAL);
	imshow("BLACKHAT", blackhat);

	// 对二值化图像进行击中不击中变换
	morphologyEx(src, hitmiss, MORPH_HITMISS, kernel);
	namedWindow("HITMISS", WINDOW_NORMAL);
	imshow("HITMISS", hitmiss);



	waitKey();
	return 0;
}