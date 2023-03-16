#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	getRotationMatrix2D(center, angle, scale);		输入旋转角度和旋转中心，返回图像旋转矩阵，返回值为Mat类，是一个 2 X 3的矩阵。
	关系式：				 α    β   （1-α) * center.x - β * center.y						其中: α = scale * cos(angle)
				Rotation =  -β    α    β * center.x + (1 - α) * center.y					      β = scale * sin(angle)




	warpAffine(src, dst, M, dsize, flags,  borderMode, borderValue)。 第三个是变换矩阵，第四个参数是输出图像尺寸，五是插值标志，六是像素边界外推方法标志。
	
	仿射变换就是图像旋转、平移和缩放操作的统称，可以表示为线性变换和平移变换的叠加。                         X
							a00    a01    b00			图像像素值为：[X           则变换后像素值为：T = A * Y   + B 
	变换矩阵 M = [A  B]  =  a10    a11    b10						   Y]



	如果直到变换前后两个图像的3个像素点坐标对应关系，就可以求得仿射变换中的变换矩阵M.

	getAffineTransform(const Point2f src[],  const Point2f dst[])  返回值是一个2*3的变换矩阵。


*/

int main332(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	if (img.empty())
	{
		cout << "图像加载错误！！！" << endl;
	}


	Mat rotation0, rotation1, img_warp0, img_warp1;
	double angle = 30;			// 设置图像旋转角度
	Size dst_size(img.rows, img.cols);			// 设置输出图像的尺寸
	Point2f center(img.rows / 2.0, img.cols / 2.0);		// 设置图像旋转中心
	rotation0 = getRotationMatrix2D(center, angle, 1);		// 计算仿射变换矩阵
	warpAffine(img, img_warp0, rotation0, dst_size);		// 仿射变换
	imshow("img_warp0", img_warp0);

	// 根据定义的3个点进行仿射变换
	Point2f src_point[3];			// 坐标点数组
	Point2f dst_point[3];

	src_point[0] = Point(0, 0);			// 原始图像的3个点
	src_point[1] = Point(0, (float)(img.cols - 1));
	src_point[2] = Point((float)(img.rows - 1), (float)(img.cols - 1));

	// 仿射变换后图像的3个点
	dst_point[0] = Point2f((float)(img.rows)*0.11, (float)(img.cols)*0.20);
	dst_point[1] = Point2f((float)(img.rows)*0.15, (float)(img.cols)*0.70);
	dst_point[2] = Point2f((float)(img.rows)*0.81, (float)(img.cols)*0.85);

	rotation1 = getAffineTransform(src_point, dst_point);		// 根据对应点求取仿射变换矩阵
	warpAffine(img, img_warp1, rotation1, dst_size);			// 进行仿射变换
	imshow("img_warp1", img_warp1);
	waitKey();
	return 0;









}