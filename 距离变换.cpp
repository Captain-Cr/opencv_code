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


float EDistance(int x1, int y1, int x2, int y2);			// ŷ�Ͼ���
float MDistance(int x1, int y1, int x2, int y2);			// D4���루���о��룩
float CDistance(int x1, int y1, int x2, int y2);			// D8���루���̾��룩
float Distsance(int x1, int y1, int x2, int y2, int type = 0);		// ����ѡ���������־��빫ʽ
void DistanceTrans(const Mat input, Mat &output, int disTtype);		// ����任����








int main33(int argc, char* argv[])
{
	Mat img = imread("E:\\data\\1.png");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
		return -1;
	}
	cout << "ͼ��ĸߡ���ֱ�Ϊ��" << img.rows <<"\t"<< img.cols << endl;
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);

	// ��ɻҶ�ͼ
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	// ��ֵ��
	Mat thresh;
	threshold(gray, thresh, 100, 255,THRESH_BINARY_INV);
	// ��ʴ
	Mat erodeImg;
	dilate(thresh, erodeImg,kernel,Point(-1,-1), 5);
	imshow("thresh", erodeImg);


	//Mat transMatD4, transMatD8, transMatE;
	//distanceTransform(erodeImg, transMatE, DIST_L2, 0);
	//distanceTransform(erodeImg, transMatD4, DIST_L1, 0, CV_8U);
	//distanceTransform(erodeImg, transMatD8, DIST_C, 0);

	//transMatE.convertTo(transMatE, CV_8U);
	//transMatD8.convertTo(transMatD8, CV_8U);

	//imshow("ŷʽ����任���ͼƬ", transMatE);
	//imshow("D4����任���ͼƬ", transMatD4);
	//imshow("D8����任���ͼƬ", transMatD8);
	//Mat BinaryImage = erodeImg;
	Mat output;
	//DistanceTrans(erodeImg, output, 1);
	//imshow("output", output*4);
	waitKey();
	


}

//float EDistance(int x1, int y1, int x2, int y2)
//{
//	// ŷ�Ͼ���
//	return sqrt(float((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
//
//}
//
//float MDistance(int x1, int y1, int x2, int y2)
//{
//	// D4����
//	return abs(x1 - x2) + abs(y1 - y2);
//}
//
//float CDistance(int x1, int y1, int x2, int y2)
//{
//	// D8����
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
//		����任������ 
//		Args��
//			const Mat input: ����Ķ�ֵͼ��
//			Mat &output:
//			int disType������ѡ���������־��빫ʽ
//	*/
//	Mat BinaryImage = input;
//	cout << BinaryImage.rows << "  " << BinaryImage.cols << endl;
//	uchar *pRowOne;					// ͼ��ǰÿһ�е�ָ��
//	uchar *pRowNext;				// ��������P�����е���һ�е�ָ��
//	float distance;					// �����������ص�P�ľ���
//	float Mindis;					// ��С����
//	
//	// �����Ͻǵ����½�
//	for (int i = 1; i <= BinaryImage.rows - 1; i++)
//	{
		// ��ȡ������������ÿһ�е�ָ�룬 ����ӵ�1�п�ʼ���ճ�һ��
		//pRowOne = BinaryImage.ptr<uchar>(i);
		//for (int j = 1; j <= BinaryImage.cols; j++)
		//{
		//	// ��ȡ����������һ�е�ָ��
		//	pRowNext = BinaryImage.ptr<uchar>(i - 1);

		//	// �����ң� ���ϵ���  ���㵽���ĵ�ľ���,   disType:ѡ��������Ĺ�ʽ
		//	distance = Distance(i, j, i - 1, j - 1, disType);			// q1
		//	Mindis = min((float)pRowOne[j], distance + pRowNext[j - 1]);	

		//	distance = Distance(i, j, i - 1, j, disType);				// q2
		//	Mindis = min(Mindis, distance + pRowNext[j]);

		//	// ��ȡ����������һ�е�ָ��
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

