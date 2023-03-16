#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	opencvʹ��morphologyEx()����ʵ����̬ѧ������
	���������ȸ�ʴ�����ͣ�ȥ������С�׵㣬������С��ͨ�򣬱����ϴ���ͨ��ͬʱ�ܹ�������������ϸ��������������룻 
	�����㣺�����ͺ�ʴ��ȥ������С�ڵ㣬ȥ����ͨ����С�Ϳն���ƽ�����������������ٽ�����ͨ��
	��̬ѧ�ݶȣ��ܹ�����Ŀ��߽磬���ݸ�ʴ��������ԭͼ֮��Ĺ�ϵ�õ�����̬ѧ�ݶȿɷ�Ϊ�����ݶȡ��ڲ��ݶȺ��ⲿ�ݶȣ������ݶ�=����-��ʴ�� �ڲ��ݶ�=ԭͼ-��ʴ���ⲿ�ݶ�=����-ԭͼ��
	��ñ���㣺��ԭͼ���뿪������֮��Ĳ�ֵ��Ҳ���ǵõ�С�׵㣻
	��ñ���㣺�Ƕ�ͼ����б�����֮��ӱս���м�ȥԭͼ��Ҳ���ǵõ�С�ڵ㣻
	���в����б任��ͼ��ʴֻ��ͼ���ܹ����ṹԪ���е����з���Ԫ�ذ��������ǻ��в����б任Ҫ��ԭͼ������Ҫ���ںͽṹԪ��һģһ���Ľṹ�����ṹԪ���з���Ԫ��Ҳ��Ҫͬʱ�����ǣ�

*/


int mainaef(int argc, char* argv[])
{
	// ������֤��̬ѧӦ�õĶ�ֵ������
	Mat src = (Mat_<uchar>(9, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	namedWindow("src", WINDOW_NORMAL);
	imshow("src", src);

	// 3x3�ṹԪ��
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	// �Զ�ֵͼ�������̬ѧ����
	Mat open, close, gradient, tophat, blackhat, hitmiss;

	// �Զ�ֵͼ����п�����
	morphologyEx(src, open, MORPH_OPEN, kernel);
	namedWindow("open", WINDOW_NORMAL);
	imshow("open", open);

	// �Զ�ֵͼ����б�����
	morphologyEx(src, close, MORPH_CLOSE, kernel);
	namedWindow("CLOSE", WINDOW_NORMAL);
	imshow("CLOSE", close);

	// ��ͼ�������̬ѧ�ݶ�����
	morphologyEx(src, gradient, MORPH_GRADIENT, kernel);
	namedWindow("grad", WINDOW_NORMAL);
	imshow("grad", gradient);

	// ��ͼ����ж�ñ����
	morphologyEx(src, tophat, MORPH_TOPHAT, kernel);
	namedWindow("tophat", WINDOW_NORMAL);
	imshow("tophat", tophat);

	// ͼ��ͼ���к�ñ����
	morphologyEx(src, blackhat, MORPH_BLACKHAT, kernel);
	namedWindow("BLACKHAT", WINDOW_NORMAL);
	imshow("BLACKHAT", blackhat);

	// �Զ�ֵ��ͼ����л��в����б任
	morphologyEx(src, hitmiss, MORPH_HITMISS, kernel);
	namedWindow("HITMISS", WINDOW_NORMAL);
	imshow("HITMISS", hitmiss);



	waitKey();
	return 0;
}