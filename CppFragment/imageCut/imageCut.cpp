// imageCut.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <list>
#include <io.h>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

list<string> getImageFromDir(string dir){

	list<string> result;
	struct _finddata_t fileInfo;
	long hFile=0;
	string fullDir;
	cout << "dir" << endl;
	if ((hFile = _findfirst(fullDir.assign(dir).append("\\*.csv").c_str(), &fileInfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileInfo.attrib & _A_SUBDIR))
			{
				cout << fileInfo.name << endl;
			}
			else
			{
				fullDir = fullDir.assign(dir).append("\\").append(fileInfo.name);
				cout << fullDir << endl;
				result.push_back(fullDir);
			}
		} while (_findnext(hFile, &fileInfo) == 0);
		_findclose(hFile);
	}

	//if ((hFile = _findfirst(fullDir.c_str(), &fileInfo)) == -1)
	//{
	//	cout << "no file found!" << endl;
	//	return result;
	//}
	//do{
	//	//cout << fileInfo.name << endl;
	//	string fullpath = dir + "\\" + fileInfo.name;
	//	cout << fullpath << endl;
	//	result.push_back(fullpath);
	//}while(_findnext(hFile, &fileInfo) == 0);

	//_findclose(hFile);
	return result;
}

int read_csv(cv::Mat &csvm, string csv_name, char dlm = ','){
    CvMLData tper;
    tper.set_delimiter(dlm);
    int r = tper.read_csv(csv_name.c_str());    
    if (r != 0)
        return r;
    csvm = cv::Mat(tper.get_values(), true);
    return r;
}

Mat read_csv(const char *filepath, Size img_size, int img_type)
{
	Mat image;
	image.create(img_size, img_type);
	string pixel;

	ifstream file(filepath, ifstream::in);
	if (!file)
		cout << "CSV read fail" << endl;

	int nl = image.rows;
	int nc = image.cols;
	int eolElem = image.cols - 1;
	int elemCount = 0;
	if (image.isContinuous())
	
	{
		nc = nc*nl;
		nl = 1;
	}
	for (int i = 0; i<nl; i++)
	{
		float* data = (float*)image.ptr<ushort>(i);
		for (int j  = 0; j < nc; j++)
		{
			if (elemCount == eolElem){
				getline(file, pixel, '\n');
				data[j] = (float)atof(pixel.c_str());
				elemCount = 0;
			}
			else{
				getline(file, pixel, ',');
				data[j] = (float)atof(pixel.c_str());
				elemCount++;
			}
		}
	}
	return image;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string path = "D:\\data\\infr\\pic\\P32\\tmp";
	list<string> files =  getImageFromDir(path);
	int nFiles = files.size();
	list<string>::iterator iter;

	char i = 0;
	iter = files.begin();
	cv::Mat origin; 
	cout << *iter << endl;
	//origin = read_csv(iter->c_str(), Size(640, 512), CV_16UC1);
	//cout << origin << endl;

	//for (iter = files.begin(); iter != files.end(); iter++, i++){
	//	//cv::Mat src = cv::imread(path + *iter);
	//	///*imshow("src", src);*/
	//	///*waitKey();*/
	//	//cout << *iter<<endl;
	//	//cv::Mat roi = src(Range(0, 512), Range(0, 640)).clone();
	//	//imwrite(path + "_cut//" + *iter, roi);

	//}
	return 0;
}

