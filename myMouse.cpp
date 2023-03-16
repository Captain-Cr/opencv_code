#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	鼠标响应
	setMouseCallback(string winname, MouseCallback onMouse, userdata=0); 为指定图像窗口创建鼠标响应。第一个参数是窗口名称，第二个参数是鼠标响应的回调函数，该函数在鼠标状态发生变化时被调用，是一个MouseCallback类型的函数。
	
	MouseCallback类型：（MouseCallback类型的回调函数是一个无返回值的函数）
	typedef void(*cv::MouseCallback)(int event,			# 鼠标响应事件标志，参数为EVENT_*
									 int x,				# 鼠标指针在图像坐标系中的x坐标
									 int y,				# 鼠标指针在图像坐标系中的y坐标
									 int flags,			# 鼠标响应标志，参数为EVENT_FLAG_*形式。
									 void *userdata)	# 传递给回回调函数的可选参数

	鼠标响应就是当鼠标位于对应的图像窗口内时，时刻检测鼠标状态，当鼠标状态发生改变时，调用回调函数。                 
*/



Mat img3, imgPoint;			// 全局的图像
Point prePoint;				// 前一时刻鼠标的坐标，用于绘制直线
void mouse(int event, int x, int y, int flags, void *);		// 声明鼠标回调函数

int main213()
{
	img3 = imread("D:\\图片\\lena.jpg");
	if (img3.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}

	img3.copyTo(imgPoint);			// 深拷贝
	imshow("图像窗口1", img3);
	imshow("图像窗口2", imgPoint);

	// 设置鼠标响应
	setMouseCallback("图像窗口1", mouse, 0);			
	waitKey();
	return 0;

}



void mouse(int event, int x, int y, int flags, void*)
{
	if (event == EVENT_RBUTTONDOWN)				// 单击右键
	{
		cout << "点击鼠标左键才可以绘制轨迹" << endl;
	}

	if (event == EVENT_LBUTTONUP)					// 单击左键，输出坐标 
	{
		prePoint = Point(x, y);
		cout << "轨迹起始坐标为：" << prePoint << endl;
	}

	if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))		// 按住鼠标左键移动
	{
		// 通过改变图像像素显示鼠标移动轨迹
		imgPoint.at<Vec3b>(y, x) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y, x - 1) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y, x + 1) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y+1, x) = Vec3b(0, 0, 255);
		imgPoint.at<Vec3b>(y+1, x) = Vec3b(0, 0, 255);
		imshow("图像窗口2", imgPoint);

		// 通过绘制直线显示鼠标移动规制
		Point pt(x, y);
		line(img3, prePoint, pt, Scalar(0, 0, 255), 2, 5, 0);
		prePoint = pt;
		imshow("图像窗口1", img3);

	}
	


}