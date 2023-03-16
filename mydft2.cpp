#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	图像傅里叶变换可以将图像从图像域变换到频率域，在经过图像傅里叶变换之后的结果会得到即含有实数又含有虚数的图像，在实际使用时常把结果分成实数图像和虚数图像，或者用复数的幅值和相位来表示变换结果，可以分成幅值图像和相位图像。

	函数描述： void cv::dft( InputArray src, OutputArray dst, int flag = 0, int nonzeroRows = 0);
		该函数能够对输入矩阵数据进行离散傅里叶变换，第一个参数是输入图像或者数组矩阵，该参数数据类型必须是CV_32F或者CV_64F，可以是单通道的实数矩阵也可以是双通道的复数矩阵。第二个参数是对输入的数组矩阵进行离散傅里叶变换的结果，
	结果以矩阵形式存放，矩阵的尺寸和类型取决于第三个参数。第三个参数是变换类型可选标志，可选标志和其执行情况如下所示。第四个参数表示输入、输出结果的形式，默认为0，当该参数不为0时，在第三个参数未设置DFT_INVERSE时，该函数
	假设只输入矩阵的第一个非零行，在第三个参数设置DFT_INVERSE时，只输出矩阵的第一个包含非零元素的非零行。

									dft()函数中变换类型可选标志
	可选标志				简记						含义
	DFT_INVERSE				 1				对一维数组或者二维数组进行逆变换
	DFT_SCALE				 2				缩放标志，输出结果会除以输入元素的数目N，通常与DFT_INVERSE结合使用
	DFT_ROWS				 4				对输入变量的每一行进行正变换或者逆变换，该标志可以处理三维或者更高维的离散变换时减少资源开销
	DFT_COMPLEX_OUTPUT		 16				对一维或者二维实数数组进行正变换，结果是相同尺寸的具有复数共轭对称的复数矩阵
	DFT_REAL_OUTPUT			 32				对一维或者二维复数矩阵进行逆变换，结果是相同尺寸的具有复数共轭对称的复数矩阵。如果输入的矩阵是具有复数共轭对称性的复数矩阵，那么计算结果为实数矩阵
	DFT_COMPLEX_INPUT		 64				指定输入数据是复数矩阵，如果设置了此标志，输入矩阵必须具有两个通道，并且如果输入矩阵具有两个通道，那么函数默认输入数据是复数矩阵

	- 如果该参数设置了DFT_ROWS或者输入矩阵具有单行或单列的形式，那么在设置DFT_ROWS时，该函数对矩阵的每一行执行正向或反向变换，否则，它执行二维变换。
	- 如果输入数组是实数且该参数未设置DFT_INVERSE,那么该函数执行正向一维或二维变换
	- 如果该参数设置DFT_COMPLEX_OUTPUT但是未设置DFT_INVERSE,那么输出结果为与输入大小相同的复数矩阵
	- 如果该参数未设置DFT_COMPLEX_OUTPUT和DFT_INVERSE，那么输出是与输入大小相同的实数矩阵。
	- 如果输入矩阵是复数矩阵并且该参数未设置DFT_INVERSE或者DFT_READL_OUTPUT,那么输出是与输入大小相同的复数矩阵
	- 当输入数组是实数并且设置了DFT_INVERSE，或者输入数据是复数矩阵并且设置DFT_REAL_OUTPUT时，那么输出是与输入相同大小的实数矩阵
	- 如果设置了DFT_SCALE，那么在转换后完成缩放，该标志是为了保证正变换之后再逆变换的结果和原始数据相同



	函数说明： void cv::idft(InputArray src, OutputArray dst, int flag = 0, int nonzeroRows = 0);
		该函数能够实现一维向量或者二维数组矩阵的离散傅里叶变换的逆变换，该函数的作用于dft()函数设置DFT_INVERSE的效果是一样的，即idft(src, dst, flags)相当于dft(src, dst, flag |DFT_INVERSE).


	傅里叶变换更倾向于某些特定长度的输入矩阵进行处理，所以介绍计算最优输入矩阵尺寸

	函数说明： int cv::getOptimalDFTSize(int vecsize)
		该函数能够返回已知矩阵数据的最优离散傅里叶变换尺寸，最优尺寸使2、3、5的公倍数。输入参数表示需要进行傅里叶变换的矩阵的最佳行数或列数。

	函数说明： void cv::copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar &value = Scalar())
		该函数能够在不对图像进行缩放的前提下扩大图像尺寸。该函数第一个参数为需要扩大尺寸的原图像。第二个参数是扩大后的图像，数据类型和原图像相同。第三个到第六个参数分别为原图像各个方向扩展像素的行数或列数，这4个参数决定
	最终图像的输出的尺寸。该函数输出图像的尺寸为Size(src.clos + left + right,  src.rows + buttom +top)。最后两个参数是扩展边界的类型和数值，扩展边界的类型常用BORDER_CONSTANT，在value参数默认时，表示用0填充新的像素。

	函数说明： void cv::magnitude(InputArray x, InputArray y, Output magnitude);
		该函数用来计算两个矩阵对应位置组成向量的幅值，也就是计算两个矩阵对应位置的平方根。第一个参数为其中一个矩阵，矩阵中的每个元素可以表示向量的x坐标，第二个参数是另一个矩阵，矩阵中每个元素可以表示向量的y坐标。
	第三个参数是输出的幅值矩阵，即平方根矩阵，该矩阵与第一个参数中的输入矩阵具有相同的尺寸和数据类型。需要注意，该函数的输入必须是CV_32F或者CV_64F。

