#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


/*
	截图、深浅拷贝
*/

int main213(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	Mat noobcv = imread("E:\\cat_and_dog.jpg");

	if (img.empty() || noobcv.empty())
	{
		cout << "图像加载错误！！！" << endl;
		return -1;
	}
	
	Mat Roi1, Roi2, Roi2_copy, mask, img2, img_copy, img_copy2;
	resize(noobcv, mask, Size(200, 200));		// mask是noobcv图片的缩放
	img2 = img;		// 浅拷贝
	

	// 深拷贝的两种方法
	img.copyTo(img_copy2);
	copyTo(img, img_copy, img);

	// 两种在图中截取Roi的方式
	Roi1 = img(Rect(206, 206, 200, 200));
	Roi2 = img(Range(300, 500), Range(300, 500));

	img(Range(300, 500), Range(300, 500)).copyTo(Roi2_copy);		// 深拷贝
	mask.copyTo(Roi1);				// 在图像中加入部分图像

	imshow("加入noobcv后图像", img);
	imshow("ROi对ROi2的影响", Roi2);
	imshow("深拷贝的Roi2_copy", Roi2_copy);
	circle(img, Point(300, 300), 20, Scalar(0, 0, 255), -1);		//绘制一个圆
	imshow("深拷贝的img2", img2);
	imshow("深拷贝的img_copy", img_copy);
	imshow("深拷贝的img_copy2", img_copy2);
	imshow("画圆对roi的影响", Roi1);
	waitKey();
	return 0;













}
