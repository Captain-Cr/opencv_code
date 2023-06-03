#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description:漫水填充法是根据像素灰度值之间的差值寻找相同区域以实现分割。
	漫水法步骤：
		1、选择种子点（x，y）
		2、以种子点为中心，判断4-邻域或者8-邻域的像素值与种子点像素的差值，将差值小于阈值的像素点添加到区域内；
		3、将新加入的像素点作为新的种子点，反复执行第二步，直到没有新的像素点被添加进该区域为止。

	Function:
		1、int cv::floodFill(InputOutputArray image,				// 输入及输出图像，可以为CV8U_或者CV_32F数据类型的单通道或者三通道图像
							 InputOutputArray mask,					// 掩码矩阵，尺寸比输入图像宽和高各大2的单通道图像，用于标记漫水法填充的区域
							 Point seenpoint,						// 种子点
							 Scalar newval,						    // 归入种子点区域内像素点的新像素值
							 Rect* rect = 0,						// 种子点漫水填充区域的最小矩形边界，默认值为0，表示不输出边界
							 Scalar loDiff = Scalar(),				// 添加进种子点区域条件的下界差值，当邻域某像素点的像素值与种子点像素值的差值大于该值时，该像素点被添加进种子点所在的区域
							 Scalar upDiff = Scalar(),				// 添加进种子点区域条件的上界差值，当种子点像素值与邻域某像素点的像素值的差值小于该值时，该像素点被添加进种子点所在的区域
							 int flags = 4							// 漫水填充法的操作标志，由3部分组成，分别表示邻域种类、掩码矩阵中被填充像素点的像素值和填充算法的规则，可以下表中给出。
							 );

						floodFill()函数漫水填充法的操作标志
		标志				简记						含义
  FLOODFILL_FIXED_RANGE    1<<16                   如果设置该参数，那么仅考虑当前像素点与初始种子点像素值之间的差值，否则考虑新种子点像素值与当前像素值之间的差异，即范围是否浮动的标志
  FLOODFILL_MASK_ONLY	   1<<17				   如果设置，那么该函数不会更改原始图像，即忽略第四个参数new Val，只生成掩码矩阵


		2、int cv::floodFill(InputOutputArray image,
							 Point seedPoint,
							 Scalar newVal,
							 Rect* rect = 0,
							 Scalar loDiff = Scalar(),
							 Scalar upDiff = Scalar(),
							 int flags = 4
							 )
							 
							 
*/

int main_floodFill(int argc, char* argv[])
{
	Mat img = imread("D:\\图片\\cat.jpg");
	if (img.empty())
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}

	RNG rng(10086);		// 随机数，用于随机生成像素

	// 设置操作标志flags
	int connectivity = 8;			// 连通邻域方式
	int maskVal = 255;				// 掩码图像的数值
	int flags = connectivity | (maskVal << 8) | FLOODFILL_FIXED_RANGE;		// 漫水填充操作方式标志

	// 设置与选中像素点的差值
	Scalar loDiff = Scalar(20, 20, 20);
	Scalar upDiff = Scalar(20, 20, 20);

	// 声明掩码矩阵变量
	Mat mask = Mat::zeros(img.rows + 2, img.cols + 2, CV_8UC1);

	while (true)
	{
		// 随机生成图像中的某一像素点
		int py = rng.uniform(0, img.rows - 1);
		int px = rng.uniform(0, img.cols - 1);
		Point point = Point(px, py);

		// 彩色图像中填充的像素值
		Scalar newVal = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

		// 漫水填充函数
		int area = floodFill(img, mask, point, newVal, &Rect(), loDiff, upDiff, flags);

		// 输出像素点和填充的像素数目
		cout << "像素点x：" << point.x << "   y:" << point.y
			<< "   填充像素数目" << area << endl;

		// 输出填充的图像结果
		imshow("填充的彩色图像", img);
		imshow("掩码图像", mask);

		// 判断是否结束程序
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			break;
		}

	}
	destroyAllWindows();
	return 0;
}