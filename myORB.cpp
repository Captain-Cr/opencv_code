#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	Description:�������ɹؼ���������ӹ��ɣ�������SIFT��SUFT��ORB
	Opencv4�д��features2D���࣬���ж����˼��������ʱ��Ҫ�Ĺؼ����⺯���������Ӽ��㺯�������������������ͼ���д�����Ⱥ�����ֻҪ����ĳ��������̳���Features2D�࣬�Ϳ���ͨ�����еĺ���
	����ؼ���������ӡ���ʵ�ϣ�Opencv4�����е������㶼�̳���Features2D�ࡣ

	��غ�����
		��1��virtual void Features2D::detect(InputArray image, std::vector<KeyPoint>& keypoints, InputArray mask = noArray());
	�ú����ܹ�������Ҫ���㲻ͬ��������Ĺؼ��㡣��һ����������Ҫ����ؼ����ͼ��ͼ���������̳�Features2D�����������ء��ڶ��������Ǽ�⵽�Ĺؼ��㣬�������������Ϊvector<KeyPoint>�������У�
	��ʱ�ؼ�����������йؼ�������꣬���йؼ��㷽�򡢰뾶�ߴ�ȣ������������������������ء����һ�������Ǽ���ؼ���ʱ������ͼ�����ڱ�ʾ��Ҫ����Щ�������ؼ��㣬���������Ҫ������ͼ�����
	��ͬ�ĳߴ粢����������ΪCV_8U����Ҫ����ؼ�����������������÷���Ԫ�ر�ʾ��

		��2��virtual void Features2D::compute(InputArray image, std::vector<KeyPoint>& keypoints, OutputArray descriptors);
	�ú����ܹ����������ͼ���ָ��ͼ���еĹؼ����������õ�ÿ���ؼ���������ӡ������ӣ�����Ψһȷ���ؼ����һ�����֣�����ͨ������������������ͬ�Ĺؼ��㣬Ҳ�����ڲ�ͬͼ��Ѱ��ͬһ���ؼ���

		��3��virtual void Features2D::detectAndCompute(InputArray image, InputArray mask, std::vector<KeyPoint>& keypoints, OutputArray descriptor, bool useProvideKeyPoints =false);
	�ú���������ؼ���������ӵĹ��ܼ�����һ�𣬿��Ը�������ͼ��ֱ�Ӽ�����ؼ���͹ؼ����Ӧ�������ӡ�

	ע�⣺����ĺ�������Ҫ��������̳�֮�����ʹ�ã�������ORB�������ORB���У�����ͨ��ORB::detect()��������ORB������Ĺؼ��㣻��SIFT�������SIFT���У�ͨ��SIFT::detect()��������SiFT�����Ĺؼ��㡣

	
		��4��static Ptr<ORB> cv::ORB::create(int nfeatures = 500, float scaleFactor = 1.2f, int nLevel = 8, int edgeThreshold = 31, int firstLevel = 0, int WTA_K =2, 
												ORB::ScoreType scoreType = ORB::HARRIS_SCORE, int patchSize = 31, int fastThreshold = 20);
	�ú������Դ���һ��ORB��ı�����֮���������еķ�������ͼ���е�ORB�����㡣

	*/




int mainORB(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\lena.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ����ORB�����������
	Ptr<ORB> orb = ORB::create(500,					// ��������Ŀ
		1.2f,					// ������֮������ű���
		8,						// ������ͼ�����ϵ��
		31,						// ��Ե��ֵ
		0,						// ԭͼ�ڽ������Ĳ�����ԭͼ�ǽ������ĵڼ��㣩
		2,						// ����������ʱ��Ҫ�õ����ص���Ŀ
		ORB::HARRIS_SCORE,			// ʹ��Harris��������������
		31,						// ����������ʱ�ؼ�����Χ������ߴ�
		20  					// ����FAST�ǵ�ʱ����ֵ��ֵ����ֵ
		);
	// ����ORB�ؼ���
	vector<KeyPoint> keypoints;
	orb->detect(img, keypoints, Mat());

	// ����ORB������
	Mat descriptions;
	orb->compute(img, keypoints, descriptions);

	// ����������
	Mat imgAngel;
	img.copyTo(imgAngel);
	// ���Ʋ����ǶȺʹ�С�Ľ��
	drawKeypoints(img, keypoints, img, Scalar(255, 255, 255));
	// ���ƺ��нǶȺʹ�С�Ľ��
	drawKeypoints(img, keypoints, imgAngel, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	// ��ʾ���
	imshow("�����ǶȺʹ�С�Ľ��", img);
	imshow("���нǶȺʹ�С�Ľ��", imgAngel);
	waitKey();
	destroyAllWindows();
	return 0;

}