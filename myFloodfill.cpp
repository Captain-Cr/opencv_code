#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description:��ˮ��䷨�Ǹ������ػҶ�ֵ֮��Ĳ�ֵѰ����ͬ������ʵ�ַָ
	��ˮ�����裺
		1��ѡ�����ӵ㣨x��y��
		2�������ӵ�Ϊ���ģ��ж�4-�������8-���������ֵ�����ӵ����صĲ�ֵ������ֵС����ֵ�����ص���ӵ������ڣ�
		3�����¼�������ص���Ϊ�µ����ӵ㣬����ִ�еڶ�����ֱ��û���µ����ص㱻��ӽ�������Ϊֹ��

	Function:
		1��int cv::floodFill(InputOutputArray image,				// ���뼰���ͼ�񣬿���ΪCV8U_����CV_32F�������͵ĵ�ͨ��������ͨ��ͼ��
							 InputOutputArray mask,					// ������󣬳ߴ������ͼ���͸߸���2�ĵ�ͨ��ͼ�����ڱ����ˮ����������
							 Point seenpoint,						// ���ӵ�
							 Scalar newval,						    // �������ӵ����������ص��������ֵ
							 Rect* rect = 0,						// ���ӵ���ˮ����������С���α߽磬Ĭ��ֵΪ0����ʾ������߽�
							 Scalar loDiff = Scalar(),				// ��ӽ����ӵ������������½��ֵ��������ĳ���ص������ֵ�����ӵ�����ֵ�Ĳ�ֵ���ڸ�ֵʱ�������ص㱻��ӽ����ӵ����ڵ�����
							 Scalar upDiff = Scalar(),				// ��ӽ����ӵ������������Ͻ��ֵ�������ӵ�����ֵ������ĳ���ص������ֵ�Ĳ�ֵС�ڸ�ֵʱ�������ص㱻��ӽ����ӵ����ڵ�����
							 int flags = 4							// ��ˮ��䷨�Ĳ�����־����3������ɣ��ֱ��ʾ�������ࡢ��������б�������ص������ֵ������㷨�Ĺ��򣬿����±��и�����
							 );

						floodFill()������ˮ��䷨�Ĳ�����־
		��־				���						����
  FLOODFILL_FIXED_RANGE    1<<16                   ������øò�������ô�����ǵ�ǰ���ص����ʼ���ӵ�����ֵ֮��Ĳ�ֵ�������������ӵ�����ֵ�뵱ǰ����ֵ֮��Ĳ��죬����Χ�Ƿ񸡶��ı�־
  FLOODFILL_MASK_ONLY	   1<<17				   ������ã���ô�ú����������ԭʼͼ�񣬼����Ե��ĸ�����new Val��ֻ�����������


		2��int cv::floodFill(InputOutputArray image,
							 Point seedPoint,
							 Scalar newVal,
							 Rect* rect = 0,
							 Scalar loDiff = Scalar(),
							 Scalar upDiff = Scalar(),
							 int flags = 4
							 )
							 
							 
*/

int main_floodFill(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼƬ\\cat.jpg");
	if (img.empty())
	{
		cout << "ͼƬ���ش��󣡣���" << endl;
		return -1;
	}

	RNG rng(10086);		// ����������������������

	// ���ò�����־flags
	int connectivity = 8;			// ��ͨ����ʽ
	int maskVal = 255;				// ����ͼ�����ֵ
	int flags = connectivity | (maskVal << 8) | FLOODFILL_FIXED_RANGE;		// ��ˮ��������ʽ��־

	// ������ѡ�����ص�Ĳ�ֵ
	Scalar loDiff = Scalar(20, 20, 20);
	Scalar upDiff = Scalar(20, 20, 20);

	// ��������������
	Mat mask = Mat::zeros(img.rows + 2, img.cols + 2, CV_8UC1);

	while (true)
	{
		// �������ͼ���е�ĳһ���ص�
		int py = rng.uniform(0, img.rows - 1);
		int px = rng.uniform(0, img.cols - 1);
		Point point = Point(px, py);

		// ��ɫͼ������������ֵ
		Scalar newVal = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

		// ��ˮ��亯��
		int area = floodFill(img, mask, point, newVal, &Rect(), loDiff, upDiff, flags);

		// ������ص������������Ŀ
		cout << "���ص�x��" << point.x << "   y:" << point.y
			<< "   ���������Ŀ" << area << endl;

		// �������ͼ����
		imshow("���Ĳ�ɫͼ��", img);
		imshow("����ͼ��", mask);

		// �ж��Ƿ��������
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			break;
		}

	}
	destroyAllWindows();
	return 0;
}