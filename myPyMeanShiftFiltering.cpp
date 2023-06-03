#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:Mean-Shift法又称为均值漂移法，是一种基于颜色空间分布的图像分割算法。该算法的输出是一个经过滤色的“分色”图像，其颜色会变得渐变，并且细纹理会变得平缓。
	在Mean-Shift法中，每个像素点用一个五维向量（x,y,b,g,r)表示，前两个量是像素点在图像中的坐标，后3个量是每个像素点的颜色分量。

	Function:
		void cv::pyrMeanShiftFiltering(InputArray src, OutputArray dst, double sp, double sr, int maxLevel=1, TermCriteria termcrit=TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 5, 1);
			-src：待分割的输入图像，必须是CV_8U类型的三通道彩色图像
			-dst：分割后的输出图像，与输入图像具有相同的尺寸和数据类型
			-sp：滑动窗口的半径
			-sr：滑动窗口颜色幅度
			-maxLevel:分割金字塔缩放层数
			-termcrit：迭代算法终止条件


		cv::TermCriteria::TermCriteria(int type, int maxCount,double epsilon);
		该函数可以表示迭代算法的终止条件，主要分为满足迭代次数和满足计算精度两种。第一个参数是终止条件的类型标志，可选标志如下表所示。需要注意，由于该参数在TermCriteria类中，因此在使用时需要在
		变量前面添加类名前缀。该函数第二个参数表示最大迭代次数或者元素数，在type==TermCriteria::COUNT时发挥作用。第三个参数表示停止迭代时需要满足的计算精度或参数变化，在type==TermCriteria::EPS时
		发挥作用。


										TermCriteria()函数中终止条件的类型标志及其含义
			标志参数                     简记                            含义
		TermCriteria::COUNT               1                           迭代次数达到设定值时才停止迭代
		TermCriteria::MAX_ITER            1                           同上
		TermCriteria::EPS				  2                           当计算的精度满足要求时停止迭代

*/


int mainMeanShift(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\apple.jpg");
	if (img.empty())
	{
		cout << "图片加载失败" << endl;
		return -1;
	}

	// 分割处理
	Mat result1, result2;
	TermCriteria T10 = TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 0.1);
	pyrMeanShiftFiltering(img, result1, 20, 40, 2, T10);				// 第一次分割
	pyrMeanShiftFiltering(result1, result2, 20, 40, 2, T10);			// 第二次分割

	// 显示分割结果
	imshow("src", img);
	imshow("result1", result1);
	imshow("result2", result2);

	// 对图像提取canny边缘
	Mat imgCanny, result1Canny, result2Canny;
	Canny(img, imgCanny, 150, 200);
	Canny(result1, result1Canny, 150, 200);
	Canny(result2, result2Canny, 150, 200);

	// 显示
	imshow("imgCanny", imgCanny);
	imshow("result1Canny", result1Canny);
	imshow("result2Canny", result2Canny);


	waitKey();
	destroyAllWindows();
	return 0;

}