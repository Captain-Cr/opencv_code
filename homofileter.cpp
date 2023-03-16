#include <iostream>
#include<time.h>
#include <math.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	这个程序是用高斯滤波传递函数（还有巴特沃斯、指数型滤波器，在机器视觉书上111页）来进行同态滤波。
	思想：这个滤波器需要对低频能量进行压制，以降低动态范围，同时要对高频进行提高，以增强图像对比度
	这个程序仅使用Y分量,而不对UV分量进行同态滤波，组合起来就是彩色图像
*/


Mat HomoFilter(Mat srcImg);				// 同态滤波函数
Mat HomoFilter2(Mat inputImg);
Mat HomoFilter3(Mat inputImg);

int mainfaef(int argc, char* argv[])
{
	// 读取图像并转换为YUV格式和将YUV各个分量拆分开
	Mat img = imread("F:\\camera\\resize\\trainResize\\13.bmp");
	// Mat img = imread("F:\\1.jpeg");
	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);			// 最后输出的彩色图像
	if (!img.data)
	{
		cout << "图片加载错误！！！" << endl;
		return -1;
	}
	Mat img1;
	img.copyTo(img1);
	cvtColor(img, img, COLOR_BGR2YUV);
	vector<Mat> yuv;
	split(img, yuv);
	Mat owY = yuv[0];			// 获取y分量

	// 对Y分量进行同态滤波
	Mat newY = HomoFilter(owY);
	imshow("srcY", owY);
	imshow("newY", newY);

	// 合并恢复彩色图像
	Mat tempY(img.rows, img.cols, CV_8UC1);		// 因为上面的Y有可能尺寸增大了1,所以要一个临时Mat重新绘制,保证y的大小和原来的一样
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			tempY.at<uchar>(i, j) = newY.at<uchar>(i, j);
		}
	}
	yuv[0] = tempY;
	merge(yuv, dst);
	cvtColor(dst, dst, COLOR_YUV2BGR);			//	变成bgr图像
	imshow("src_bgr", img1);
	imshow("dst", dst);
	waitKey();




}



Mat HomoFilter(Mat inputImg)
{
	// 同态滤波实现方法
	Mat homoImg = inputImg.clone();			// 滤波输出的图像，进行深拷贝
	Mat orginalImg = inputImg.clone();		// 滤波前的图像

	// 转换数据类型
	homoImg.convertTo(homoImg, CV_64FC1);

	// 复制图像并制作边界
	int rows = homoImg.rows;		// 高
	int cols = homoImg.cols;		// 宽
	int m = rows % 2 == 1 ? rows + 1 : rows;	// 判断图像的行数是奇数还是偶数，如果是奇数则+1
	int n = cols % 2 == 1 ? cols + 1 : cols;
	copyMakeBorder(homoImg, homoImg, 0, m - rows, 0, n - cols, BORDER_CONSTANT, Scalar::all(0));	// 制作边界
	rows = homoImg.rows;			// 填充后图片的行数
	cols = homoImg.cols;			// 填充后图片的列数
	Mat homo_result_Img(rows, cols, CV_64FC1);			//创建最终输出图像


	// 1、对原图像f(x,y) = i(x, y) * r(x,y)取对数.(每个像素）
	for (int i = 0; i < rows; i++) {
		double* srcImgPtr = homoImg.ptr<double>(i);			// 原始图像行的指针
		double* logImgPtr = homoImg.ptr<double>(i);			// 对数图像行的指针
		for (int j = 0; j < cols; j++) {
			logImgPtr[j] = log(srcImgPtr[j] + 0.0001);	
		}
	}


	// 2、离散傅里叶变换（or 离散余弦变换）， 频率域
	Mat mat_dft = Mat::zeros(Size(rows, cols), CV_64FC1);
	// dft(homoImg, mat_dft);
	dct(homoImg, mat_dft);

	// 3、设计滤波器传递函数H(u,v), 这个滤波器需要对低频能量进行压制，以降低动态范围，同时要对高频进行提高，以增强图像对比度
	// 这里是高斯同态滤波器
	Mat H_u_v = Mat::zeros(rows, cols, CV_64FC1);		// 滤波频谱
	double gammaH = 3;			// 高频增益
	double gammaL = 0.1;		// 低频增益
	double C = 0.6;				// 斜面锐化常数， 斜率
	//double D0 = pow((homoImg.rows / 2), 2.0) + pow((homoImg.cols / 2), 2.0);		// 截止频率，值越大越亮
	double D0 = (homoImg.rows / 2) * (homoImg.rows / 2) + (homoImg.cols / 2) * (homoImg.cols / 2);//截止频率;
	//double D0 = 200;						//5 - 200  截止频率 越大越亮
	double D = 0;
	for (int i = 0; i < rows; i++) {
		double* data_H_u_v = H_u_v.ptr<double>(i);			// 滤波频谱的行指针
		for (int j = 0; j < cols; j++) {
			D = pow((i - homoImg.rows / 2), 2.0) + pow((j - homoImg.cols / 2), 2.0);
			data_H_u_v[j] = (gammaH - gammaL) * (1 - exp(-C * (D / D0))) + gammaL;		// 看公式
		}
	}
	H_u_v.ptr<double>(0)[0] = 1.1;			// 将第一个像素赋值

	// 4、滤波频谱和频域图像对应位置相乘(mul)得到频域滤波图片
	mat_dft = mat_dft.mul(H_u_v);			

	// 5、反傅里叶变换（or 反离散余弦变换）， 图像域
	// idft(mat_dft, homo_result_Img);
	idct(mat_dft, homo_result_Img);

	// 6、反对数, 得到原始图像
	for (int i = 0; i < rows; i++) {
		double* srcdata = homo_result_Img.ptr<double>(i);		// 反变换后图像的行指针
		double* dstdata = homo_result_Img.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			dstdata[j] = exp(srcdata[j]);					// 对每个像素反对数
		}
	}
	homo_result_Img.convertTo(homo_result_Img, CV_8UC1);		// 转变图像格式
	return homo_result_Img;

}



