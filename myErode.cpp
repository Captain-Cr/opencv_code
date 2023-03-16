#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	getStructuringElement(int shape, Size ksize, Point anchor=Point(-1,-1));
	�ú�����������ͼ����̬ѧ�����г��õľ��Ρ�ʮ�ֽṹ����Բ�ṹԪ�ء���һ������Ϊ���ɽṹԪ�ص����࣬��MORPH_RECT��MORPH_CROSS��MORPH_ELLIPSE��
	�ڶ�������Ϊ�ṹԪ�صĳߴ硣

	erode(src, dst, kernel, Point(-1,-1), iterations=1, borderType=BOREDER_CONSTANT, borderValue);
	�ú������ݽṹԪ�ض�����ͼ����и�ʴ���ڸ�ʴ��ͨ��ͼ��ʱ��ÿ��ͨ���������и�ʴ���㡣��Ҫע����ǣ��ú����ĸ�ʴ����ֻ���ͼ��ķ������ء�

	dilate(src, dst, kernel, Point(-1, -1), iterations=1, borderType=BOREDER_CONSTANT, borderValue);
	�ú������ݽṹԪ�ض�����ͼ��������͡������Ͷ�ͨ��ͼ��ʱ��ÿ��ͨ�����������������㡣��Ҫע����ǣ��ú��������͹���ֻ���ͼ��ķ������ء�

*/

// ���ư���������
void drawStats(Mat &img, int number, Mat centeriods, Mat stats, String str)
{
	RNG rng(100);
	vector<Vec3b> colors;
	for (int i = 0; i < number; i++)
	{
		// ʹ�þ��ȷֲ����������ɫ
		Vec3b vec = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec);
	}

	for (int j = 1; j < number; j++)
	{
		// ����λ��
		int center_x = centeriods.at<double>(j, 0);
		int center_y = centeriods.at<double>(j, 1);

		// ���α߿�
		int x = stats.at<int>(j, CC_STAT_LEFT);
		int y = stats.at<int>(j, CC_STAT_TOP);
		int w = stats.at<int>(j, CC_STAT_WIDTH);
		int h = stats.at<int>(j, CC_STAT_HEIGHT);

		// ���ĵ����
		circle(img, Point(center_x, center_y), 2, Scalar(0, 0, 255), 2, 8, 0);
		// ���λ���
		rectangle(img, Rect(x, y, w, h), colors[j], 1, 8, 0);
		putText(img, format("%d", j), Point(center_x, center_y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
	}
	imshow(str, img);
}


int mainadc(int argc, char* argv[])
{
	// �������ڸ�ʴ��ԭͼ
	uchar src_arr[] = { 0, 0, 0, 0, 255, 0,
					   0, 255, 255, 255, 255, 255,
					   0, 255, 255, 255, 255, 0,
					   0, 255, 255, 255, 255, 0,
					   0, 255, 255, 255, 255, 0,
					   0, 0, 0, 0, 0, 0 };
	Mat src = Mat(6, 6, CV_8U, src_arr);
	Mat struct1, struct2;
	struct1 = getStructuringElement(MORPH_RECT, Size(3, 3));		// ���νṹԪ��
	struct2 = getStructuringElement(MORPH_CROSS, Size(3, 3));       // ʮ�ֽṹԪ��

	Mat erodeSrc1, erodeSrc2;	// ��Ÿ�ʴ���ͼ��
	erode(src, erodeSrc1, struct1);
	erode(src, erodeSrc2, struct2);
	cout << erodeSrc1 << endl;
	cout << erodeSrc2 << endl;


	Mat img = imread("D:\\ͼƬ\\123.png");
	if (img.empty())
	{
		cout << "ͼ����ش���" << endl;
		return -1;
	}
	Mat img2;
	img.copyTo(img2);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat thresh;
	threshold(gray, thresh, 150, 255, THRESH_BINARY);
	imshow("thresh", thresh);
	Mat erode_img;
	erode(thresh, erode_img, struct1,Point(-1,-1), 3);
	imshow("erode_img", erode_img);

	// ��֤��ʴ��С��ͨ���ȥ��
	Mat src_label, src_stats, src_centeriods;
	int src_num = connectedComponentsWithStats(thresh, src_label, src_stats, src_centeriods);		// ԭͼ����ͨ����Ϣ
	drawStats(img, src_num, src_centeriods, src_stats, "δ��ʴʱͳ�Ƶ���ͨ��");                    // ����ͼ��

	Mat dst_label, dst_stats, dst_centeriods;
	int dst_num = connectedComponentsWithStats(erode_img, dst_label, dst_stats, dst_centeriods);
	drawStats(img2, dst_num, dst_centeriods, dst_stats, "��ʴ��ͳ�Ƶ���ͨ��");




	waitKey();


}