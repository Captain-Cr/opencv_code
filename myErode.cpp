#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	getStructuringElement(int shape, Size ksize, Point anchor=Point(-1,-1));
	该函数用于生成图像形态学操作中常用的矩形、十字结构和椭圆结构元素。第一个参数为生成结构元素的种类，有MORPH_RECT、MORPH_CROSS、MORPH_ELLIPSE。
	第二个参数为结构元素的尺寸。

	erode(src, dst, kernel, Point(-1,-1), iterations=1, borderType=BOREDER_CONSTANT, borderValue);
	该函数根据结构元素对输入图像进行腐蚀、在腐蚀多通道图像时，每个通道独立进行腐蚀运算。需要注意的是，该函数的腐蚀过程只针对图像的非零像素。

	dilate(src, dst, kernel, Point(-1, -1), iterations=1, borderType=BOREDER_CONSTANT, borderValue);
	该函数根据结构元素对输入图像进行膨胀、在膨胀多通道图像时，每个通道独立进行膨胀运算。需要注意的是，该函数的膨胀过程只针对图像的非零像素。

*/

// 绘制包含区域函数
void drawStats(Mat &img, int number, Mat centeriods, Mat stats, String str)
{
	RNG rng(100);
	vector<Vec3b> colors;
	for (int i = 0; i < number; i++)
	{
		// 使用均匀分布的随机数颜色
		Vec3b vec = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec);
	}

	for (int j = 1; j < number; j++)
	{
		// 中心位置
		int center_x = centeriods.at<double>(j, 0);
		int center_y = centeriods.at<double>(j, 1);

		// 矩形边框
		int x = stats.at<int>(j, CC_STAT_LEFT);
		int y = stats.at<int>(j, CC_STAT_TOP);
		int w = stats.at<int>(j, CC_STAT_WIDTH);
		int h = stats.at<int>(j, CC_STAT_HEIGHT);

		// 中心点绘制
		circle(img, Point(center_x, center_y), 2, Scalar(0, 0, 255), 2, 8, 0);
		// 矩形绘制
		rectangle(img, Rect(x, y, w, h), colors[j], 1, 8, 0);
		putText(img, format("%d", j), Point(center_x, center_y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
	}
	imshow(str, img);
}


int mainadc(int argc, char* argv[])
{
	// 生成用于腐蚀的原图
	uchar src_arr[] = { 0, 0, 0, 0, 255, 0,
					   0, 255, 255, 255, 255, 255,
					   0, 255, 255, 255, 255, 0,
					   0, 255, 255, 255, 255, 0,
					   0, 255, 255, 255, 255, 0,
					   0, 0, 0, 0, 0, 0 };
	Mat src = Mat(6, 6, CV_8U, src_arr);
	Mat struct1, struct2;
	struct1 = getStructuringElement(MORPH_RECT, Size(3, 3));		// 矩形结构元素
	struct2 = getStructuringElement(MORPH_CROSS, Size(3, 3));       // 十字结构元素

	Mat erodeSrc1, erodeSrc2;	// 存放腐蚀后的图像
	erode(src, erodeSrc1, struct1);
	erode(src, erodeSrc2, struct2);
	cout << erodeSrc1 << endl;
	cout << erodeSrc2 << endl;


	Mat img = imread("D:\\图片\\123.png");
	if (img.empty())
	{
		cout << "图像加载错误" << endl;
		return -1;
	}
	Mat img2;
	img.copyTo(img2);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat thresh;
	threshold(gray, thresh, 150, 255, THRESH_BINARY);
	imshow("thresh", thresh);
	Mat erode_img;
	erode(thresh, erode_img, struct1,Point(-1,-1), 3);
	imshow("erode_img", erode_img);

	// 验证腐蚀对小连通域的去除
	Mat src_label, src_stats, src_centeriods;
	int src_num = connectedComponentsWithStats(thresh, src_label, src_stats, src_centeriods);		// 原图中连通域信息
	drawStats(img, src_num, src_centeriods, src_stats, "未腐蚀时统计的连通域");                    // 绘制图像

	Mat dst_label, dst_stats, dst_centeriods;
	int dst_num = connectedComponentsWithStats(erode_img, dst_label, dst_stats, dst_centeriods);
	drawStats(img2, dst_num, dst_centeriods, dst_stats, "腐蚀后统计的连通域");




	waitKey();


}