Mat HomoFilter2(Mat inputImg)
{
	// 同态滤波实现方法,巴特沃斯同态滤波器
	Mat homoImg = inputImg.clone();			// 滤波输出的图像，进行深拷贝
	Mat orginalImg = inputImg.clone();		// 滤波前的图像

	// 转换数据类型
	homoImg.convertTo(homoImg, CV_64FC1);

	// 复制图像并制作边界
	int rows = homoImg.rows;		// 高
	int cols = homoImg.cols;		// 宽
	int m = rows % 2 == 1 ? rows + 1 : rows;	// 判断图像的行数是奇数还是偶数，如果是奇数则+1
	int n = cols % 2 == 1 ? cols + 1 : cols;
	copyMakeBorder(homoImg, homoImg, 0, m - rows, 0, n - cols, BORDER_CONSTANT, Scalar::all(0));	// 制作边界
	rows = homoImg.rows;			// 填充后图片的行数
	cols = homoImg.cols;			// 填充后图片的列数
	Mat homo_result_Img(rows, cols, CV_64FC1);			//创建最终输出图像


	// 1、对原图像f(x,y) = i(x, y) * r(x,y)取对数.(每个像素）
	for (int i = 0; i < rows; i++) {
		double* srcImgPtr = homoImg.ptr<double>(i);			// 原始图像行的指针
		double* logImgPtr = homoImg.ptr<double>(i);			// 对数图像行的指针
		for (int j = 0; j < cols; j++) {
			logImgPtr[j] = log(srcImgPtr[j] + 0.0001);
		}
	}


	// 2、离散傅里叶变换（or 离散余弦变换）， 频率域
	Mat mat_dft = Mat::zeros(Size(rows, cols), CV_64FC1);
	// dft(homoImg, mat_dft);
	dct(homoImg, mat_dft);

	// 3、设计滤波器传递函数H(u,v), 这个滤波器需要对低频能量进行压制，以降低动态范围，同时要对高频进行提高，以增强图像对比度
	// 这里是巴特沃斯同态滤波器
	Mat H_u_v = Mat::zeros(rows, cols, CV_64FC1);		// 滤波频谱
	double gammaH = 3;			// 高频增益
	double gammaL = 0.1;		// 低频增益
	double C = 0.5;				// 斜面锐化常数， 斜率
	//double D0 = pow((homoImg.rows / 2), 2.0) + pow((homoImg.cols / 2), 2.0);		// 截止频率，值越大越亮
	double D0 = (homoImg.rows / 2) * (homoImg.rows / 2) + (homoImg.cols / 2) * (homoImg.cols / 2);//截止频率;
	//double D0 = 200;						//5 - 200  截止频率 越大越亮
	double D = 0;
	for (int i = 0; i < rows; i++) {
		double* data_H_u_v = H_u_v.ptr<double>(i);			// 滤波频谱的行指针
		for (int j = 0; j < cols; j++) {
			D = pow((i - homoImg.rows / 2), 2.0) + pow((j - homoImg.cols / 2), 2.0);
			data_H_u_v[j] = (gammaH - gammaL) * (1 /(1 + D0 / (C * D))) + gammaL;		// 看公式
		}
	}
	H_u_v.ptr<double>(0)[0] = 1.1;			// 将第一个像素赋值

	// 4、滤波频谱和频域图像对应位置相乘(mul)得到频域滤波图片
	mat_dft = mat_dft.mul(H_u_v);

	// 5、反傅里叶变换（or 反离散余弦变换）， 图像域
	// idft(mat_dft, homo_result_Img);
	idct(mat_dft, homo_result_Img);

	// 6、反对数, 得到原始图像
	for (int i = 0; i < rows; i++) {
		double* srcdata = homo_result_Img.ptr<double>(i);		// 反变换后图像的行指针
		double* dstdata = homo_result_Img.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			dstdata[j] = exp(srcdata[j]);					// 对每个像素反对数
		}
	}
	homo_result_Img.convertTo(homo_result_Img, CV_8UC1);		// 转变图像格式
	return homo_result_Img;

}



