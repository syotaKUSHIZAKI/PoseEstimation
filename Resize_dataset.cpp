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
	//const
	int RESIZE_WID = 128;
	int RESIZE_HEI = 128;

	//FLIC
	//string filename_trim_joints = "Trim_joints_FLIC.csv";
	//string filename_resize_joints = "Resize_joints_FLIC.csv";
	//string Path_dataset = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\FLIC\\Trim_images\\";
	//string Path_output = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\FLIC\\Resize_images\\";

	//lsp
	string filename_trim_joints = "Trim_joints_lsp.csv";
	string filename_resize_joints = "Resize_joints_lsp.csv";
	string Path_dataset = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\lsp_dataset_original\\Trim_images\\";
	string Path_output = "C:\\Users\\Shun\\Pictures\\DeepLearning\\dataset\\lsp_dataset_original\\Resize_images\\";

	ofstream wf; //writeing file
	wf.open(filename_resize_joints, ios::out);
	wf << "Resize_joints" << endl;

	ifstream ifs1(filename_trim_joints);
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
		//imshow(filepath, src_org);
		double corr_wid = (double)RESIZE_WID / (double)src_org.cols;
		double corr_hei = (double)RESIZE_HEI / (double)src_org.rows;
		//cout << "corr_wid : "<< corr_wid << endl;
		//cout << "corr_hei : "<< corr_hei << endl;
		Mat src_res;
		resize(src_org, src_res, cv::Size(RESIZE_WID,RESIZE_HEI));
		imwrite(Path_output + filepath, src_res);

		int n = 0;
		for (int k = 0; k < 27; k += 2){
			//circle(src_res, cv::Point((int)data_ifs1[k]*corr_wid, (int)data_ifs1[k + 1]*corr_hei), 2, cv::Scalar(0, 255, 0), -1, CV_AA);
			data_wid[n] = (int)data_ifs1[k]*corr_wid;
			data_hei[n] = (int)data_ifs1[k + 1]*corr_hei;
			n++;
		}

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


