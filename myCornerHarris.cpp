#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description:像素值的局部最大峰值即为Harris角点，以某一个像素为中心构建一个滑动窗口，通过线性叠加得到窗口所有像素值的衡量系数，当滑动窗口无论向哪个方向移动像素值衡量系数都缩小时，滑动窗口中心点对应的像素就为Harris角点

	Function:
		void cv::cornerHarris(InputArray src, OutputArray dst, int blockSize, int ksize, double k, int borderType=BORDER_DEFAULT);
	该像素能够计算出图像每个像素点的Harris评价系数，通过对比该系数大小，可以确定该点是否为harris角点。第一个参数是待检测Harris角点的输入图像，图像必须是CV_8U或CV_32F的单通道灰度图像。
	第二个参数是存放Harris评价系数R的矩阵，R可能是负数或小数，因此该图像矩阵的数据类型为CV_32F。第三个参数是邻域的大小，通常选2.第四个参数是计算提取信息的Sobel算子的半径，该参数需要是奇数，
	多使用3或者5.第五个参数是权重系数，一般取0.02 - 0.04。最后一个参数是像素外推算法标志。
*/

int mainHarrisCorner(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\lena.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 转化为灰度图
	Mat gray; 
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// 计算harris角点评价系数
	Mat harris;
	int blocksize = 2;			// 邻域半径
	int apertureSize = 3;
	cornerHarris(gray, harris, blocksize, apertureSize, 0.04);

	// 归一化
	Mat harrisn;
	normalize(harris, harrisn, 0, 255, NORM_MINMAX);
	// 将图像数据变成CV_8U
	convertScaleAbs(harrisn, harrisn);

	// 寻找harris角点
	vector<KeyPoint> keypoints;
	for (int i = 0; i < harrisn.rows; i++)
	{
		for (int j = 0; j < harrisn.cols; j++)
		{
			int R = harrisn.at<uchar>(i, j);
			if (R > 125)
			{
				// 将角点存入KeyPoint中
				KeyPoint keypoint;
				keypoint.pt.y = i;
				keypoint.pt.x = j;
				keypoints.push_back(keypoint);
			}

		}
	}

	// 绘制角点并进行显示
	drawKeypoints(img, keypoints, img);
	imshow("系数矩阵", harrisn);
	imshow("harris角点", img);



	waitKey();
	destroyAllWindows();
	return 0;
}