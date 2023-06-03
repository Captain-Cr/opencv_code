#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description:一次性绘制所有的关键点

	Function:
		void cv::drawKeypoints(InputArray image, const vector<KeyPoint>& keypoints, InputOutputArray outImage, const Scalar& color=Scalar::all(-1), DrawMatchesFlags flags= DrawMatchesFlags::DEFAULT)
	该函数可以一次性在图像中绘制所有的像素点，以关键点为圆心绘制空心圆，以突出显示关键点在图像中的位置。第一个参数是需要绘制关键点的原图像，可以是单通道和三通道图像。第二个参数来自原图中的关键点
	向量，vector向量中存放这表示关键点KeyPoint类型的数据。第三个参数是绘制关键点后的输出图像，是否利用该参数数据绘制关键点结果取决于最后一个参数的取值。第四个参数是绘制关键点空心圆的颜色，如果选用
	默认值，那么表示用随机颜色绘制空心圆。最后一个参数表示绘制功能的选择标志，该参数可选择值以及含义如下表所示

										drawKeyPoint()函数绘制功能选择标志可选参数以及含义
			标志参数                     简记					含义
			DEFAULT						  0					创建输出图像矩阵，将绘制结果存放到输出图像中，并且绘制圆形表示关键点位置，不表示关键点大小和方向
			DRAW_OVER_OUTIMG			  1					不创建输出图像矩阵，直接在原图中绘制关键点
			NOT_DRAW_SINGLE_POINTS        2					不绘制单个关键点
			DRAW_RICH_KEYPOINTS           4					在关键点位置绘制圆形，圆形体现关键点的大小和方向

	KeyPoint类：
		class KeyPoint
		{
			float angle;		// 关键点的角度
			int class_id;		// 关键点的分类号
			int octave;			// 特征点来源（"金字塔")
			Point2f pt;			// 关键点坐标
			float response;		// 最强关键点的响应，可用于进一步分类和二次采样
			float size;			// 关键点邻域的直径


*/

int mainDrawKeypoint(int argc, char* argv[])
{
	Mat img = imread("D:\\图像处理案例图片\\images\\1.jpg");
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	// 随机生成关键点
	RNG rng(10086);
	vector<KeyPoint> keypoints;
	for (int i = 0; i < 20; i++)
	{
		float pty = rng.uniform(0, img.rows - 1);
		float ptx = rng.uniform(0, img.cols - 1);
		KeyPoint keypoint;
		keypoint.pt.x = ptx;
		keypoint.pt.y = pty;
		keypoints.push_back(keypoint);
	}

	// 绘制关键点
	drawKeypoints(img, keypoints, img, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), DrawMatchesFlags::DEFAULT);
	
	// 显示
	imshow("img", img);
	waitKey();
	destroyAllWindows();
	return 0;



}