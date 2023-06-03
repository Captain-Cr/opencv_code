#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:Grabcut是重要的图像分割算法，其使用高斯混合模型估计目标区域的背景和前景，并通过迭代的方法解决了能量函数最小化的问题。

	Function：
		void cv::grabcut(InputArray img, InputOutputArray mask, Rect rect, InputOutputArray bgdModel, InputOutputArray fgdModel, int iterCount, int mode=GC_EVAL);
	Paramenets:
		img:输入的待分割图像，为CV_8U数据类型的三通道图像。
		mask：用于输入、输出的CV_8U单通道掩码图像，图像中像素值的取值范围及其含义在表1中给出
		rect：包含对象的ROI区域，该参数仅在mode=GC_INIT_WITH_RECT时使用
		bgdModel:背景模型的临时数组
		fgdModel：前景模型的临时数组
		iterCount:算法需要进行的迭代次数
		mode:分割模式标志，该参数的可选择范围及其含义在表2中给出

							grabcut()函数中掩码图像像素值范围和含义
		标志参数						简记							含义
		GC_BGD							 0                            明显为背景的像素
		GC_FGD							 1                            明显为前景（对象）的像素
		GC_PR_BGD						 2							  可能为背景的像素
		GC_PR_FGD						 3							  可能为前景（对象）的像素


							grabcut（）函数中分割模式标志取值范围和含义
		标志参数						 简记							含义
	GC_INIT_WITH_RECT					  0                          使用提供的矩形初始化状态和掩码，之后根据算法进行迭代更新
	GC_INIT_WITH_MASK				      1                          使用提供的掩码初始化状态，可以组合GC_INIT_WITH_RECT和GC_INIT_WITH_MASK。然后，使用GC_BGD自动初始化ROI外部所有像素
	GC_EVAL								  2                          算法应该恢复
	GC_EVAL_FREEZE_MODEL                  3                          只使用固定模型运行Grabcut算法（单次迭代）


*/


int mainGrabcut(int argc, char* argv[])
{
	Mat img = imread("D:\\图片\\lena2.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 绘制矩形
	Mat imgRect;
	img.copyTo(imgRect);
	Rect rect(50, 20, 150, 180);
	rectangle(imgRect, rect, Scalar(255, 255, 255), 2);
	imshow("选择的矩形区域", imgRect);

	// 进行分割
	Mat bgdmodel = Mat::zeros(1, 65, CV_64FC1);
	Mat fgdmodel = Mat::zeros(1, 65, CV_64FC1);
	Mat mask = Mat::zeros(img.size(), CV_8UC1);
	grabCut(img, mask, rect, bgdmodel, fgdmodel, 5, GC_INIT_WITH_RECT);

	// 将分割出的前景重新绘制
	Mat result;
	for (int row = 0; row < mask.rows; row++)
	{
		for (int col = 0; col < mask.cols; col++)
		{
			int n = mask.at<uchar>(row, col);
			// 将明显是前景和可能是前景的区域都保留
			if (n == 1 || n == 3)
			{
				mask.at<uchar>(row, col) = 255;
			}
			// 将明显是背景和可能是背景的区域都删除
			else
			{
				mask.at<uchar>(row, col) = 0;
			}
		}
	}
	bitwise_and(img, img, result, mask);
	imshow("分割结果", result);



	waitKey();
	destroyAllWindows();
	return 0;
}