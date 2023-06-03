#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description: 离散余弦变换和离散傅里叶变换类似，但是变换过程中只使用实数。主要用于对信号和图像的有损压缩，具有“能量集中”的特性，信号经过变换后能量主要集中在结果的低频部分。

	Functional: void cv::dct(InputArray src, OutputArray dst, int flags = 0);
	Parameters: 
			InputArray src:待进行离散余弦变换的数据矩阵，数据必须是浮点数
			OutputArray dst: 离散余弦变换结果矩阵，与输入矩阵具有相同的尺寸和数据类型，数据也必须是浮点型
			int flags: 转换方法的标志，可以选择的标志及其含义如下所示

											dct（）函数中转换方法的可选标志
	   标志                          简记                                      含义
	   --                             0                                   对一维或者二维数组进行正变换
     DCT_INVERSE                      1                                   对一维或者二维数组进行逆变换
	 DCT_ROWS                         4                                   执行输入矩阵的每一行正变换？或逆变换？此标志使程序可以同时转换多个向量，可用于减少开销以执行三维或者更高维度的转换

	 PS：该函数对一维或者二维的数据进行正向或者逆向的离散余弦变换，另外该函数的第三个参数为转换方法的标志，使用规则如下：
		-- 如果(flags & DCT_INVERSE) == 0, 那么该函数对一维或者二维数据进行正向离散余弦变换；否则，进行正变换；
		-- 如果(flags & DCT_ROWS) != 0, 那么该函数执行每行的一维变换；
		-- 如果以上都不成立，那么该函数执行二维变换。

	Additionary:目前dct()函数只支持偶数大小的数组，因此在使用该函数处理数据时，需要将数据填充到指定的尺寸，最佳尺寸可以通过2 * getOptimalDFT((N+1)/2)计算得到。
	

	Functional:  void cv::idct(InputArray src, OutputArray dst, int flags = 0);
	Parameters:
			InputArray src:待进行离散余弦变换的逆变换的数据矩阵，数据是单通道的浮点数
			OutputArray dst:离散余弦变换的逆变换的结果矩阵，与输入量具有相同的尺寸和数据类型；
			flags：转换方法的标志
	该函数能够实现一维或者二维数组矩阵的离散余弦变换的逆变换，该函数的作用于dct（）函数设置DFT_INVERSE时效果一致，即idct(src, dst, flags)=dct(src, dst, flags|DFT_INVERSE)
	Additional:dct（）函数只能变换单通道的矩阵，因此需要分别对3个通道进行离散余弦变换，并将变换结果重新组成一副具有三通道的彩色图像。
*/

int main1345(int argc, char* argv[])
{
	Mat kernel = (Mat_<float>(5, 5) << 1, 2, 3, 4, 5,
		2, 3, 4, 5, 6,
		3, 4, 5, 6, 7,
		4, 5, 6, 7, 8,
		5, 6, 7, 8, 9);
	Mat a, b;
	dct(kernel, a);				// 离散余弦变换
	idct(a, b);					// 离散反余弦变换


	// 对图像进行处理
	Mat img = imread("D:\\图像处理案例图片\\images\\1.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 计算最优尺寸
	int width = 2 * getOptimalDFTSize((img.cols + 1) / 2);
	int height = 2 * getOptimalDFTSize((img.rows + 1) / 2);

	// 填充到最优尺寸
	int top = 0; 
	int buttom = height - img.rows;
	int left = 0;
	int right = width - img.cols;
	Mat appropriate;				// 保存填充后的图像
	copyMakeBorder(img, appropriate, top, buttom, left, right, BORDER_CONSTANT, Scalar(0));

	// 对3个通道需要分别进行离散余弦变换
	vector<Mat> channels;
	split(img, channels);

	// 提取BGR颜色的各个通道
	Mat one = channels[0];
	Mat two = channels[1];
	Mat three = channels[2];

	// 进行离散余弦变换
	Mat oneDCT, twoDCT, threeDCT;
	dct(Mat_<float>(one), oneDCT);
	dct(Mat_<float>(two), twoDCT);
	dct(Mat_<float>(three), threeDCT);

	// 重新组合成一副图像
	vector<Mat> channelsDCT;
	channelsDCT.push_back(Mat_<uchar>(oneDCT));
	channelsDCT.push_back(Mat_<uchar>(twoDCT));
	channelsDCT.push_back(Mat_<uchar>(threeDCT));

	// 输出图像
	Mat result;
	merge(channelsDCT, result);
	imshow("DCT图像", result);
	
	waitKey();
	destroyAllWindows();
	return 0;

}