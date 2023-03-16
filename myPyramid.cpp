#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	图像金字塔
	（1）高斯金字塔：通过下采样不断地将图像的尺寸缩小；  （可以解决尺度不确定性）
	（2）拉普拉斯金字塔： 对于第i层的高斯金字塔图像，首先通过下采样得到第i+1层或者不在高斯金字塔中的图像， 之后对第i+1层图像进行上采样将图像尺寸还原回第i层的大小，最后求取高斯金字塔第i层与经过上采样后得到图像的差值图像，就是拉普拉斯金字塔
*/

int main243(int argc, char* argv[])
{
	Mat img = imread("D:\\图片\\44.jpg");
	if (img.empty())
	{
		cout << "图像加载错误！！！" << endl;
		return -1;
	}

	// 获取高斯金字塔
	vector<Mat> Gauss, Laps;			// 高斯金字塔和拉普拉斯金字塔
	int Level = 3;						// 金字塔的层数
	Gauss.push_back(img);			// 将原图作为金字塔的第0层
	for (int i = 0; i < Level; i++)
	{
		Mat gauss;
		pyrDown(Gauss[i], gauss);		// 下采样
		Gauss.push_back(gauss);
		imshow(to_string(i), gauss);
		waitKey();
	}


	// 构建拉普拉斯金字塔
	for (int j = Gauss.size()-1; j > 0; j--)
	{
		cout << "j=" << j << endl;
		Mat lap, upGaussian;
		if (j == Gauss.size() -1)		// 如果是最上面一层
		{
			Mat down;
			pyrDown(Gauss[j], down);			// 下采样
			pyrUp(down, upGaussian);		// 将下采样的图片进行上采样
			imshow("up", upGaussian);
			waitKey();
			cout << "Gauss[j]的高宽：" << Gauss[j].rows << " " << Gauss[j].cols << endl;
			cout << "upGaussian的高宽" << upGaussian.rows << "  " << upGaussian.cols << endl;
			lap = Gauss[j] - upGaussian;		// 图像差值
			Laps.push_back(lap);
		}

		pyrUp(Gauss[j], upGaussian);			// 上采样
		lap = Gauss[j - 1] - upGaussian;		// 图像差值
		Laps.push_back(lap);
	}

	// 查看两个图像的图像金字塔
	for (int i = 0; i < Laps.size(); i++)
	{
		string name = to_string(i);		// 将整数变成string
		imshow("G" + name, Gauss[i]);
		imshow("L" + name, Laps[i]);
	}

	waitKey();
	return 0;

}