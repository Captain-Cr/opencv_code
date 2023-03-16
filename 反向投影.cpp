#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	反向投影：就是首先计算某一特征的直方图模型，然后使用该模型去寻找图像中是否存在该特征的方法；

	calcBackProject(const Mat *images,		// 输待统计直方图图像数组， 只能是CV_8U, CV_16U, CV_32F
					int nimages,			// 输入图像的数量
					const int *channels,	// 需要统计的通道索引数组， 第一个图像的通道索引从0到image[0].channel()-1,第二个图像通道索引从images[0].channels()到images[0].channels+images[1].channels()-1... 以此类推
					InputArray hist,		// 输入直方图， 输入模板图像的直方图统计结果
					backProject,			// 目标为反向投影图像，与images[0]具有相同尺寸和数据类型的单通道图像
					ranges,					// 每个图像通道中灰度值的取值范围
					scale,					// 输出反向投影矩阵的比例因子
					uniform,				// 直方图是否均匀的标志符， 默认下是均匀（True）
	
	该函数用于在输入图像中寻找与特定图像最匹配的点或区域，即对图像直方图反向投影。

	步骤：  1、加载img， temp模板（从img中截取）；
			2、将两张图片由BGR 2 HSV;
			3、统计H-S直方图
			4、直方图归一化并绘制H-S二维直方图；
			5、调用calcBackProject().
	
*/


void drawHist(Mat &hist, int type, string name)
{
	int hist_w = 500;
	int hist_h = 400;
	Mat histImg = Mat::zeros(hist_w, hist_h, CV_8UC3);

	// 归一化
	normalize(hist, hist, 255, 0, type, -1, Mat());
	namedWindow(name, WINDOW_AUTOSIZE);
	imshow(name, hist);

}




int mainaacx(int argc, char* argv[])
{
	Mat img = imread("D:\\图片\\1.jpg");
	if (img.empty())
	{
		cout << "图片加载错误!" << endl;
		return -1;
	}

	Mat temp = img(Rect(100, 100, 100, 100));		// 模板图像， 也就是某一特征的图像

	imshow("img", img);
	imshow("temp", temp);


	// 2、将图片转化为hsv空间
	Mat img_hsv, temp_hsv;
	cvtColor(img, img_hsv,COLOR_BGR2HSV);
	cvtColor(temp, temp_hsv, COLOR_BGR2HSV);

	// 3、统计h-s直方图
	Mat hist, hist2;
	int h_bins = 32; int s_bins = 32;			// 每个通道的直方图维度，就是像素的最大值，  这里是二维，所以要用两个数的数组
	int histSize[] = { h_bins, s_bins };		
	// H通道值的范围在0-179
	float h_ranges[] = { 0, 180 };
	// S通道值的范围在0-255
	float s_ranges[] = { 0, 255 };
	const float* ranges[] = { h_ranges, s_ranges };		// 范围指针数组，  每个通道的范围
	int channels[] = { 0, 1 };                  // 统计的通道索引
	calcHist(&temp, 1, channels, Mat(), hist, 2, histSize, ranges);			// 统计模板的h-s直方图
	
	// 4、直方图归一化并绘制h-s二维直方图
	drawHist(hist, NORM_INF, "hist");

	// 5、调用calcBackProject()
	Mat backProject;
	calcBackProject(&img_hsv, 1, channels, hist, backProject, ranges, 1.0);		// 直方图方向投影

	imshow("反向投影", backProject);
	waitKey();

	return 0;


}