*/


int main(int argc, char* argv[])
{
	// 输入一个矩阵，对其进行处理，展示正逆变换的关系
	Mat a = (Mat_<float>(5, 5) << 1, 2, 3, 4, 5,
		2, 3, 4, 5, 6,
		3, 4, 5, 6, 7,
		4, 5, 6, 7, 8,
		5, 6, 7, 8, 9);

	Mat b, c, d;
	dft(a, b, DFT_COMPLEX_OUTPUT);		// 正变换
	dft(b, c, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);		// 逆变换，只输出实数部分
	idft(b, d, DFT_SCALE);				// 逆变换，变回a

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << d << endl;

	// 图像傅里叶变换
	Mat src = imread("D:\\图片\\1.jpg");
	if (src.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 转化为灰度图
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("src", src);

	// 计算最适合傅里叶变换的尺寸
	int F_width = getOptimalDFTSize(gray.cols);
	int F_height = getOptimalDFTSize(gray.rows);

	// 对图像进行填充
	Mat fillImg;
	int top = (F_height - gray.rows) / 2;		// 顶部填充的行数
	int bottom = F_height - gray.rows - top;
	int left = (F_width - gray.cols) / 2;
	int right = F_width - gray.cols - left;
	copyMakeBorder(gray, fillImg, top, bottom, left, right, BORDER_CONSTANT);
	imshow("fill Img", fillImg);

	// 构建傅里叶变换输入量
	Mat flo[2], complex;
	flo[0] = Mat_<float>(fillImg);			// 实部部分
	flo[1] = Mat::zeros(fillImg.size(), CV_32F);		// 虚部部分
	merge(flo, 2, complex);				// 将实部和虚部组合成一个数

	// 进行傅里叶变换
	Mat result;
	dft(complex, result);

	// 将复数转化为幅值
	Mat resultC[2];
	split(result, resultC);		// 将傅里叶变换的虚部和实部分开
	Mat amplitude;
	magnitude(resultC[0], resultC[1], amplitude);		// 计算幅值图像，平方和

	// 使用对数缩小，公式为：M1=log(1+M),保证所有的数都大于0
	amplitude = amplitude + 1;
	log(amplitude, amplitude);		// 求自然对数

	// 与原图像尺寸对于的区域（去除填充的地方）
	amplitude = amplitude(Rect(top, left, gray.cols, gray.rows));
	normalize(amplitude, amplitude, 0, 1, NORM_MINMAX);		// 归一化
	imshow("傅里叶变换结果幅值图像", amplitude);	


	// 重新排列傅里叶图像中的象限，使的原点位于图像中心
	int centerX = amplitude.cols / 2;
	int centerY = amplitude.rows / 2;
	// 分解成4个小区域
	Mat Qlt(amplitude, Rect(0, 0, centerX, centerY));		// ROI区域左上
	Mat Qrt(amplitude, Rect(centerX, 0, centerX, centerY));	// 右上
	Mat Qlb(amplitude, Rect(0, centerY, centerX, centerY));	//左下
	Mat Qrb(amplitude, Rect(centerX, centerY, centerX, centerY));//右下

	// 交换象限，左上和右下进行交换
	Mat med;
	Qlt.copyTo(med);
	Qrb.copyTo(Qlt);
	med.copyTo(Qrb);
	// 交换象限，左下和右上进行交换
	Qrt.copyTo(med);
	Qlb.copyTo(Qrt);
	med.copyTo(Qlb);

	imshow("中心化幅值图", amplitude);







	waitKey();
	destroyAllWindows();
	return 0;


}