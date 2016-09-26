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

#define NUMBER_NAN 114514

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
	string filename_joints = "joints.csv";
	string filename_trim_joints = "Trim_joints.csv";
	string Path_dataset = "C:\\Users\\Shun\\Pictures\\DeepLearning\dataset\\lsp_dataset_original\\images\\";

	ifstream ifs1(filename_joints);
	string buff_ifs1, buff_ifs2;
	string filepath;
	int data_ifs1[100] = { 0 };
	getline(ifs1, buff_ifs1);

	while (getline(ifs1, buff_ifs1)) {

		//------------ load csv ---------------
		vector<string> result_ifs1 = split(buff_ifs1, ",");
		for (int k = 0; k < result_ifs1.size(); k++) {
			if (k == 0) filepath = result_ifs1[k];
			else{
				if (result_ifs1[k] == "NaN") data_ifs1[k - 1] = NUMBER_NAN;
				else                         data_ifs1[k - 1] = stoi(result_ifs1[k]);
			}
			//printf("data_ifs1[%d] : ", k);
			//if (result_ifs1[k] == "NAN") cout << "NaN" << endl;
			//else cout <<  result_ifs1[k] << endl;
			//getchar();
		}
		//cout << "【" << filepath << "】" << " [" << data_ifs1[0] << " " << data_ifs1[1] << "] [" << data_ifs1[2] << " " << data_ifs1[3] << "]" << endl;

		//-------------------------------------

	}

	return 0;
}


