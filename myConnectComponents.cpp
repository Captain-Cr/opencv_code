#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
	connectedComponents(InputArray img, OutputArray labels, connectivity, ltype, ccltype);
		-img: 待标记不同连通域的单通道图像，数据类型必须为CV_8U
		-labels： 标记不同连通域后的输出图像，与输入图像具有相同的尺寸
		-connectivity: 标记连通域时使用的邻域种类， 4表示4邻域， 8表示8邻域
		-ltype: 输出图像的数据类型，目前支持CV_32S和CV_16U两种
		-ccltype: 标记连通域时使用的算法类型标记。 CCL_WU:8邻域使用SAUF算法，4邻域使用SAUF； CCL_DEFAULT:8使用BBDT,4使用SAUF; CCL_GRANA: 8使用BBDT, 4使用SAUF
	
	该函数用于计算而知图像中连通域的个数，并在图像中将不同的连通域用不同的数字标签标记，其中0位背景，
	同时函数具有一个int类型的返回数据用于表示图像中连通域的数量

*/


int mainfae(int argc, char* argv[])
{
	RNG rng(10086);   // 随机数对象

	Mat img = imread("D:\\图片\\123.jpg");
	resize(img, img, Size(600, 800));
	if (img.empty())
	{
		cout << "图像加载失败" << endl;
		return -1;
	}

	//灰度图
	Mat gray, thresh;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 20, 255, THRESH_BINARY);
	Mat dilate_img;
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
	dilate(thresh, dilate_img, kernel, Point(-1, -1), 3);
	imshow("thresh", dilate_img);

	// 统计连通域
	Mat connect;
	int num_connect = connectedComponents(dilate_img, connect, 8, CV_16U);
	cout << "共有 " << num_connect - 1 << " 个轮廓" << endl;		// 除去背景


	vector<Vec3b> colors;
	for (int i = 0; i < num_connect; i++)
	{
		// 使用均匀分布的随机数确定颜色
		Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3);
	}

	Mat result = Mat::zeros(img.size(), img.type());
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			int color_index = connect.at<uint16_t>(i, j);			// 获取连通域图像像素
			if (color_index == 0)				// 背景颜色不改变
			{
				continue;
			}
			result.at<Vec3b>(i, j) = colors[color_index];
		}
	}


	imshow("result", result);
	waitKey();
	return 0;

}