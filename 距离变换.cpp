#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	距离变换：
	（1）欧氏距离：D[(i,j),(h,k)] = sqrt((i+h)^2 + (j+k)^2)							DIST_L2
	（2）D4距离（城市街区距离）= |i - h | + |j - k |                                DIST_L1
	（3）D8距离（棋盘距离） = max{|i - h |, |j - k |}                               DIST_C

	距离变换描述的是图像中像素点与某个区域块的距离，区域块中的像素点值为0，临近区域块的像素点有较小的值，离它越远值越大。

	mask1:                                           mask2:                                            f(x): 图像像素值；
	       q1    q2                                                q4                                  d(P,q): P与q的距离（欧氏、D4、D8)
		   q3    P                                             P   q3				                   d0=f(P); d1=f(q1)+d(P,q1);  d2=f(q2)+d(P,q2);  
		   q4                                                  q1  q2                                  d3=f(q3)+d(P,q3);    d4=f(q4)+d(P,d4)
		                                                                                               f(P)=min(d0, d1, d2, d3, d4)
*/


float EDistance(int x1, int y1, int x2, int y2);			// 欧氏距离
float MDistance(int x1, int y1, int x2, int y2);			// D4距离（城市距离）
float CDistance(int x1, int y1, int x2, int y2);			// D8距离（棋盘距离）
float Distsance(int x1, int y1, int x2, int y2, int type = 0);		// 用来选择上面三种距离公式
void DistanceTrans(const Mat input, Mat &output, int disTtype);		// 距离变换函数








int main33(int argc, char* argv[])
{
	Mat img = imread("E:\\data\\1.png");
	if (img.empty())
	{
		cout << "图像加载错误！！！" << endl;
		return -1;
	}
	cout << "图像的高、宽分别为：" << img.rows <<"\t"<< img.cols << endl;
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);

	// 变成灰度图
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	// 二值化
	Mat thresh;
	threshold(gray, thresh, 100, 255,THRESH_BINARY_INV);
	// 腐蚀
	Mat erodeImg;
	dilate(thresh, erodeImg,kernel,Point(-1,-1), 5);
	imshow("thresh", erodeImg);


	//Mat transMatD4, transMatD8, transMatE;
	//distanceTransform(erodeImg, transMatE, DIST_L2, 0);
	//distanceTransform(erodeImg, transMatD4, DIST_L1, 0, CV_8U);
	//distanceTransform(erodeImg, transMatD8, DIST_C, 0);

	//transMatE.convertTo(transMatE, CV_8U);
	//transMatD8.convertTo(transMatD8, CV_8U);

	//imshow("欧式距离变换后的图片", transMatE);
	//imshow("D4距离变换后的图片", transMatD4);
	//imshow("D8距离变换后的图片", transMatD8);
	//Mat BinaryImage = erodeImg;
	Mat output;
	//DistanceTrans(erodeImg, output, 1);
	//imshow("output", output*4);
	waitKey();
	


}

//float EDistance(int x1, int y1, int x2, int y2)
//{
//	// 欧氏距离
//	return sqrt(float((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
//
//}
//
//float MDistance(int x1, int y1, int x2, int y2)
//{
//	// D4距离
//	return abs(x1 - x2) + abs(y1 - y2);
//}
//
//float CDistance(int x1, int y1, int x2, int y2)
//{
//	// D8距离
//	return max(abs(x1 - x2), abs(y1 - y2));
//
//}
//
//float Distance(int x1, int y1, int x2, int y2, int type)
//{
//	if (type == 0)
//	{
//		return EDistance(x1, y1, x2, y2);
//	}
//	else if (type == 1)
//	{
//		return MDistance(x1, y1, x2, y2);
//	}
//	else if (type == 2)
//	{
//		return CDistance(x1, y1, x2, y2);
//	}
//}


//void DistanceTrans(const Mat input, Mat &output, int disType)
//{
//	/*
//		距离变换函数， 
//		Args：
//			const Mat input: 输入的二值图像
//			Mat &output:
//			int disType：用来选择是用哪种距离公式
//	*/
//	Mat BinaryImage = input;
//	cout << BinaryImage.rows << "  " << BinaryImage.cols << endl;
//	uchar *pRowOne;					// 图像当前每一行的指针
//	uchar *pRowNext;				// 中心像素P所在行的上一行的指针
//	float distance;					// 距离中心像素点P的距离
//	float Mindis;					// 最小距离
//	
//	// 从左上角到右下角
//	for (int i = 1; i <= BinaryImage.rows - 1; i++)
//	{
		// 获取中心像素所在每一行的指针， 这里从第1行开始，空出一行
		//pRowOne = BinaryImage.ptr<uchar>(i);
		//for (int j = 1; j <= BinaryImage.cols; j++)
		//{
		//	// 获取中心像素上一行的指针
		//	pRowNext = BinaryImage.ptr<uchar>(i - 1);

		//	// 从左到右， 从上到下  计算到中心点的距离,   disType:选择计算距离的公式
		//	distance = Distance(i, j, i - 1, j - 1, disType);			// q1
		//	Mindis = min((float)pRowOne[j], distance + pRowNext[j - 1]);	

		//	distance = Distance(i, j, i - 1, j, disType);				// q2
		//	Mindis = min(Mindis, distance + pRowNext[j]);

		//	// 获取中心像素下一行的指针
		//	pRowNext = BinaryImage.ptr<uchar>(i);
		//	distance = Distance(i, j, i, j - 1, disType);//q3
		//	Mindis = min(Mindis, distance + pRowNext[j]);
		//
		//	pRowNext = BinaryImage.ptr<uchar>(i + 1);//q4
		//	distance = Distance(i, j, i + 1, j - 1, disType);
		//	Mindis = min(Mindis, distance + pRowNext[j - 1]);
		//	pRowOne[j] = (uchar)round(Mindis);
		//	

		//}
	//}
		
