#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:分水岭算法和漫水填充法类似，区别在于漫水填充法是从某个像素进行分割，是一种局部分割算法；而分水岭算法是从全局出发，需要对全局进行分割。

	Function:
		void cv::watershed(InputArray Image, InputOutputArray maskers);

	Paramerates:
		Images:输入图像，需要设置为CV_8U的数据类型的三通道图像
		maskers：输入/输出CV_32S数据类型的单通道图像的标记结果，与原图像具有相同的尺寸。

	Stage：
		每个标记区域被表示为具有像素值1,2,3等的一个或多个连通分量，标记图像的尺寸与输入图像相同，但数据类型为CV_32S，可以使用findContours()函数和drawContours()函数从二值掩码中得到此类标记图像，
		标记图像中所有没有被标记的像素值都为0，在函数输出时，两个区域之间的分割线用-1表示。
*/



int mainWatershed(int argc, char* argv[])
{
	Mat img = imread("D:\\abc.png");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	
	Mat gray, canny;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//threshold(gray, thresh, 120, 255, THRESH_BINARY);
	Canny(gray, canny, 80, 150);

	// 进行填充，每个轮廓填充不同的值，分别为1,2，。。。
	vector<vector<Point>> contours;				// 轮廓点
	vector<Vec4i> hierarchy;						// 描述轮廓层级
	findContours(canny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// 进行绘制填充
	Mat maskWatershed = Mat::zeros(img.size(), CV_32S);
	for (int i = 0; i < contours.size(); i++)
	{
		// 对每个轮廓进行绘制填充
		drawContours(maskWatershed, contours, i, Scalar(i + 1), -1, 8, hierarchy, INT_MAX);
	}
	// 分水岭法， 需要对原图像进行处理
	watershed(img, maskWatershed);


	// 分水岭后图像边缘为-1， 背景为0， 其余的为轮廓1,2，。。。
	RNG rng(10086);
	vector<Vec3b> colors;			// 随机生成几种颜色
	for (int j = 0; j < contours.size(); j++)
	{
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	
	// 遍历图像，将图像各个部分进行显示
	Mat resultImg = Mat::zeros(img.size(), CV_8UC3);		// 结果分割图像
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			// 绘制每个区域的颜色
			int index = maskWatershed.at<int>(y, x);
			// 区域间边界被置为-1, 用白色绘制边界
			if (index == -1)
			{
				resultImg.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
			}
			// 背景被设置0， 用黑色绘制
			else if (index <= 0 || index > contours.size())
			{
				resultImg.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
			}
			// 其余的区域，用相应区域索引的颜色进行绘制
			else
			{
				resultImg.at<Vec3b>(y, x) = colors[index - 1];
			}
		}
	}
	addWeighted(img, 0.5, resultImg, 0.5, 1, resultImg);
	imshow("result", resultImg);
	

	// 绘制出每个区域的图像
	for (int k = 1; k <= contours.size(); k++)
	{
		Mat resImg1 = Mat(img.size(), CV_8UC3);
		for (int a = 0; a < resultImg.rows; a++)
		{
			for (int b = 0; b < resultImg.cols; b++)
			{
				int index = maskWatershed.at<int>(a, b);
				if (index == k)
				{
					resImg1.at<Vec3b>(a, b) = img.at<Vec3b>(a, b);		// 将原图中属于区域index的像素截取下来
				}
				else
				{
					resImg1.at<Vec3b>(a, b) = Vec3b(0, 0, 0);			// 不属于区域index的置0
				}

			}
		}
		imshow(to_string(k), resImg1);
	}

	

	imshow("img", img);
	imshow("canny", canny);

	waitKey();
	destroyAllWindows();
	return 0;
}
