#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main12452(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	cout << "img: " << img.cols << " " << img.rows << endl;
	imshow("img", img);

	int row = (int)(img.rows / 2);
	int col = (int)(img.cols / 2);
	//裁剪图片
	Mat img0 = img(Rect(0, 0, col, row));
	Mat img1 = img(Rect(col, 0, col, row));
	Mat img2 = img(Rect(0, row, col, row));
	Mat img3 = img(Rect(col, row, col, row));
	imshow("img0", img0);
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	cout << "img0:" << img0.cols << "  " << img0.rows << endl;
	cout << "img1:" << img1.cols << "  " << img1.rows << endl;
	waitKey();




	// 矩阵数组的横竖拼接
	Mat matArray[] = { img0, img1, img2, img3 };
	Mat vout, hout;
	hconcat(matArray, 2, hout);	
	cout << "水平拼接" << endl;
	imshow("水平拼接", hout);
	vconcat(matArray, 2, vout);
	cout << "垂直拼接" << endl;
	imshow("垂直拼接", vout);
	waitKey();



	// 图像拼接
	Mat hImg, vImg, hImg2;
	// 图像水平连接
	hconcat(img0, img1, hImg);		// 先将两个子图水平拼接
	hconcat(img2, img3, hImg2);
	vconcat(hImg, hImg2, vImg);     // 然后进行垂直拼接，还原原图
	imshow("还原原图", vImg);
	waitKey();

	return 0;
}