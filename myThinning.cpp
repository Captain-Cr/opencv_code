#include <opencv2/opencv.hpp>
//#include <opencv2/ximgproc.hpp>		// 细化函数thinning()所在的头文件
#include <iostream>


using namespace std;
using namespace cv;

/*
	图像细化：图像细化是将图像的线条从多像素宽度减少到单位像素宽度的过程，（也称“骨架化”和“中轴变换”）
	

	cv::ximgproc::thinning(src, dst, int thinningType = THINNING_ZHANGSUEN);
	该函数能够对图像中的连通域进行细分，得到单位像素宽度的连通域。第一个参数是输入用于细化的图像，要求输入的图像必须是CV_8U的单通道图像；
	第二个参数是细化后的输出图像；第三个参数是细化算法的选择标志，目前只支持两种细化方法，一种是THINNING_ZHANGSUEN(0),另一种是THINNING_GUOHALL(1)

*/




int mainaefff(int argc, char* argv[])
{
	
	return 0;


}