#include <iostream>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace xfeatures2d;		


/*
��1��SIFT������
	SIFT�������SIFT�༰����غ�����װ��opencv_contrib��չģ���У�Ҫ��װopencv_contrib��չģ�����ʹ�ã�
	SIFT����opencv_contrib��չģ���µ�<xfeature2ds.hpp>ͷ�ļ��С���̳�Features2D�࣬��˿���ʹ��detect���������������compute�������������ӡ�
	���ڴ�֮ǰ��Ҫ����SIFT�������SIFT�����ṩ��create()�������ڴ���SFIT�������

	����ԭ�ͣ�
		static Ptr<SIFT> cv::xfeatures2d::SIFT::create(int nfeatures = 0, int nOctaveLayers = 3, double contrastThreshold = 0.04, double edgeThreshold = 10, double sigma = 1.6);
	�ú������Դ���һ��SIFT��ı�����֮����������ķ�������ͼ���е�SIFT�����㡣���У�nfeatures�Ǽ���SIFT���������Ŀ,nOctaveLayers�ǽ�������ÿ��Ĳ���,contrastThreshold�ǹ��˽ϲ����������ֵ����ֵԽ��
	���ص�������Խ�١�edgeThreshold�ǹ��˱�ԵЧӦ����ֵ����ֵԽ�󣬷��ص�������Խ��,sigma�ǽ�������0��ͼ���˹�˲���ϵ����

��2��SURF������
	SURF�������SURF�༰����غ���ͬ����װ��opencv_contrib��չģ���С�
	SURF����opencv_contrib��չģ���µ�<xfeatures2d.hpp>ͷ�ļ��С���̳�Features2D�࣬��˿���ʹ��detect()��compute��������ؼ���������ӡ�
	�ڴ�֮ǰ��Ҫ����SURF�������SURF���ṩcreate()�������ڴ���SURF�������

	����ԭ�ͣ�
		static Ptr<SURF> cv::xfeatures2d::SURF::create(double hessianThreshold = 100, int nOctaves = 4, int nOctaveLayers = 3, bool extended = false, bool upright = false);
	�ú������Դ���һ��SURF��ı�����֮����������ķ�������ͼ���е�SURF�����㡣
*/



int mainSURF(int argc, char* argv[])
{
	
	Mat img = imread("D:\\360�������������\\2.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ����SURF�����������
	Ptr<SURF> sufr = SURF::create(500,		// �ؼ�������
		4,				// 4�������
		3,				// ÿ���������3��
		true,			// ʹ��128ά������
		false			// ����ؼ��㷽��
	);

	// ����SURF�ؼ���
	vector<KeyPoint> Keypoints;
	sufr->detect(img, Keypoints);		// ȷ���ؼ���
	// ����������
	Mat descriptions;
	sufr->compute(img, Keypoints, descriptions);	

	// ���ƹؼ���
	Mat img1;
	img.copyTo(img1);
	// ���Ʋ����ǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, img, Scalar(255, 255, 255));
	// ���ƺ��нǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, img1, Scalar(255, 255, 255),
		DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// ������ʾ
	//imshow("img", img);
	imshow("�����ǶȺʹ�С�Ľ��", img);
	imshow("���нǶȺʹ�С�Ľ��", img1);
	waitKey();
	return 0;
}