//
//		for (int i = BinaryImage.rows - 2; i > 0; i--)
//		{
//			pRowOne = BinaryImage.ptr<uchar>(i);
//			for (int j = BinaryImage.cols - 1; j > 0; j--)
//			{
//				pRowNext = BinaryImage.ptr<uchar>(i + 1);
//
//				distance = Distance(i, j, i + 1, j, disType);//q1
//				Mindis = min((float)pRowOne[j], distance + pRowNext[j]);
//
//				distance = Distance(i, j, i + 1, j + 1, disType);//q2
//				Mindis = min(Mindis, distance + pRowNext[j + 1]);
//
//				pRowNext = BinaryImage.ptr<uchar>(i);//q3
//				distance = Distance(i, j, i, j + 1, disType);
//				Mindis = min(Mindis, distance + pRowNext[j + 1]);
//
//				pRowNext = BinaryImage.ptr<uchar>(i - 1);//q4
//				distance = Distance(i, j, i - 1, j + 1, disType);
//				Mindis = min(Mindis, distance + pRowNext[j + 1]);
//				pRowOne[j] = (uchar)round(Mindis);
//
//			}
//
//		}
//	output = BinaryImage;
//
//}
float EDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(float((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}
float MDistance(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
float CDistance(int x1, int y1, int x2, int y2)
{
	return max(abs(x1 - x2), abs(y1 - y2));
}
float Distance(int x1, int y1, int x2, int y2, int type)
{
	if (type == 0)
	{
		return EDistance(x1, y1, x2, y2);
	}
	else if (type == 1)
	{
		return MDistance(x1, y1, x2, y2);
	}
	else if (type == 2)
	{
		return CDistance(x1, y1, x2, y2);
	}
}


void DistanceTrans( Mat input, Mat &output, int disType)
{
	Mat BinaryImage = input;
	uchar *pRowOne;
	uchar *pRowNext;
	float distance;
	float Mindis;
	for (int i = 1; i <= BinaryImage.rows - 1; i++)
	{
		pRowOne = BinaryImage.ptr<uchar>(i);
		for (int j = 1; j <= BinaryImage.cols; j++)
		{
			pRowNext = BinaryImage.ptr<uchar>(i - 1);

			distance = Distance(i, j, i - 1, j - 1, disType);//q1
			Mindis = min((float)pRowOne[j], distance + pRowNext[j - 1]);

			distance = Distance(i, j, i - 1, j, disType);//q2
			Mindis = min(Mindis, distance + pRowNext[j]);

			pRowNext = BinaryImage.ptr<uchar>(i);
			distance = Distance(i, j, i, j - 1, disType);//q3
			Mindis = min(Mindis, distance + pRowNext[j]);

			pRowNext = BinaryImage.ptr<uchar>(i + 1);//q4
			distance = Distance(i, j, i + 1, j - 1, disType);
			Mindis = min(Mindis, distance + pRowNext[j - 1]);
			pRowOne[j] = (uchar)round(Mindis);
		}
	}
	for (int i = BinaryImage.rows - 2; i > 0; i--)
	{
		pRowOne = BinaryImage.ptr<uchar>(i);
		for (int j = BinaryImage.cols - 1; j > 0; j--)
		{
			pRowNext = BinaryImage.ptr<uchar>(i + 1);

			distance = Distance(i, j, i + 1, j, disType);//q1
			Mindis = min((float)pRowOne[j], distance + pRowNext[j]);

			distance = Distance(i, j, i + 1, j + 1, disType);//q2
			Mindis = min(Mindis, distance + pRowNext[j + 1]);

			pRowNext = BinaryImage.ptr<uchar>(i);//q3
			distance = Distance(i, j, i, j + 1, disType);
			Mindis = min(Mindis, distance + pRowNext[j + 1]);

			pRowNext = BinaryImage.ptr<uchar>(i - 1);//q4
			distance = Distance(i, j, i - 1, j + 1, disType);
			Mindis = min(Mindis, distance + pRowNext[j + 1]);
			pRowOne[j] = (uchar)round(Mindis);

		}

	}
	output = BinaryImage;


}

