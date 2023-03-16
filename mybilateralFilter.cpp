#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	双边滤波对高频率的波动信号起到平滑的作用，同时保留大幅值变化的信号波动，进而实现对保留图像中边缘信息的作用。
	双边滤波器是两个滤波器的结合，分别考虑空域信号和值域信号。

	双边滤波器：	bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType);
	其中： d表示滤波过程中每个像素领域的直径；   sigmaColor: 颜色空间滤波器的标准差值，这个差值越大，表明该像素领域内有越多的颜色被混合在一起，产生较大的半相等颜色区域；
	sigmaSpace:  空间坐标中滤波器的标准差值；

	滤波器的直径越大，滤波效果越明显；滤波器直径相同时， 标准差值越大，滤波效果越明显；
*/

int mainaeeaf()
{
	Mat img1 = imread("D:\\图片\\1.jpg");
	Mat img2 = imread("D:\\图片\\lena.jpg");
	if (img1.empty() || img2.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}

	Mat result1, result2, result3, result4;

	// 验证不同滤波器直径的滤波效果
	bilateralFilter(img1, result1, 9, 50, 25 / 2);		// 直径为9
	bilateralFilter(img1, result2, 25, 50, 25 / 2);		// 直径为25

	// 验证不同标准差值的滤波效果
	bilateralFilter(img2, result3, 9, 9, 9);			// 不同标准差值
	bilateralFilter(img2, result4, 9, 200, 200);

	//显示原图
	imshow("img1", img1);
	imshow("img2", img2);
	// 不同直径滤波结果
	imshow("result1", result1);
	imshow("result2", result2);
	imshow("result3", result3);
	imshow("result4", result4);

	waitKey();
	return 0;


}