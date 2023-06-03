#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:积分图像主要用于快速计算某些区域像素的平均灰度。另外积分图像是比原始图像尺寸大1的新图像。
根据积分图像的计算规则的不同，可以分为3种主要的积分图像，分别是标准求和积分图像，平方求和积分图像，以及倾斜求和积分图像。

	Function:	
			void cv::integral(InputArray src, OutputArray sum, int sdepth = -1);																    // 标准求和
			void cv::integral(InputArray src, OutputArray sum, OuputArray sqsum, int sdepth = -1, int sqdepth = -1);								// 平方求和
			void cv::integral(InputArray src, OutputArray sum, OutputArray sqsum, OutputArray tilted, int sdepth=-1, int sqdepth=-1);				// 倾斜求和

*/


int main_Integral(int argc, char* argv[])
{
	// 创建一个16x16且像素值全为1的矩阵，因为16x16=256
	Mat img = Mat::ones(16,16, CV_32FC1);

	// 在图像中加入随机噪声
	RNG rng(10086);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float d = rng.uniform(-0.5, 0.5);
			img.at<float>(i, j) = img.at<float>(i, j) + d;
		}
	}

	// 计算标准求和
	Mat sum;
	integral(img, sum);
	// 为了显示方便，转化为CV_8U格式
	Mat sum8u = Mat_<uchar>(sum);

	// 计算平方求和
	Mat sqsum;
	integral(img, sum, sqsum);
	Mat sqsum8u = Mat_<uchar>(sqsum);

	// 计算倾斜求和
	Mat tilted;
	integral(img, sum, sqsum, tilted);
	Mat tilted8u = Mat_<uchar>(tilted);

	// 输出结果
	namedWindow("sum", WINDOW_NORMAL);
	namedWindow("sqsum", WINDOW_NORMAL);
	namedWindow("tilted", WINDOW_NORMAL);
	imshow("sum", sum);
	imshow("sqsum", sqsum);
	imshow("tilted", tilted);

	waitKey();
	destroyAllWindows();
	return 0;

}