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
