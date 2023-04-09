#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	功能描述：傅里叶变换进行卷积

	傅里叶变换可以将两个矩阵的卷积转化为两个矩阵的傅里叶变换结果的乘积（卷积定理，频域的乘积等于空域的卷积），通过这种方式可以极大地提高卷积的计算速度。

	函数原型： void cv::mulSpectrums(InputArray a, InputArray b, OutputArray c, int flag, bool conjB = false);
	  该函数能够实现两个离散傅里叶变换后的矩阵的每个元素之间的乘法（卷积）。该函数的前两个参数是输入的需要相乘的矩阵，这两个参数的数据类型和尺寸必须相同，并且同时为复数共轭格式的单通道频谱或者双通道频谱，数值可通过dft()获得。
	第三个参数是计算频域乘积后的输出矩阵，与输入矩阵具有相同的尺寸和数据类型。最后两个参数是运算过程的操作标志，当最后一个参数为false时，表示输入矩阵之间的乘法，当最后一个参数为true时，表示前一个数组的元素与第二个数组的复数
	共轭的乘法。

	代码讲解：在该程序中，首先需要将图像和卷积核扩展到相同的最优傅里叶变换尺寸，之后分别进行离散傅里叶变换，并对变换结果进行乘积，最后对乘积结果进行离散傅里叶变换的逆变换并归一化得到最终结果。
*/



int mainSpectrums(int argc, char* argv[])
{
	Mat img = imread("D:\\图片\\1.jpg");
	resize(img, img, Size(512, 512));
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat grayfloat = Mat_<float>(gray);		// 更改图像类型为float
	Mat kernel = (Mat_<float>(5, 5) << 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1);

	// 构建输出图像
	Mat result;
	int rwidth = abs(grayfloat.rows - kernel.rows) + 1;
	int rheight = abs(grayfloat.cols - kernel.cols) + 1;
	result.create(rwidth, rheight, grayfloat.type());

	// 计算最优离散傅里叶变换尺寸
	int width = getOptimalDFTSize(grayfloat.cols + kernel.cols - 1);
	int height = getOptimalDFTSize(grayfloat.rows + kernel.rows - 1);

	// 改变输入图像尺寸
	Mat tempA;
	int A_T = 0;
	int A_B = width - grayfloat.rows;
	int A_L = 0;
	int A_R = height - grayfloat.cols;
	copyMakeBorder(grayfloat, tempA, 0, A_B, 0, A_R, BORDER_CONSTANT);

	// 改变滤波器尺寸
	Mat tempB;
	int B_T = 0;
	int B_B = width - kernel.rows;
	int B_L = 0;
	int B_R = height - kernel.cols;
	copyMakeBorder(kernel, tempB, 0, B_B, 0, B_R, BORDER_CONSTANT);

	// 分别进行离散傅里叶变换
	dft(tempA, tempA, 0, grayfloat.rows);
	dft(tempB, tempB, 0, kernel.rows);

	// 多个傅里叶变换结果相乘（频域相乘等于空域卷积）
	mulSpectrums(tempA, tempB, tempA, DFT_COMPLEX_OUTPUT);

	// 对相乘的结果进行逆变换
	// dft(tempA, tempA, DFT_INVERSE | DFT_SCALE, result.rows);
	idft(tempA, tempA, DFT_SCALE, result.rows);

	// 对逆变换结果进行归一化
	normalize(tempA, tempA, 0, 1, NORM_MINMAX);

	// 截取部分结果作为滤波结果
	tempA(Rect(0, 0, result.cols, result.rows)).copyTo(result);

	// 显示结果
	imshow("原图像", gray);
	imshow("滤波结果", result);
	waitKey(0);

}