#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*																	-1  0   1			
	sobel算子：													    -2  0   2                                           
		第一步： 提取x方向的边缘。  x方向的一阶边缘检测算子为       -1  0   1      之所以为x方向，拿[-1, 0, 1]为例， df(x, y)/dx = (f(x+1, y) -f(x-1, y)) / 2


		                                                     -1  -2   -1
		第二步： 提取y方向边缘。 y方向一阶边缘检测算子为      0   0    0     之所以是y方向，拿[-1, 0, 1].T()为例，   df(x, y) / dy = (f(x, y+1) - f(x, y-1)) /2
		                                                      1   2    1

		第三步： 综合两个方向的边缘信息，有两种方法：
				（1） I(x, y) = sqrt((Iy(x, y)² + Ix(x, y)²);
				（2） I(x, y) = |Ix(x, y)²| + |Iy(x, y)|²；


		Sobel(src, dst, ddpeth, dx, dy, ksize, scale, delta, borderType);
		 dx,dy: 分别是X、Y方向的差分阶数；  scale：对导数计算结果进行缩放的缩放因子；  delta：偏值，在计算结果加上偏值；

		注意：因为提取边缘信息时有可能出现负数，所以不要使用CV_8U数据类型的输出图像。该函数第4、5、6个参数是控制图像边缘检测效果的关键参数，这三者存在的关系是任意一个方向的差分阶数都需要小于算子的尺寸。

		                         -3    0    3                                -3    -10     -3
		Scharr算子：        Gx = -10   0    10                         Gy =  0      0       0		
		                         -3    0    3                                3      10      3

		Scharr(src, dst, ddepth, dx, dy, scale, delta, borderType);  
		该函数第4、5个参数分别是提取x方向边缘和y方向边缘的标志，要求这两个参数只能有一个参数为1， 且不能同时为0.   默认使用3x3滤波器，并且无法改变。
*/


int mainAFEA()
{
	Mat img = imread("D:\\图片\\1.jpg", 0);
	if (img.empty())
	{
		cout << "图片加载出错！" << endl;
		return -1;
	}

	Mat resultX, resultY, resultXY;

	// x方向一阶边缘
	Sobel(img, resultX, CV_16S, 2, 0, 1);
	convertScaleAbs(resultX, resultX);

	// y方向一阶边缘
	Sobel(img, resultY, CV_16S, 0, 1, 3);
	convertScaleAbs(resultY, resultY);

	// 整个图像的一阶边缘
	resultXY = resultX + resultY;

	// 显示图像
	imshow("resultX", resultX);
	imshow("resultY", resultY);
	imshow("resultXY", resultXY);



	Mat res1, res2, res3;
	// x方向一阶边缘
	Scharr(img, res1, CV_16S, 1, 0);
	convertScaleAbs(res1, res1);

	// y方向一阶边缘
	Scharr(img, res2, CV_16S, 0, 1);
	convertScaleAbs(res2, res2);

	// 整幅图像的一阶边缘
	res3 = res1 + res2;

	// 显示图像
	imshow("res1", res1);
	imshow("res2", res2);
	imshow("res3", res3);







	waitKey();
}

