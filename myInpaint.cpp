#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:图像修复技术就是利用图像中损坏区域边缘的像素，即根据像素值间的结构关系，估计出损坏区域可能的像素排列，从而去除图像中受污染的区域。可以去除图像中划痕、水印和日期

	Function:
		void cv::inpaint(InputArray src, InputArray inpainMask, OutputArray dst, double inpainRadius, int flags);
	该函数利用图像修复算法对图像中指定的区域进行修复，函数无法判断哪些区域需要修复，因此在使用过程中需要明确指出需要修复的区域。该函数的第一个参数为需要修复的图像，该函数可以对灰度图像和彩色图像
	进行修复，修复灰度图像时，数据类型可以是CV_8U,CV_16U或CV_32U的单通道图像；在修复彩色图像时，图像的数据类型只能为CV_8U。第二个参数为修复掩码，即指定图像中需要修复的区域，该参数的输入量是一个与
	待修复图像相同尺寸和类型的CV_8U单通道图像，图像中非零像素表示需要修复的区域。第三个参数是修复后输出图像；第四个参数表示修复算法考虑的每个像素点的圆形领域半径。最后一个参数表示修复图像的方法
	标志，可以选择的标志及其含义如下所示：
													inpaint()函数修复图像方法可选标志
	             标志参数                   简记                               含义
			    INPAINT_NS                   0                               基于Navier-Stokes算法修复图像
				INPAINT_TELEA                1                               基于Alexandru-Telea算法修复图像
									
*/




int maininpaint(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\lenaInpaint.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return 0;
	}
	imshow("img", img);

	// 通过阈值处理获取要修复图像的区域
	Mat gray, thresh;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 20, 255, THRESH_BINARY_INV);		// 阈值图像就是mask
	imshow("thresh", thresh);
	// 形态学操作
	Mat mask; 
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
	dilate(thresh, mask, kernel, Point(-1,-1),2);
	imshow("dilate", mask);
	/*Mat mask;
	Mat kernel = (Mat_<uchar>(3, 1) << 1,1,1);
	morphologyEx(thresh, mask, MORPH_OPEN, kernel);
	imshow("morphology", mask);*/

	// 进行图像修复
	Mat imgInpaint;
	inpaint(img, mask, imgInpaint, 5, INPAINT_NS);
	imshow("imgInpaint", imgInpaint);

	

	waitKey();
	destroyAllWindows();
	return 0;
}