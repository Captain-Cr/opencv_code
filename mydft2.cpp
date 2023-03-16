#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*
	ͼ����Ҷ�任���Խ�ͼ���ͼ����任��Ƶ�����ھ���ͼ����Ҷ�任֮��Ľ����õ�������ʵ���ֺ���������ͼ����ʵ��ʹ��ʱ���ѽ���ֳ�ʵ��ͼ�������ͼ�񣬻����ø����ķ�ֵ����λ����ʾ�任��������Էֳɷ�ֵͼ�����λͼ��

	���������� void cv::dft( InputArray src, OutputArray dst, int flag = 0, int nonzeroRows = 0);
		�ú����ܹ�������������ݽ�����ɢ����Ҷ�任����һ������������ͼ�����������󣬸ò����������ͱ�����CV_32F����CV_64F�������ǵ�ͨ����ʵ������Ҳ������˫ͨ���ĸ������󡣵ڶ��������Ƕ������������������ɢ����Ҷ�任�Ľ����
	����Ծ�����ʽ��ţ�����ĳߴ������ȡ���ڵ����������������������Ǳ任���Ϳ�ѡ��־����ѡ��־����ִ�����������ʾ�����ĸ�������ʾ���롢����������ʽ��Ĭ��Ϊ0�����ò�����Ϊ0ʱ���ڵ���������δ����DFT_INVERSEʱ���ú���
	����ֻ�������ĵ�һ�������У��ڵ�������������DFT_INVERSEʱ��ֻ�������ĵ�һ����������Ԫ�صķ����С�

									dft()�����б任���Ϳ�ѡ��־
	��ѡ��־				���						����
	DFT_INVERSE				 1				��һά������߶�ά���������任
	DFT_SCALE				 2				���ű�־�����������������Ԫ�ص���ĿN��ͨ����DFT_INVERSE���ʹ��
	DFT_ROWS				 4				�����������ÿһ�н������任������任���ñ�־���Դ�����ά���߸���ά����ɢ�任ʱ������Դ����
	DFT_COMPLEX_OUTPUT		 16				��һά���߶�άʵ������������任���������ͬ�ߴ�ľ��и�������ԳƵĸ�������
	DFT_REAL_OUTPUT			 32				��һά���߶�ά�������������任���������ͬ�ߴ�ľ��и�������ԳƵĸ��������������ľ����Ǿ��и�������Գ��Եĸ���������ô������Ϊʵ������
	DFT_COMPLEX_INPUT		 64				ָ�����������Ǹ���������������˴˱�־�������������������ͨ�������������������������ͨ������ô����Ĭ�����������Ǹ�������

	- ����ò���������DFT_ROWS�������������е��л��е���ʽ����ô������DFT_ROWSʱ���ú����Ծ����ÿһ��ִ���������任��������ִ�ж�ά�任��
	- �������������ʵ���Ҹò���δ����DFT_INVERSE,��ô�ú���ִ������һά���ά�任
	- ����ò�������DFT_COMPLEX_OUTPUT����δ����DFT_INVERSE,��ô������Ϊ�������С��ͬ�ĸ�������
	- ����ò���δ����DFT_COMPLEX_OUTPUT��DFT_INVERSE����ô������������С��ͬ��ʵ������
	- �����������Ǹ��������Ҹò���δ����DFT_INVERSE����DFT_READL_OUTPUT,��ô������������С��ͬ�ĸ�������
	- ������������ʵ������������DFT_INVERSE���������������Ǹ�������������DFT_REAL_OUTPUTʱ����ô�������������ͬ��С��ʵ������
	- ���������DFT_SCALE����ô��ת����������ţ��ñ�־��Ϊ�˱�֤���任֮������任�Ľ����ԭʼ������ͬ



	����˵���� void cv::idft(InputArray src, OutputArray dst, int flag = 0, int nonzeroRows = 0);
		�ú����ܹ�ʵ��һά�������߶�ά����������ɢ����Ҷ�任����任���ú�����������dft()��������DFT_INVERSE��Ч����һ���ģ���idft(src, dst, flags)�൱��dft(src, dst, flag |DFT_INVERSE).


	����Ҷ�任��������ĳЩ�ض����ȵ����������д������Խ��ܼ��������������ߴ�

	����˵���� int cv::getOptimalDFTSize(int vecsize)
		�ú����ܹ�������֪�������ݵ�������ɢ����Ҷ�任�ߴ磬���ųߴ�ʹ2��3��5�Ĺ����������������ʾ��Ҫ���и���Ҷ�任�ľ�������������������

	����˵���� void cv::copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar &value = Scalar())
		�ú����ܹ��ڲ���ͼ��������ŵ�ǰ��������ͼ��ߴ硣�ú�����һ������Ϊ��Ҫ����ߴ��ԭͼ�񡣵ڶ���������������ͼ���������ͺ�ԭͼ����ͬ���������������������ֱ�Ϊԭͼ�����������չ���ص���������������4����������
	����ͼ�������ĳߴ硣�ú������ͼ��ĳߴ�ΪSize(src.clos + left + right,  src.rows + buttom +top)�����������������չ�߽�����ͺ���ֵ����չ�߽�����ͳ���BORDER_CONSTANT����value����Ĭ��ʱ����ʾ��0����µ����ء�

	����˵���� void cv::magnitude(InputArray x, InputArray y, Output magnitude);
		�ú��������������������Ӧλ����������ķ�ֵ��Ҳ���Ǽ������������Ӧλ�õ�ƽ��������һ������Ϊ����һ�����󣬾����е�ÿ��Ԫ�ؿ��Ա�ʾ������x���꣬�ڶ�����������һ�����󣬾�����ÿ��Ԫ�ؿ��Ա�ʾ������y���ꡣ
	����������������ķ�ֵ���󣬼�ƽ�������󣬸þ������һ�������е�������������ͬ�ĳߴ���������͡���Ҫע�⣬�ú��������������CV_32F����CV_64F��

*/


int main(int argc, char* argv[])
{
	// ����һ�����󣬶�����д���չʾ����任�Ĺ�ϵ
	Mat a = (Mat_<float>(5, 5) << 1, 2, 3, 4, 5,
		2, 3, 4, 5, 6,
		3, 4, 5, 6, 7,
		4, 5, 6, 7, 8,
		5, 6, 7, 8, 9);

	Mat b, c, d;
	dft(a, b, DFT_COMPLEX_OUTPUT);		// ���任
	dft(b, c, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);		// ��任��ֻ���ʵ������
	idft(b, d, DFT_SCALE);				// ��任�����a

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	cout << d << endl;

	// ͼ����Ҷ�任
	Mat src = imread("D:\\ͼƬ\\1.jpg");
	if (src.empty())
	{
		cout << "ͼ�����ʧ��" << endl;
		return -1;
	}

	// ת��Ϊ�Ҷ�ͼ
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("src", src);

	// �������ʺϸ���Ҷ�任�ĳߴ�
	int F_width = getOptimalDFTSize(gray.cols);
	int F_height = getOptimalDFTSize(gray.rows);

	// ��ͼ��������
	Mat fillImg;
	int top = (F_height - gray.rows) / 2;		// ������������
	int bottom = F_height - gray.rows - top;
	int left = (F_width - gray.cols) / 2;
	int right = F_width - gray.cols - left;
	copyMakeBorder(gray, fillImg, top, bottom, left, right, BORDER_CONSTANT);
	imshow("fill Img", fillImg);

	// ��������Ҷ�任������
	Mat flo[2], complex;
	flo[0] = Mat_<float>(fillImg);			// ʵ������
	flo[1] = Mat::zeros(fillImg.size(), CV_32F);		// �鲿����
	merge(flo, 2, complex);				// ��ʵ�����鲿��ϳ�һ����

	// ���и���Ҷ�任
	Mat result;
	dft(complex, result);

	// ������ת��Ϊ��ֵ
	Mat resultC[2];
	split(result, resultC);		// ������Ҷ�任���鲿��ʵ���ֿ�
	Mat amplitude;
	magnitude(resultC[0], resultC[1], amplitude);		// �����ֵͼ��ƽ����

	// ʹ�ö�����С����ʽΪ��M1=log(1+M),��֤���е���������0
	amplitude = amplitude + 1;
	log(amplitude, amplitude);		// ����Ȼ����

	// ��ԭͼ��ߴ���ڵ�����ȥ�����ĵط���
	amplitude = amplitude(Rect(top, left, gray.cols, gray.rows));
	normalize(amplitude, amplitude, 0, 1, NORM_MINMAX);		// ��һ��
	imshow("����Ҷ�任�����ֵͼ��", amplitude);	


	// �������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
	int centerX = amplitude.cols / 2;
	int centerY = amplitude.rows / 2;
	// �ֽ��4��С����
	Mat Qlt(amplitude, Rect(0, 0, centerX, centerY));		// ROI��������
	Mat Qrt(amplitude, Rect(centerX, 0, centerX, centerY));	// ����
	Mat Qlb(amplitude, Rect(0, centerY, centerX, centerY));	//����
	Mat Qrb(amplitude, Rect(centerX, centerY, centerX, centerY));//����

	// �������ޣ����Ϻ����½��н���
	Mat med;
	Qlt.copyTo(med);
	Qrb.copyTo(Qlt);
	med.copyTo(Qrb);
	// �������ޣ����º����Ͻ��н���
	Qrt.copyTo(med);
	Qlb.copyTo(Qrt);
	med.copyTo(Qlb);

	imshow("���Ļ���ֵͼ", amplitude);







	waitKey();
	destroyAllWindows();
	return 0;


}