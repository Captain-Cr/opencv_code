#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	模板匹配： 常采用在待匹配图片中选择与模板图片相同的尺寸的滑动窗口，通过比较滑动窗口与模板的相似程度，判断待匹配图像是否含有与模板图像相同的内容。

	模板匹配流程：
		1、在待匹配图像选取与模板尺寸大小相同的滑动窗口；
		2、比较滑动窗口中每个像素与模板中对应像素灰度值的关系，计算模板与滑动窗口的相似性；
		3、将滑动窗口从左上角开始向右滑动，滑动到最右边后向下滑动一行，然后从最左侧重新开始滑动，记录每一次移动后计算的模板与滑动窗口的相似性；
		4、比较所有位置的相似性，选择相似性最大的滑动窗口作为备选匹配结果。

*/



//float tm_SQDIFF(Mat x, Mat x_p)
Mat SQDIFF(Mat T, Mat I)
{
	// 为滑动窗口和待匹配图像计算相似度。
	// 平方差， R(x, y) = ∑(T（x', y') - I(x+x', y+y')^2)      其中T为模板图像, I为原始图像。   当模板与滑动窗口完全匹配时，计算数值为0，匹配度越低，计算数值越大。

	double R = 0.0;
	int re_height = I.cols - T.cols + 1;
	int re_width = I.rows - T.cols + 1;
	cout << re_width << endl;
	Mat result = Mat(re_height, re_width, CV_32F);				// 相似性矩阵，类型CV_32F，滑动窗口与模板相似性系数存放在滑动窗口左上角第一个像素
	cout << result.cols << "  " << result.rows << endl;

	for (int i = 0; i < T.rows; i++)
	{
		for (int j = 0; j < T.cols; j++)
		{
			cout << "gae" << endl;
		}
	}
	Mat a = Mat::zeros(3, 3, CV_8UC1);
	return a;

};
















int myMatchTemplate()
{
	// 自己写的模板匹配算法， 按照上面的步骤
	Mat src = imread("D:\\图片\\1.jpg");
	Mat temp = imread("D:\\图片\\1_templ.png");
	if (src.empty() || temp.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}

	SQDIFF(temp, src);

}










int mainfaa()
{
	Mat src = imread("D:\\图片\\1.jpg");
	Mat temp = imread("D:\\图片\\1_templ.png");
	if (src.empty() || temp.empty())
	{
		cout << "图片加载错误！" << endl;
		return -1;
	}
	imshow("src", src);
	imshow("temp", temp);
	
	Mat result;   // 相似性矩阵，类型CV_32F，滑动窗口与模板相似性系数存放在滑动窗口左上角第一个像素
	matchTemplate(src, temp, result, TM_CCOEFF_NORMED);  // 模板匹配			TM_CCOEFF_NORMED：完全匹配为1， 完全不匹配为0
	
	
	double maxVal, minVal;		
	Point maxLoc, minLoc;
	// 寻找匹配结果中的最大值和最小值以及坐标位置
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);	


	// 绘制最佳匹配的区域
	rectangle(src, Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 255, 0));
	imshow("匹配的区域", src);

	myMatchTemplate();
	waitKey();




	


	return 0;





}