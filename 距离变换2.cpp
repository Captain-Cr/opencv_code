#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	����任��
	��1��ŷ�Ͼ��룺D[(i,j),(h,k)] = sqrt((i+h)^2 + (j+k)^2)							DIST_L2
	��2��D4���루���н������룩= |i - h | + |j - k |                                DIST_L1
	��3��D8���루���̾��룩 = max{|i - h |, |j - k |}                               DIST_C

	����任��������ͼ�������ص���ĳ�������ľ��룬������е����ص�ֵΪ0���ٽ����������ص��н�С��ֵ������ԽԶֵԽ��

	mask1:                                           mask2:                                            f(x): ͼ������ֵ��
		   q1    q2                                                q4                                  d(P,q): P��q�ľ��루ŷ�ϡ�D4��D8)
		   q3    P                                             P   q3				                   d0=f(P); d1=f(q1)+d(P,q1);  d2=f(q2)+d(P,q2);
		   q4                                                  q1  q2                                  d3=f(q3)+d(P,q3);    d4=f(q4)+d(P,d4)
																									   f(P)=min(d0, d1, d2, d3, d4)
*/
