// 功能：读取和保存xml和yaml
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

int main_1(int argc, char* argv[])
{
	system("color F0");			// 修改运行程序背景和文字颜色
	// String Filename = "data.xml";			// 文件名称
	String Filename = "data.yaml";				// 文件名称，可以是已经存在或者没存在，但如果是读则要求是已经存在的文件
	// 以写入的方式打开文件
	FileStorage fwrite(Filename, FileStorage::WRITE);

	// 存入矩阵Mat类型的数据
	Mat mat = Mat::eye(3, 3, CV_8U);
	fwrite.write("mat", mat);				// 用write将数据写入文件
	// 存放浮点型数据，节点名称为x
	float x = 100;
	fwrite << "x" << x;
	// 存放字符串型数据，节点名称为str
	String str = "Learn OpenCV 4";
	fwrite << "str" << str;
	// 存入数组，节点名称为number_array
	fwrite << "number_array" << "[" << 4 << 5 << 6 << "]";		// [4, 5, 6]
	// 存入多node节点数据，主名称为multi_nodes
	fwrite << "multi_nodes" << "{" << "month" << 8 << "day" << 28 << "year" << 2022 << "time" << "[" << 0 << 1 << 2 << 3 << "]" << "}";

	// 关闭文件
	fwrite.release();


	// 以读取的模式打开文件
	FileStorage fread(Filename, FileStorage::READ);
	// 判断文件是否成功打开
	if (!fread.isOpened())
	{
		cout << "打开文件失败！！！" << endl;
		return -1;
	}
	//读取文件的数据
	float xRead;
	fread["x"] >> xRead;		// 从节点读取数据
	cout << "x=" << xRead << endl;

	// 读取字符串数据
	String strRead;
	fread["str"] >> strRead;
	cout << "str=" << strRead << endl;

	// 读取含多个数据的number_array节点,需要FileNode节点类型和迭代器FileNodeIterator读取，
	FileNode fileNode = fread["number_array"];			// 相当于根节点
	cout << "number_array = [";
	// 循环遍历每个数据
	for (FileNodeIterator i = fileNode.begin(); i != fileNode.end(); i++)
	{
		float a;
		*i >> a;
		cout << a << " ";
	}
	cout << "]" << endl;

	// 读取Mat类型数据
	Mat matRead;
	fread["mat"] >> matRead;
	cout << "mat = " << matRead << endl;

	// 读取多个节点的节点数据，不使用FileNodeIterator和FileNode进行读取
	FileNode fileNodel = fread["multi_nodes"];			// 根节点
	int month = (int)fileNodel["month"];
	int day = (int)fileNodel["day"];
	int year = (int)fileNodel["year"];
	cout << "multi_nodes:" << endl
		<< "  month = " << month << " day = " << day << "year = " << year;
	// 然后读取time， time是一个多数据array
	cout << " time = " << "[";
	for (int i = 0; i < 4; i++)
	{
		int a = (int)fileNodel["time"][i];
		cout << a << " ";
	}
	cout << "]" << endl;

	// 关闭文件
	fread.release();
	return 0;




}