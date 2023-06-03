#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


/*
	Description: Shi-Tomas�ǵ��⡣Harris�ǵ�����ϵ���Ĵ�С������ȫ�ĸ���������������֮��Ĵ�С��ϵ�����Shi��Tomas��Harris�ǵ������ָ����е�������������������Сֵ��Ϊ�ǵ�����ϵ����
	R = min(��1����2��; ��R����ĳһ��ֵ���򽫸õ���Ϊ�ǽǵ㡣

	Function��
		void  goodFeaturesToTrack(InputArray image, OutputArray corners, int maxCorners, double qualityLevel, double minDistance, InputArray mask = noArray(), int blockSize = 3, 
	bool useHarrisDetector = False, double k = 0.04);
	�ú����ܹ�Ѱ��ͼ����ָ�������ڵ�Shi-Tomas�ǵ㣬�ú�������ֵ����ѽǵ����Ӧ�������˾�����ֵ�ڲ�ͬͼ����Ч����������������⣬��������ֱ������ǵ�����꣬����Ҫ�����������ٴ��ж��Ƿ�Ϊ�ǵ�
	

*/


int mainGoodFeaturesToTrack(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\lena.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}
	// ������ڵڶ��ַ������ƽǵ�
	Mat img2;
	img.copyTo(img2);
	Mat gray; 
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// ��ȡ�ǵ�
	int maxCorners = 100;			// ���ǵ�����
	double quality_level = 0.01;		// �����ȼ�������ָ��ֵ����ѽǵ�ı�����ϵ
	double minDistance = 0.04;			// �����ǵ�֮�����Сŷʽ����
	vector<Point2f> corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);

	// ���ƽǵ�
	vector<KeyPoint> keypoints;			// ��Žǵ��keyPoint��
	RNG rng(10086);
	for (int i = 0; i < corners.size(); i++)
	{
		// ��һ�ֻ��ƽǵ㣬��circle������������
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int r = rng.uniform(0, 256);
		circle(img, corners[i], 2, Scalar(b, g, r), 2, 8, 0);

		// ���ǵ�����KeyPoint����
		KeyPoint keypoint;
		keypoint.pt = corners[i];
		keypoints.push_back(keypoint);
	}


	// �ڶ��ֻ��Ʒ���
	drawKeypoints(img2, keypoints, img2);
	// ������ƽǵ���
	imshow("ʹ��circle�����������ƽǵ���", img);
	imshow("ʹ��drawKeyPoint���ƽǵ���", img2);
	waitKey();
	destroyAllWindows();
	return 0;

}