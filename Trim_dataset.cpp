// Trim_dataset.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <opencv_lib.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

#pragma warning(disable:4996)
using namespace std;
using namespace cv;

std::vector<std::string> split(std::string str, std::string delim) {
	std::vector<std::string> items;
	std::size_t dlm_idx;
	if (str.npos == (dlm_idx = str.find_first_of(delim))) {
		items.push_back(str.substr(0, dlm_idx));
	}
	while (str.npos != (dlm_idx = str.find_first_of(delim))) {
		if (str.npos == str.find_first_not_of(delim)) {
			break;
		}
		items.push_back(str.substr(0, dlm_idx));
		dlm_idx++;
		str = str.erase(0, dlm_idx);
		if (str.npos == str.find_first_of(delim) && "" != str) {
			items.push_back(str);
			break;
		}
	}
	return items;
}

int main()
{
	//string filename = "torsobox.csv";
	string filename = "joints.csv";
	string Path_dataset = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\FLIC\\images\\";
	string Path_output = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\FLIC\\trim_images\\";
	ifstream ifs(filename);

	string buff;
	string filepath;
	int data[100] = {0};
	getline(ifs, buff);
	while (getline(ifs, buff)) {

		//------------ load csv ---------------
		vector<string> result = split(buff, ",");
		for (int k = 0; k < result.size(); k++) {
			if (k == 0) filepath = result[k];
			else data[k - 1] = stoi(result[k]);
			printf("data[%d] : ", k);
			isnan
			if (result[k])) cout << "NaN" << endl;
			else cout <<  result[k] << endl;
			getchar();
		}
		//cout << "【" << filepath << "】" << " [" << data[0] << " " << data[1] << "] [" << data[2] << " " << data[3] << "]" << endl;

		//-------------------------------------

		Mat src_org = imread(Path_dataset + filepath);
		//rectangle(src_org, Point(data[0], data[1]), Point(data[2], data[3]),Scalar(255,0,0),3,4);
		int tb_width = abs(data[0] - data[2]);
		int tb_height = abs(data[1] - data[3]);

		const double k = 0.80;

		if (data[0] - tb_width*k < 0) data[0] = 0;
		else data[0] -= tb_width*k;
		if (data[1] - tb_height*k < 0) data[1] = 0;
		else data[1] -= tb_height*k;
		if (data[2] + tb_width*k > src_org.cols) data[2] = src_org.cols;
		else data[2] += tb_width*k;
		if (data[3] + tb_height*k > src_org.rows) data[3] = src_org.rows;
		else data[3] += tb_height*k;

		//printf("[torsobox] = [ %d , %d ] , [ %d , %d ]\n", data[0], data[1], data[2], data[3]);

		Mat src_roi  = src_org( Rect(data[0], data[1], data[2]-data[0], data[3]-data[1]));
		imwrite(Path_output + filepath, src_roi);
	}

	return 0;
}


