#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	distanceTransform(src, dst, labels, distanceType, maskSize, labelType=DIST_LABEL_CCOMP);
	用于实现图像的距离变换，即统计图像中所有像素距离0像素的最小距离。第一个参数为待距离变换的输入图像，输入图像必须是CV_8U的单通道图像；
	第二个参数：距离变换的图像，距离有可能会大于256，输出图像的数据类型可选CV_8U或CV_32F.
	第三个参数是输出原始图像的离散Voronoi图，输出图像是数据类型为CV_32S的单通道图像，尺寸和原图相同。
	第四个参数是距离变换过程中使用的距离种类，有(欧式、街区、棋盘， DIST_l2,DIST_L1,DIST_C）；
	第五个参数是求取路径时候的掩码矩阵尺寸，默认选择掩码矩阵尺寸为3x3.
	最后一个参数是构建标签数组的类型，当labelType==DIST_LABEL_CCOMP时，该函数会自动在输入图像中找到0像素的连通分量，并用相同的标签标记他们；
	当labelType==DIST_LABEL_PIXEL,该函数扫描输入图像并用不同的标签标记所有0像素。

	// 重载
	distanceTransform(src, dst, distanceType, maskSize, dstType=CV_32F)
*/

int mainga(int argc, char* argv[])
{
	// 构建简易矩阵，用于求取像素之间的距离
	Mat a = (Mat_<uchar>(5, 5) << 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 0, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1);

	Mat dist_L1, dist_L2, dist_c;

	// 计算街区距离
	distanceTransform(a, dist_L1, DIST_L1, 3, CV_8U);
	cout << "街区距离："<<endl << dist_L1 << endl;

	// 计算欧式距离
	distanceTransform(a, dist_L2, DIST_L2, 5, CV_8U);
	cout << "欧式距离："<<endl << dist_L2 << endl;

	// 计算棋盘距离
	distanceTransform(a, dist_c, DIST_C, 5, CV_8U);
	cout << "棋盘距离：" << endl << dist_c << endl;
	
	// 对图像进行距离变换
	Mat img = imread("D:\\图片\\1.jpg",0);
	if (img.empty())
	{
		cout << "图像加载错误" << endl;
		return -1;
	}

	Mat riceBW, riceINV;

	// 将图像转化为二值图像，同时把黑白区域进行颜色互换
	threshold(img, riceBW, 150, 255, THRESH_BINARY);
	threshold(img, riceINV, 150, 255, THRESH_BINARY_INV);

	// 距离变换
	Mat dist, dist_INV;
	distanceTransform(riceBW, dist, 1, 3, CV_32F);    // 为了显示清晰，将数据类型变成CV_32F
	distanceTransform(riceINV, dist_INV, 1, 3, CV_8U);

	imshow("riceBW", riceBW);
	imshow("dist", dist);
	imshow("riceBW_INV", riceINV);
	imshow("dist_INV", dist_INV);
	waitKey();
	return 0;


}