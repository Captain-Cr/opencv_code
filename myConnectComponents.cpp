#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
	connectedComponents(InputArray img, OutputArray labels, connectivity, ltype, ccltype);
		-img: ����ǲ�ͬ��ͨ��ĵ�ͨ��ͼ���������ͱ���ΪCV_8U
		-labels�� ��ǲ�ͬ��ͨ�������ͼ��������ͼ�������ͬ�ĳߴ�
		-connectivity: �����ͨ��ʱʹ�õ��������࣬ 4��ʾ4���� 8��ʾ8����
		-ltype: ���ͼ����������ͣ�Ŀǰ֧��CV_32S��CV_16U����
		-ccltype: �����ͨ��ʱʹ�õ��㷨���ͱ�ǡ� CCL_WU:8����ʹ��SAUF�㷨��4����ʹ��SAUF�� CCL_DEFAULT:8ʹ��BBDT,4ʹ��SAUF; CCL_GRANA: 8ʹ��BBDT, 4ʹ��SAUF
	
	�ú������ڼ����֪ͼ������ͨ��ĸ���������ͼ���н���ͬ����ͨ���ò�ͬ�����ֱ�ǩ��ǣ�����0λ������
	ͬʱ��������һ��int���͵ķ����������ڱ�ʾͼ������ͨ�������

*/


int mainfae(int argc, char* argv[])
{
	RNG rng(10086);   // ���������

	Mat img = imread("D:\\ͼƬ\\123.jpg");
	resize(img, img, Size(600, 800));
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	//�Ҷ�ͼ
	Mat gray, thresh;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, thresh, 20, 255, THRESH_BINARY);
	Mat dilate_img;
	Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
	dilate(thresh, dilate_img, kernel, Point(-1, -1), 3);
	imshow("thresh", dilate_img);

	// ͳ����ͨ��
	Mat connect;
	int num_connect = connectedComponents(dilate_img, connect, 8, CV_16U);
	cout << "���� " << num_connect - 1 << " ������" << endl;		// ��ȥ����


	vector<Vec3b> colors;
	for (int i = 0; i < num_connect; i++)
	{
		// ʹ�þ��ȷֲ��������ȷ����ɫ
		Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3);
	}

	Mat result = Mat::zeros(img.size(), img.type());
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			int color_index = connect.at<uint16_t>(i, j);			// ��ȡ��ͨ��ͼ������
			if (color_index == 0)				// ������ɫ���ı�
			{
				continue;
			}
			result.at<Vec3b>(i, j) = colors[color_index];
		}
	}


	imshow("result", result);
	waitKey();
	return 0;

}