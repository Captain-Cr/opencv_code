#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	ģ��ƥ�䣺 �������ڴ�ƥ��ͼƬ��ѡ����ģ��ͼƬ��ͬ�ĳߴ�Ļ������ڣ�ͨ���Ƚϻ���������ģ������Ƴ̶ȣ��жϴ�ƥ��ͼ���Ƿ�����ģ��ͼ����ͬ�����ݡ�

	ģ��ƥ�����̣�
		1���ڴ�ƥ��ͼ��ѡȡ��ģ��ߴ��С��ͬ�Ļ������ڣ�
		2���Ƚϻ���������ÿ��������ģ���ж�Ӧ���ػҶ�ֵ�Ĺ�ϵ������ģ���뻬�����ڵ������ԣ�
		3�����������ڴ����Ͻǿ�ʼ���һ��������������ұߺ����»���һ�У�Ȼ�����������¿�ʼ��������¼ÿһ���ƶ�������ģ���뻬�����ڵ������ԣ�
		4���Ƚ�����λ�õ������ԣ�ѡ�����������Ļ���������Ϊ��ѡƥ������

*/



//float tm_SQDIFF(Mat x, Mat x_p)
Mat SQDIFF(Mat T, Mat I)
{
	// Ϊ�������ںʹ�ƥ��ͼ��������ƶȡ�
	// ƽ��� R(x, y) = ��(T��x', y') - I(x+x', y+y')^2)      ����TΪģ��ͼ��, IΪԭʼͼ��   ��ģ���뻬��������ȫƥ��ʱ��������ֵΪ0��ƥ���Խ�ͣ�������ֵԽ��

	double R = 0.0;
	int re_height = I.cols - T.cols + 1;
	int re_width = I.rows - T.cols + 1;
	cout << re_width << endl;
	Mat result = Mat(re_height, re_width, CV_32F);				// �����Ծ�������CV_32F������������ģ��������ϵ������ڻ����������Ͻǵ�һ������
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
	// �Լ�д��ģ��ƥ���㷨�� ��������Ĳ���
	Mat src = imread("D:\\ͼƬ\\1.jpg");
	Mat temp = imread("D:\\ͼƬ\\1_templ.png");
	if (src.empty() || temp.empty())
	{
		cout << "ͼƬ���ش���" << endl;
		return -1;
	}

	SQDIFF(temp, src);

}










int mainfaa()
{
	Mat src = imread("D:\\ͼƬ\\1.jpg");
	Mat temp = imread("D:\\ͼƬ\\1_templ.png");
	if (src.empty() || temp.empty())
	{
		cout << "ͼƬ���ش���" << endl;
		return -1;
	}
	imshow("src", src);
	imshow("temp", temp);
	
	Mat result;   // �����Ծ�������CV_32F������������ģ��������ϵ������ڻ����������Ͻǵ�һ������
	matchTemplate(src, temp, result, TM_CCOEFF_NORMED);  // ģ��ƥ��			TM_CCOEFF_NORMED����ȫƥ��Ϊ1�� ��ȫ��ƥ��Ϊ0
	
	
	double maxVal, minVal;		
	Point maxLoc, minLoc;
	// Ѱ��ƥ�����е����ֵ����Сֵ�Լ�����λ��
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);	


	// �������ƥ�������
	rectangle(src, Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 255, 0));
	imshow("ƥ�������", src);

	myMatchTemplate();
	waitKey();




	


	return 0;





}