Mat HomoFilter3(Mat inputImg)
{
	// 同态滤波实现方法,巴特沃斯同态滤波器
	Mat homoImg = inputImg.clone();			// 滤波输出的图像，进行深拷贝
	Mat orginalImg = inputImg.clone();		// 滤波前的图像

	// 转换数据类型
	homoImg.convertTo(homoImg, CV_64FC1);

	// 复制图像并制作边界
	int rows = homoImg.rows;		// 高
	int cols = homoImg.cols;		// 宽
	int m = rows % 2 == 1 ? rows + 1 : rows;	// 判断图像的行数是奇数还是偶数，如果是奇数则+1
	int n = cols % 2 == 1 ? cols + 1 : cols;
	copyMakeBorder(homoImg, homoImg, 0, m - rows, 0, n - cols, BORDER_CONSTANT, Scalar::all(0));	// 制作边界
	rows = homoImg.rows;			// 填充后图片的行数
	cols = homoImg.cols;			// 填充后图片的列数
	Mat homo_result_Img(rows, cols, CV_64FC1);			//创建最终输出图像


	// 1、对原图像f(x,y) = i(x, y) * r(x,y)取对数.(每个像素）
	for (int i = 0; i < rows; i++) {
		double* srcImgPtr = homoImg.ptr<double>(i);			// 原始图像行的指针
		double* logImgPtr = homoImg.ptr<double>(i);			// 对数图像行的指针
		for (int j = 0; j < cols; j++) {
			logImgPtr[j] = log(srcImgPtr[j] + 0.0001);
		}
	}


	// 2、离散傅里叶变换（or 离散余弦变换）， 频率域
	Mat mat_dft = Mat::zeros(Size(rows, cols), CV_64FC1);
	// dft(homoImg, mat_dft);
	dct(homoImg, mat_dft);

	// 3、设计滤波器传递函数H(u,v), 这个滤波器需要对低频能量进行压制，以降低动态范围，同时要对高频进行提高，以增强图像对比度
	// 这里是巴特沃斯同态滤波器
	Mat H_u_v = Mat::zeros(rows, cols, CV_64FC1);		// 滤波频谱
	double gammaH = 1.7;			// 高频增益
	double gammaL = 0.5;		// 低频增益
	double C = 1.2;				// 斜面锐化常数， 斜率
	//double D0 = pow((homoImg.rows / 2), 2.0) + pow((homoImg.cols / 2), 2.0);		// 截止频率，值越大越亮
	//double D0 = (homoImg.rows / 2) * (homoImg.rows / 2) + (homoImg.cols / 2) * (homoImg.cols / 2);//截止频率;
	double D0 = 5;						//5 - 200  截止频率 越大越亮
	double D = 0;
	double alpha = 0.001;
	for (int i = 0; i < rows; i++) {
		double* data_H_u_v = H_u_v.ptr<double>(i);			// 滤波频谱的行指针
		for (int j = 0; j < cols; j++) {
			D = pow((i - homoImg.rows / 2), 2.0) + pow((j - homoImg.cols / 2), 2.0);
			//data_H_u_v[j] = (gammaH - gammaL) * (1 / (1 + D0 / (C * D))) + gammaL;		// 看公式
			data_H_u_v[j] = (gammaH - gammaL) * exp(exp(1 - alpha * D)) + gammaL;
		}
	}
	//H_u_v.ptr<double>(0)[0] = 1.1;			// 将第一个像素赋值

	// 4、滤波频谱和频域图像对应位置相乘(mul)得到频域滤波图片
	mat_dft = mat_dft.mul(H_u_v);

	// 5、反傅里叶变换（or 反离散余弦变换）， 图像域
	// idft(mat_dft, homo_result_Img);
	idct(mat_dft, homo_result_Img);

	// 6、反对数, 得到原始图像
	for (int i = 0; i < rows; i++) {
		double* srcdata = homo_result_Img.ptr<double>(i);		// 反变换后图像的行指针
		double* dstdata = homo_result_Img.ptr<double>(i);
		for (int j = 0; j < cols; j++) {
			dstdata[j] = exp(srcdata[j]);					// 对每个像素反对数
		}
	}
	homo_result_Img.convertTo(homo_result_Img, CV_8UC1);		// 转变图像格式
	return homo_result_Img;

}