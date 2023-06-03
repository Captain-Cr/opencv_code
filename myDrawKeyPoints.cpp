#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description:һ���Ի������еĹؼ���

	Function:
		void cv::drawKeypoints(InputArray image, const vector<KeyPoint>& keypoints, InputOutputArray outImage, const Scalar& color=Scalar::all(-1), DrawMatchesFlags flags= DrawMatchesFlags::DEFAULT)
	�ú�������һ������ͼ���л������е����ص㣬�Թؼ���ΪԲ�Ļ��ƿ���Բ����ͻ����ʾ�ؼ�����ͼ���е�λ�á���һ����������Ҫ���ƹؼ����ԭͼ�񣬿����ǵ�ͨ������ͨ��ͼ�񡣵ڶ�����������ԭͼ�еĹؼ���
	������vector�����д�����ʾ�ؼ���KeyPoint���͵����ݡ������������ǻ��ƹؼ��������ͼ���Ƿ����øò������ݻ��ƹؼ�����ȡ�������һ��������ȡֵ�����ĸ������ǻ��ƹؼ������Բ����ɫ�����ѡ��
	Ĭ��ֵ����ô��ʾ�������ɫ���ƿ���Բ�����һ��������ʾ���ƹ��ܵ�ѡ���־���ò�����ѡ��ֵ�Լ��������±���ʾ

										drawKeyPoint()�������ƹ���ѡ���־��ѡ�����Լ�����
			��־����                     ���					����
			DEFAULT						  0					�������ͼ����󣬽����ƽ����ŵ����ͼ���У����һ���Բ�α�ʾ�ؼ���λ�ã�����ʾ�ؼ����С�ͷ���
			DRAW_OVER_OUTIMG			  1					���������ͼ�����ֱ����ԭͼ�л��ƹؼ���
			NOT_DRAW_SINGLE_POINTS        2					�����Ƶ����ؼ���
			DRAW_RICH_KEYPOINTS           4					�ڹؼ���λ�û���Բ�Σ�Բ�����ֹؼ���Ĵ�С�ͷ���

	KeyPoint�ࣺ
		class KeyPoint
		{
			float angle;		// �ؼ���ĽǶ�
			int class_id;		// �ؼ���ķ����
			int octave;			// ��������Դ��"������")
			Point2f pt;			// �ؼ�������
			float response;		// ��ǿ�ؼ������Ӧ�������ڽ�һ������Ͷ��β���
			float size;			// �ؼ��������ֱ��


*/

int mainDrawKeypoint(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\1.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ������ɹؼ���
	RNG rng(10086);
	vector<KeyPoint> keypoints;
	for (int i = 0; i < 20; i++)
	{
		float pty = rng.uniform(0, img.rows - 1);
		float ptx = rng.uniform(0, img.cols - 1);
		KeyPoint keypoint;
		keypoint.pt.x = ptx;
		keypoint.pt.y = pty;
		keypoints.push_back(keypoint);
	}

	// ���ƹؼ���
	drawKeypoints(img, keypoints, img, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), DrawMatchesFlags::DEFAULT);
	
	// ��ʾ
	imshow("img", img);
	waitKey();
	destroyAllWindows();
	return 0;



}