#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	getRotationMatrix2D(center, angle, scale);		������ת�ǶȺ���ת���ģ�����ͼ����ת���󣬷���ֵΪMat�࣬��һ�� 2 X 3�ľ���
	��ϵʽ��				 ��    ��   ��1-��) * center.x - �� * center.y						����: �� = scale * cos(angle)
				Rotation =  -��    ��    �� * center.x + (1 - ��) * center.y					      �� = scale * sin(angle)




	warpAffine(src, dst, M, dsize, flags,  borderMode, borderValue)�� �������Ǳ任���󣬵��ĸ����������ͼ��ߴ磬���ǲ�ֵ��־���������ر߽����Ʒ�����־��
	
	����任����ͼ����ת��ƽ�ƺ����Ų�����ͳ�ƣ����Ա�ʾΪ���Ա任��ƽ�Ʊ任�ĵ��ӡ�                         X
							a00    a01    b00			ͼ������ֵΪ��[X           ��任������ֵΪ��T = A * Y   + B 
	�任���� M = [A  B]  =  a10    a11    b10						   Y]



	���ֱ���任ǰ������ͼ���3�����ص������Ӧ��ϵ���Ϳ�����÷���任�еı任����M.

	getAffineTransform(const Point2f src[],  const Point2f dst[])  ����ֵ��һ��2*3�ı任����


*/

int main332(int argc, char* argv[])
{
	Mat img = imread("E:\\XIUGOU.png");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
	}


	Mat rotation0, rotation1, img_warp0, img_warp1;
	double angle = 30;			// ����ͼ����ת�Ƕ�
	Size dst_size(img.rows, img.cols);			// �������ͼ��ĳߴ�
	Point2f center(img.rows / 2.0, img.cols / 2.0);		// ����ͼ����ת����
	rotation0 = getRotationMatrix2D(center, angle, 1);		// �������任����
	warpAffine(img, img_warp0, rotation0, dst_size);		// ����任
	imshow("img_warp0", img_warp0);

	// ���ݶ����3������з���任
	Point2f src_point[3];			// ���������
	Point2f dst_point[3];

	src_point[0] = Point(0, 0);			// ԭʼͼ���3����
	src_point[1] = Point(0, (float)(img.cols - 1));
	src_point[2] = Point((float)(img.rows - 1), (float)(img.cols - 1));

	// ����任��ͼ���3����
	dst_point[0] = Point2f((float)(img.rows)*0.11, (float)(img.cols)*0.20);
	dst_point[1] = Point2f((float)(img.rows)*0.15, (float)(img.cols)*0.70);
	dst_point[2] = Point2f((float)(img.rows)*0.81, (float)(img.cols)*0.85);

	rotation1 = getAffineTransform(src_point, dst_point);		// ���ݶ�Ӧ����ȡ����任����
	warpAffine(img, img_warp1, rotation1, dst_size);			// ���з���任
	imshow("img_warp1", img_warp1);
	waitKey();
	return 0;









}