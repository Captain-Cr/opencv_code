#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace  cv;



/*
	图像边缘：图像中像素灰度值突然发生变化的区域。函数值的变化趋势可以用函数的导数描述，函数值增大，导数也变大； 函数值变小，导数也变小； 因此可以通过寻找导数值较大的区域寻找函数中突然变化的区域。

	图像是离散的信号，因此可以用临近的两个像素差值来表示像素灰度值函数的导数，  df(x, y) / dx = f(x, y) - f(x-1, y);			对x轴方向求导对应的滤波器为[-1, 1]

	如果想要表示某个像素出的梯度，最接近的方式是求取前一个像素和后一个像素的差值，  即 df(x, y) / dx = f(x+1, y) - f(x-1, y) / 2   对应的滤波器为[-0.5, 0, 0.5]

	计算45°方向的梯度可以用  XY = 1  0                  YX = 0   1
                                   0  -1   	                  -1  0


	计算矩阵中所有数据的绝对值：    convertScaleAbs(src, dst, alpha=1,  beta=0);
	该函数可以求取矩阵中所有数据的绝对值，第三个、第四个参数为绝对的缩放和数据上的偏移。  计算公式：  dst(I) = |src(I)  * alpha + beta

	由于求取边缘的结果有可能是负数， 因此滤波后的图像数据类型不要用-1， 而应该改为CV_16S
*/

int mainafvx()
{
	// 创建边缘检测滤波器
	Mat kernel1 = (Mat_<float>(1, 2) << 1, -1);						// x方向的边缘检测滤波器
	Mat kernel2 = (Mat_<float>(1, 3) << 1, 0, -1);					// x方向的边缘检测滤波器
	Mat kernel3 = (Mat_<float>(3, 1) << 1, 0, -1);					// x方向的边缘检测滤波器

	Mat kernelXY = (Mat_<float>(2, 2) << 1, 0, 0, -1);					// 由左上到右下边缘检测滤波器
	Mat kernelYX = (Mat_<float>(2, 2) << 0, -1, 1, 0);					// 由右上到左下边缘检测滤波器

	// 读取图像，黑白图像边缘检测结果较为明显
	Mat img = imread("D:\\图片\\1.jpg", 0);
	if (img.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}
	Mat result1, result2, result3, result4, result5, result6;

	// 检测图像边缘
	// 以[1, -1]检测水平方向边缘
	filter2D(img, result1, CV_16S, kernel1);			// 注意这里要是CV_16S类型
	convertScaleAbs(result1, result1);				

	// 以[1, 0, -1]检测水平方向边缘
	filter2D(img, result2, CV_16S, kernel2);			// 注意这里要是CV_16S类型
	convertScaleAbs(result2, result2);

	// 以[1, 0, -1]检测垂直方向边缘
	filter2D(img, result3, CV_16S, kernel3);			// 注意这里要是CV_16S类型
	convertScaleAbs(result3, result3);

	// 检测由左上到右下方向的边缘
	filter2D(img, result4, CV_16S, kernelXY);		  
	convertScaleAbs(result4, result4);

	// 检测由右上到左下方向的边缘
	filter2D(img, result5, CV_16S, kernelYX);
	convertScaleAbs(result5, result5);

	// 整幅图像的边缘
	result6 = result2 + result3;


	// 显示边缘检测结果
	imshow("result1", result1);
	imshow("result2", result2);
	imshow("result3", result3);
	imshow("result4", result4);
	imshow("result5", result5);
	imshow("result6", result6);

	waitKey();

}