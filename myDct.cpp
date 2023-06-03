#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

/*
	Description: ��ɢ���ұ任����ɢ����Ҷ�任���ƣ����Ǳ任������ֻʹ��ʵ������Ҫ���ڶ��źź�ͼ�������ѹ�������С��������С������ԣ��źž����任��������Ҫ�����ڽ���ĵ�Ƶ���֡�

	Functional: void cv::dct(InputArray src, OutputArray dst, int flags = 0);
	Parameters: 
			InputArray src:��������ɢ���ұ任�����ݾ������ݱ����Ǹ�����
			OutputArray dst: ��ɢ���ұ任���������������������ͬ�ĳߴ���������ͣ�����Ҳ�����Ǹ�����
			int flags: ת�������ı�־������ѡ��ı�־���京��������ʾ

											dct����������ת�������Ŀ�ѡ��־
	   ��־                          ���                                      ����
	   --                             0                                   ��һά���߶�ά����������任
     DCT_INVERSE                      1                                   ��һά���߶�ά���������任
	 DCT_ROWS                         4                                   ִ����������ÿһ�����任������任���˱�־ʹ�������ͬʱת����������������ڼ��ٿ�����ִ����ά���߸���ά�ȵ�ת��

	 PS���ú�����һά���߶�ά�����ݽ�����������������ɢ���ұ任������ú����ĵ���������Ϊת�������ı�־��ʹ�ù������£�
		-- ���(flags & DCT_INVERSE) == 0, ��ô�ú�����һά���߶�ά���ݽ���������ɢ���ұ任�����򣬽������任��
		-- ���(flags & DCT_ROWS) != 0, ��ô�ú���ִ��ÿ�е�һά�任��
		-- ������϶�����������ô�ú���ִ�ж�ά�任��

	Additionary:Ŀǰdct()����ֻ֧��ż����С�����飬�����ʹ�øú�����������ʱ����Ҫ��������䵽ָ���ĳߴ磬��ѳߴ����ͨ��2 * getOptimalDFT((N+1)/2)����õ���
	

	Functional:  void cv::idct(InputArray src, OutputArray dst, int flags = 0);
	Parameters:
			InputArray src:��������ɢ���ұ任����任�����ݾ��������ǵ�ͨ���ĸ�����
			OutputArray dst:��ɢ���ұ任����任�Ľ��������������������ͬ�ĳߴ���������ͣ�
			flags��ת�������ı�־
	�ú����ܹ�ʵ��һά���߶�ά����������ɢ���ұ任����任���ú�����������dct������������DFT_INVERSEʱЧ��һ�£���idct(src, dst, flags)=dct(src, dst, flags|DFT_INVERSE)
	Additional:dct��������ֻ�ܱ任��ͨ���ľ��������Ҫ�ֱ��3��ͨ��������ɢ���ұ任�������任����������һ��������ͨ���Ĳ�ɫͼ��
*/

int main1345(int argc, char* argv[])
{
	Mat kernel = (Mat_<float>(5, 5) << 1, 2, 3, 4, 5,
		2, 3, 4, 5, 6,
		3, 4, 5, 6, 7,
		4, 5, 6, 7, 8,
		5, 6, 7, 8, 9);
	Mat a, b;
	dct(kernel, a);				// ��ɢ���ұ任
	idct(a, b);					// ��ɢ�����ұ任


	// ��ͼ����д���
	Mat img = imread("D:\\ͼ������ͼƬ\\images\\1.jpg");
	if (img.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// �������ųߴ�
	int width = 2 * getOptimalDFTSize((img.cols + 1) / 2);
	int height = 2 * getOptimalDFTSize((img.rows + 1) / 2);

	// ��䵽���ųߴ�
	int top = 0; 
	int buttom = height - img.rows;
	int left = 0;
	int right = width - img.cols;
	Mat appropriate;				// ���������ͼ��
	copyMakeBorder(img, appropriate, top, buttom, left, right, BORDER_CONSTANT, Scalar(0));

	// ��3��ͨ����Ҫ�ֱ������ɢ���ұ任
	vector<Mat> channels;
	split(img, channels);

	// ��ȡBGR��ɫ�ĸ���ͨ��
	Mat one = channels[0];
	Mat two = channels[1];
	Mat three = channels[2];

	// ������ɢ���ұ任
	Mat oneDCT, twoDCT, threeDCT;
	dct(Mat_<float>(one), oneDCT);
	dct(Mat_<float>(two), twoDCT);
	dct(Mat_<float>(three), threeDCT);

	// ������ϳ�һ��ͼ��
	vector<Mat> channelsDCT;
	channelsDCT.push_back(Mat_<uchar>(oneDCT));
	channelsDCT.push_back(Mat_<uchar>(twoDCT));
	channelsDCT.push_back(Mat_<uchar>(threeDCT));

	// ���ͼ��
	Mat result;
	merge(channelsDCT, result);
	imshow("DCTͼ��", result);
	
	waitKey();
	destroyAllWindows();
	return 0;

}