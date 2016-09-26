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
int compare_int(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	string filename_joints = "joints.csv";
	string filename_trim_joints = "Trim_joints.csv";
	string Path_dataset = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\lsp_dataset_original\\images\\";
	string Path_output  = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\lsp_dataset_original\\trim_images\\";

	ofstream wf; //writeing file
	wf.open(filename_trim_joints, ios::out);
	wf << "Trim_joints" << endl;

	ifstream ifs1(filename_joints);
	string buff_ifs1;
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

		const int NUM_joints = 14;
		int data_wid[NUM_joints];
		int data_hei[NUM_joints];
		
		Mat src_org = imread(Path_dataset + filepath);
		int n = 0;
		for (int k = 0; k < 27; k += 2){
			//circle(src_org, cv::Point(data_ifs1[k], data_ifs1[k + 1]), 4, cv::Scalar(0, 255, 0), -1, CV_AA);
			data_wid[n] = data_ifs1[k];
			data_hei[n] = data_ifs1[k + 1];	
			n++;
		}

		qsort(data_wid, NUM_joints, sizeof(int), compare_int);
		qsort(data_hei, NUM_joints, sizeof(int), compare_int);

		const double k = 0.30;

		int tb_width = abs(data_wid[0] - data_wid[NUM_joints - 1]);
		int tb_height = abs(data_hei[1] - data_hei[NUM_joints - 1]);

		if (data_wid[0] - tb_width*k < 0) data_wid[0] = 0;
		else data_wid[0] -= tb_width*k;
		if (data_hei[0] - tb_height*k < 0) data_hei[0] = 0;
		else data_hei[0] -= tb_height*k;
		if (data_wid[NUM_joints - 1] + tb_width*k > src_org.cols) data_wid[NUM_joints - 1] = src_org.cols;
		else data_wid[NUM_joints - 1] += tb_width*k;
		if (data_hei[NUM_joints - 1] + tb_height*k > src_org.rows) data_hei[NUM_joints - 1] = src_org.rows;
		else data_hei[NUM_joints - 1] += tb_height*k;

		Mat src_roi = src_org(Rect(data_wid[0],data_hei[0],data_wid[NUM_joints-1]-data_wid[0],data_hei[NUM_joints-1]-data_hei[0]));
		imwrite(Path_output + filepath, src_roi);

		wf << filepath;
		for (int k = 0; k < result_ifs1.size() - 1; k++){
			if (data_ifs1[k] == NUMBER_NAN) wf << ",NaN";
			else if (k % 2 == 0) wf << "," << data_ifs1[k] - data_wid[0];
			else                 wf << "," << data_ifs1[k] - data_hei[0];
		}
		wf << endl;
	}

	return 0;
}


