#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:��ˮ���㷨����ˮ��䷨���ƣ�����������ˮ��䷨�Ǵ�ĳ�����ؽ��зָ��һ�־ֲ��ָ��㷨������ˮ���㷨�Ǵ�ȫ�ֳ�������Ҫ��ȫ�ֽ��зָ

	Function:
		void cv::watershed(InputArray Image, InputOutputArray maskers);

	Paramerates:
		Images:����ͼ����Ҫ����ΪCV_8U���������͵���ͨ��ͼ��
		maskers������/���CV_32S�������͵ĵ�ͨ��ͼ��ı�ǽ������ԭͼ�������ͬ�ĳߴ硣

	Stage��
		ÿ��������򱻱�ʾΪ��������ֵ1,2,3�ȵ�һ��������ͨ���������ͼ��ĳߴ�������ͼ����ͬ������������ΪCV_32S������ʹ��findContours()������drawContours()�����Ӷ�ֵ�����еõ�������ͼ��
		���ͼ��������û�б���ǵ�����ֵ��Ϊ0���ں������ʱ����������֮��ķָ�����-1��ʾ��
*/



int mainWatershed(int argc, char* argv[])
{
	Mat img = imread("D:\\abc.png");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	
	Mat gray, canny;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//threshold(gray, thresh, 120, 255, THRESH_BINARY);
	Canny(gray, canny, 80, 150);

	// ������䣬ÿ��������䲻ͬ��ֵ���ֱ�Ϊ1,2��������
	vector<vector<Point>> contours;				// ������
	vector<Vec4i> hierarchy;						// ���������㼶
	findContours(canny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// ���л������
	Mat maskWatershed = Mat::zeros(img.size(), CV_32S);
	for (int i = 0; i < contours.size(); i++)
	{
		// ��ÿ���������л������
		drawContours(maskWatershed, contours, i, Scalar(i + 1), -1, 8, hierarchy, INT_MAX);
	}
	// ��ˮ�뷨�� ��Ҫ��ԭͼ����д���
	watershed(img, maskWatershed);


	// ��ˮ���ͼ���ԵΪ-1�� ����Ϊ0�� �����Ϊ����1,2��������
	RNG rng(10086);
	vector<Vec3b> colors;			// ������ɼ�����ɫ
	for (int j = 0; j < contours.size(); j++)
	{
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	
	// ����ͼ�񣬽�ͼ��������ֽ�����ʾ
	Mat resultImg = Mat::zeros(img.size(), CV_8UC3);		// ����ָ�ͼ��
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			// ����ÿ���������ɫ
			int index = maskWatershed.at<int>(y, x);
			// �����߽类��Ϊ-1, �ð�ɫ���Ʊ߽�
			if (index == -1)
			{
				resultImg.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
			}
			// ����������0�� �ú�ɫ����
			else if (index <= 0 || index > contours.size())
			{
				resultImg.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
			}
			// �������������Ӧ������������ɫ���л���
			else
			{
				resultImg.at<Vec3b>(y, x) = colors[index - 1];
			}
		}
	}
	addWeighted(img, 0.5, resultImg, 0.5, 1, resultImg);
	imshow("result", resultImg);
	

	// ���Ƴ�ÿ�������ͼ��
	for (int k = 1; k <= contours.size(); k++)
	{
		Mat resImg1 = Mat(img.size(), CV_8UC3);
		for (int a = 0; a < resultImg.rows; a++)
		{
			for (int b = 0; b < resultImg.cols; b++)
			{
				int index = maskWatershed.at<int>(a, b);
				if (index == k)
				{
					resImg1.at<Vec3b>(a, b) = img.at<Vec3b>(a, b);		// ��ԭͼ����������index�����ؽ�ȡ����
				}
				else
				{
					resImg1.at<Vec3b>(a, b) = Vec3b(0, 0, 0);			// ����������index����0
				}

			}
		}
		imshow(to_string(k), resImg1);
	}

	

	imshow("img", img);
	imshow("canny", canny);

	waitKey();
	destroyAllWindows();
	return 0;
}
