#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	distanceTransform(src, dst, labels, distanceType, maskSize, labelType=DIST_LABEL_CCOMP);
	����ʵ��ͼ��ľ���任����ͳ��ͼ�����������ؾ���0���ص���С���롣��һ������Ϊ������任������ͼ������ͼ�������CV_8U�ĵ�ͨ��ͼ��
	�ڶ�������������任��ͼ�񣬾����п��ܻ����256�����ͼ����������Ϳ�ѡCV_8U��CV_32F.
	���������������ԭʼͼ�����ɢVoronoiͼ�����ͼ������������ΪCV_32S�ĵ�ͨ��ͼ�񣬳ߴ��ԭͼ��ͬ��
	���ĸ������Ǿ���任������ʹ�õľ������࣬��(ŷʽ�����������̣� DIST_l2,DIST_L1,DIST_C����
	�������������ȡ·��ʱ����������ߴ磬Ĭ��ѡ���������ߴ�Ϊ3x3.
	���һ�������ǹ�����ǩ��������ͣ���labelType==DIST_LABEL_CCOMPʱ���ú������Զ�������ͼ�����ҵ�0���ص���ͨ������������ͬ�ı�ǩ������ǣ�
	��labelType==DIST_LABEL_PIXEL,�ú���ɨ������ͼ���ò�ͬ�ı�ǩ�������0���ء�

	// ����
	distanceTransform(src, dst, distanceType, maskSize, dstType=CV_32F)
*/

int mainga(int argc, char* argv[])
{
	// �������׾���������ȡ����֮��ľ���
	Mat a = (Mat_<uchar>(5, 5) << 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 0, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1);

	Mat dist_L1, dist_L2, dist_c;

	// �����������
	distanceTransform(a, dist_L1, DIST_L1, 3, CV_8U);
	cout << "�������룺"<<endl << dist_L1 << endl;

	// ����ŷʽ����
	distanceTransform(a, dist_L2, DIST_L2, 5, CV_8U);
	cout << "ŷʽ���룺"<<endl << dist_L2 << endl;

	// �������̾���
	distanceTransform(a, dist_c, DIST_C, 5, CV_8U);
	cout << "���̾��룺" << endl << dist_c << endl;
	
	// ��ͼ����о���任
	Mat img = imread("D:\\ͼƬ\\1.jpg",0);
	if (img.empty())
	{
		cout << "ͼ����ش���" << endl;
		return -1;
	}

	Mat riceBW, riceINV;

	// ��ͼ��ת��Ϊ��ֵͼ��ͬʱ�Ѻڰ����������ɫ����
	threshold(img, riceBW, 150, 255, THRESH_BINARY);
	threshold(img, riceINV, 150, 255, THRESH_BINARY_INV);

	// ����任
	Mat dist, dist_INV;
	distanceTransform(riceBW, dist, 1, 3, CV_32F);    // Ϊ����ʾ���������������ͱ��CV_32F
	distanceTransform(riceINV, dist_INV, 1, 3, CV_8U);

	imshow("riceBW", riceBW);
	imshow("dist", dist);
	imshow("riceBW_INV", riceINV);
	imshow("dist_INV", dist_INV);
	waitKey();
	return 0;


}