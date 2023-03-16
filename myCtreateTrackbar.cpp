#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	通过滑动窗口滑动条trackbar改变图像的亮度
*/


int value;				// 亮度值
Mat img, img2;			// 全局
void callback(int, void*);			// 声明回调函数
char win[] = "改变亮度";




int mainA()
{
	img = imread("D:\\图片\\lena.jpg");
	if (img.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}

	
	namedWindow(win, WINDOW_AUTOSIZE);
	createTrackbar("val", win, &value, 600, callback);
	waitKey();
	return 0;

}

static void callback(int, void*)
{
	float a = value / 100.0;
	img2 = img * a;
	imshow(win, img2);
}