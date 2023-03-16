#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Laplacian算子具有各方向同性的特点，能够对任意方向的边缘进行提取，Laplacian算子是一种二阶导数算子，对噪声敏感，需要配合高斯滤波一起使用。

	Laplacian(src, dst, ddepth, ksize, scale, delta, borderType);
	参数：
		ddepth: 输出图像的数据范围,不要使用CV_8U数据类型，因为提取边缘信息有可能为负数。
		ksize:  当ksize大于1， 该函数通过sobel算子计算出图像X方向和Y方向的二阶导数，将两个方向的导数求和得到Laplacian算子。
				当ksize等于1， Laplacian算子如下：  0     1     0
				                                    1    -4     1
													0     1     0

*/

int main21AD()
{
	Mat img = imread("D://图片//1.jpg");
	if (img.empty())
	{
		cout << "图像加载错误" << endl;
		return -1;
	}

	Mat result, result_g, result_G;

	// 未进行滤波提取Laplacian边缘
	Laplacian(img, result, CV_16S, 3, 1, 0);
	convertScaleAbs(result, result);

	// 滤波后提取Laplacian边缘
	GaussianBlur(img, result_g, Size(3, 3), 5, 0);		// 高斯滤波
	Laplacian(result_g, result_G, CV_16S, 3, 1, 0);
	convertScaleAbs(result_G, result_G);

	// 显示图像
	imshow("result", result);
	imshow("result_G", result_G);
	waitKey();
	return 0;


}