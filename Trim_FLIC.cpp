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
	string filename_torsobox = "torsobox.csv";
	string filename_trim_joints = "Trim_joints.csv";
	string Path_dataset = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\FLIC\\images\\";
	string Path_output = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\FLIC\\trim_images\\";
	ifstream ifs1(filename_joints);
	ifstream ifs2(filename_torsobox);
	ofstream wf; //writeing file
	wf.open(filename_trim_joints, ios::out);
	wf << "Trim_joints" << endl;

	string buff_ifs1, buff_ifs2;
	string filepath;
	int data_ifs1[100] = { 0 };
	int data_ifs2[100] = { 0 };
	getline(ifs1, buff_ifs1);
	getline(ifs2, buff_ifs2);

	while (getline(ifs1, buff_ifs1)) {
		getline(ifs2, buff_ifs2);

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

		vector<string> result_ifs2 = split(buff_ifs2, ",");
		for (int k = 0; k < result_ifs2.size(); k++) {
			if (k == 0) continue;
			else{
				if (result_ifs1[k] == "NaN") data_ifs2[k - 1] = NUMBER_NAN;
				else                         data_ifs2[k - 1] = stoi(result_ifs2[k]);
			}
			//printf("data_ifs2[%d] : ", k);
			//if (result_ifs2[k] == "NAN") cout << "NaN" << endl;
			//else cout << result_ifs2[k] << endl;
			//getchar();
		}

		//-------------------------------------

		wf << filepath;
		Mat src_org = imread(Path_dataset + filepath);
		//rectangle(src_org, Point(data_ifs2[0], data_ifs2[1]), Point(data_ifs2[2], data_ifs2[3]),Scalar(255,0,0),3,4);
		int tb_width = abs(data_ifs2[0] - data_ifs2[2]);
		int tb_height = abs(data_ifs2[1] - data_ifs2[3]);

		const double k = 0.90;

		if (data_ifs2[0] - tb_width*k < 0) data_ifs2[0] = 0;
		else data_ifs2[0] -= tb_width*k;
		if (data_ifs2[1] - tb_height*k < 0) data_ifs2[1] = 0;
		else data_ifs2[1] -= tb_height*k;
		if (data_ifs2[2] + tb_width*k > src_org.cols) data_ifs2[2] = src_org.cols;
		else data_ifs2[2] += tb_width*k;
		if (data_ifs2[3] + tb_height*k > src_org.rows) data_ifs2[3] = src_org.rows;
		else data_ifs2[3] += tb_height*k;


		//printf("[torsobox] = [ %d , %d ] , [ %d , %d ]\n", data_ifs2[0], data_ifs2[1], data_ifs2[2], data_ifs2[3]);

		Mat src_roi = src_org(Rect(data_ifs2[0], data_ifs2[1], data_ifs2[2] - data_ifs2[0], data_ifs2[3] - data_ifs2[1]));
		//imshow("src_roi", src_roi);
		//waitKey();
		imwrite(Path_output + filepath, src_roi);

		//cout << "result_ifs1.size() : " << result_ifs1.size();
		//getchar();

		for (int k = 0; k < result_ifs1.size() - 1; k++){
			if (data_ifs1[k] == NUMBER_NAN) wf << ",NaN";
			else if (k % 2 == 0) wf << "," << data_ifs1[k] - data_ifs2[0];
			else                 wf << "," << data_ifs1[k] - data_ifs2[1];
		}
		wf << endl;
		//getchar();
	}

	return 0;
}


