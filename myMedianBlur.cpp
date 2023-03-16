#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	中值滤波算法：
		1、把窗口放到元素上；
		2、取出窗口中的元素；
		3、将窗口中的元素排序；
		4、选出这些元素的中值；
*/


void myMedianBlur()
{
	// 设置滤波的窗口为3x3
	Mat image = imread("D:\\图片\\1.jpg", 0);
	Mat salt = imread("D:\\图片\\salt.jpg");

	/*uchar points[25] = { 1,2,3,4,5,
						6,7,8,9,10,
						11, 12, 13, 14,15,
						16, 17,18, 19, 20,
						21,22, 23, 24, 25 };
	Mat image(5, 5, CV_8UC1, points);*/

	if (image.empty())
	{
		cout << "图片加载错误！" << endl;
	}

	Mat img;		// 用于输出opencv的medienBlur（）
	image.copyTo(img);
	Mat result;			// 用于输出中值滤波后的结果
	vector<int> grayv(9);		// 3x3的滤波模板
	for (int i = 1; i < image.rows - 1; i++)			// 要空一个像素
	{
		uchar *preptr = image.ptr(i - 1);			// (i,j)是要改变的坐标点坐标
		uchar *ptr = image.ptr(i);
		uchar *nextptr = image.ptr(i + 1);
		uchar *imgptr = img.ptr(i);		// 用于输出中值滤波的图片的行指针

		for (int j = 1; j < image.cols - 1; j++)
		{
			grayv[0] = (preptr[j - 1]);			// 滤波模板的第一个元素，preptr： 上一行的指针
			grayv[1] = (preptr[j]);
			grayv[2] = (preptr[j + 1]);
			grayv[3] = (ptr[j - 1]);			// 滤波模板从当前行开始，ptr：当前行的指针
			grayv[4] = (ptr[j]);
			grayv[5] = (ptr[j + 1]);
			grayv[6] = (nextptr[j - 1]);		// nextptr： 下一行的指针
			grayv[7] = (nextptr[j]);
			grayv[8] = (nextptr[j + 1]);

			sort(grayv.begin(), grayv.end());		// 对vector进行排序，用迭代器
			imgptr[j] = int(grayv[4]);			// 将当前像素设置为中值的值

		}
	}
	//cout << img << endl;

	medianBlur(image, result, 3);		// 调用opencv中值滤波函数

	Mat salt_blur;
	medianBlur(salt, salt_blur, 3);
	//cout << result << endl;

	imshow("原图", image);
	imshow("中值滤波后", img);
	imshow("opencv自带滤波", result);

	imshow("椒盐", salt);
	imshow("中值滤波去除椒盐", salt_blur);
	waitKey(0);
	
}












int main_fae()
{
	myMedianBlur();
	return 0;
}