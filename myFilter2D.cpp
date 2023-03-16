#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	filter2D作图像卷积，注意如果模板不是中心对称，需要将卷积模板进行旋转180°

	void filter2D(src,  dst, ddepth,  kernel, anchor,  delta, bordertype);
	卷积核为CV_32FC1类型的矩阵
	如果需要用不同的卷积模板对不同通道进行卷积运算，需要先使用split()函数将图像多个通道分离之后单独对每一个通道求卷积运算。
	中心点位置可以在卷积模板中任意指定；  卷积偏值表示在卷积步骤的计算结果的基础上加上偏值delta作为最终结果。
*/

int mainAZ()
{
	// 待卷积矩阵
	uchar points[25] = { 1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25 };
	Mat img = Mat(5, 5, CV_8UC1, points);

	// 卷积模板
	Mat kernel = (Mat_<float>(3, 3) << 1, 2, 1, 2, 0, 2, 1, 2, 1);
	Mat kernel_norm = kernel / 12;				// 卷积模板归一化

	Mat result, result_norm;					// 未归一化卷积结果和归一化卷积结果
	filter2D(img, result, CV_32F, kernel, Point(-1, -1), 2, BORDER_CONSTANT);
	filter2D(img, result_norm, CV_32F, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
	cout << "result:" << endl << result << endl;
	cout << "result_norm:" << endl << result_norm << endl;
	

	// 图像卷积
	Mat image = imread("D:\\图片\\1.jpg",0);
	if (image.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}
	Mat filter;
	filter2D(image, filter, -1, kernel_norm, Point(-1, -1), 2, BORDER_CONSTANT);
	imshow("filter", filter);
	imshow("image", image);
	waitKey();
	return 0;

	

}