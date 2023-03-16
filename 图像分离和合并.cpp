/*
	实现图像的多通道分离和合并操作
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main_124(int argc, char* argv[])
{
	Mat img = imread("E:\\data\\1.png");
	if (img.empty())
	{
		cout << "图像加载错误！！！" << endl;
		return -1;
	}

	Mat HSV;								// HSV模型
	cvtColor(img, HSV, COLOR_BGR2HSV);

	Mat imgs0, imgs1, imgs2;				// 用于存放数组类型的结果
	Mat imgv0, imgv1, imgv2;				// 用于存放vector类型的结果
	Mat result0, result1, result2;			// 多通道合并的结果


	// 输入数组参数的多通道分离和合并
	Mat imgs[3];							// 图像数组
	split(img, imgs);						// 拆分图像
	imgs0 = imgs[0];
	imgs1 = imgs[1];
	imgs2 = imgs[2];
	imshow("BGR-B通道", imgs0);				// 显示图像
	imshow("BGR-G通道", imgs1);			
	imshow("BGR-R通道", imgs2);
	
	
	imgs[2] = img;							// 将数组中的图像通道数变成不一致
	merge(imgs, 3, result0);				// 合并图像
	// imshow("result0",result0);			// imshow最多显示4个通道，因此结果在Image Watch中查看，  这里result是5个通道
	Mat zero = Mat::zeros(img.rows, img.cols, CV_8UC1);
    // 将第0和第2个通道置0
	imgs[0] = zero;
	imgs[2] = zero;
	merge(imgs, 3, result1);				// 用于还原G通道的真实情况，合并结果为绿色
	imshow("result1", result1);

	// 输入vector参数的多通道分离与合并
	vector<Mat> imgv;
	split(HSV, imgv);
	imgv0 = imgv.at(0);					// 获取第一个通道图片
	imgv1 = imgv.at(1);					// 后去第二个通道图片
	imgv2 = imgv.at(2);
	imshow("HSV-H通道", imgv0);				// 显示分离后H通道的像素值
	imshow("HSV-S通道", imgv0);				// 显示分离后S通道的像素值
	imshow("HSV-V通道", imgv0);				// 显示分离后V通道的像素值
	imgv.push_back(HSV);					// 将vector中的图像通道数变成不一致
	merge(imgv, result2);					// 合并图像
	// imshow("result1",result1);			// imshow最多显示4个通道，因此结果在Image Watch中查看，  这里result是5个通道
	
	
	
	
	
	
	
	waitKey();














}