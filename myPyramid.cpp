#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	ͼ�������
	��1����˹��������ͨ���²������ϵؽ�ͼ��ĳߴ���С��  �����Խ���߶Ȳ�ȷ���ԣ�
	��2��������˹�������� ���ڵ�i��ĸ�˹������ͼ������ͨ���²����õ���i+1����߲��ڸ�˹�������е�ͼ�� ֮��Ե�i+1��ͼ������ϲ�����ͼ��ߴ绹ԭ�ص�i��Ĵ�С�������ȡ��˹��������i���뾭���ϲ�����õ�ͼ��Ĳ�ֵͼ�񣬾���������˹������
*/

int main243(int argc, char* argv[])
{
	Mat img = imread("D:\\ͼƬ\\44.jpg");
	if (img.empty())
	{
		cout << "ͼ����ش��󣡣���" << endl;
		return -1;
	}

	// ��ȡ��˹������
	vector<Mat> Gauss, Laps;			// ��˹��������������˹������
	int Level = 3;						// �������Ĳ���
	Gauss.push_back(img);			// ��ԭͼ��Ϊ�������ĵ�0��
	for (int i = 0; i < Level; i++)
	{
		Mat gauss;
		pyrDown(Gauss[i], gauss);		// �²���
		Gauss.push_back(gauss);
		imshow(to_string(i), gauss);
		waitKey();
	}


	// ����������˹������
	for (int j = Gauss.size()-1; j > 0; j--)
	{
		cout << "j=" << j << endl;
		Mat lap, upGaussian;
		if (j == Gauss.size() -1)		// �����������һ��
		{
			Mat down;
			pyrDown(Gauss[j], down);			// �²���
			pyrUp(down, upGaussian);		// ���²�����ͼƬ�����ϲ���
			imshow("up", upGaussian);
			waitKey();
			cout << "Gauss[j]�ĸ߿�" << Gauss[j].rows << " " << Gauss[j].cols << endl;
			cout << "upGaussian�ĸ߿�" << upGaussian.rows << "  " << upGaussian.cols << endl;
			lap = Gauss[j] - upGaussian;		// ͼ���ֵ
			Laps.push_back(lap);
		}

		pyrUp(Gauss[j], upGaussian);			// �ϲ���
		lap = Gauss[j - 1] - upGaussian;		// ͼ���ֵ
		Laps.push_back(lap);
	}

	// �鿴����ͼ���ͼ�������
	for (int i = 0; i < Laps.size(); i++)
	{
		string name = to_string(i);		// ���������string
		imshow("G" + name, Gauss[i]);
		imshow("L" + name, Laps[i]);
	}

	waitKey();
	return 0;

}