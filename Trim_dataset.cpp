// Trim_dataset.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#pragma warning(disable:4996)
using namespace std;

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
	string filename = "torsobox.csv";
	ifstream ifs(filename);

	string buff;
	string filepath;
	int data[4];
	getline(ifs, buff);
	while (getline(ifs, buff)) {
		vector<string> result = split(buff, ",");
		for (int k = 0; k < result.size(); k++) {
			if (k == 0) filepath = result[k];
			else data[k - 1] = stoi(result[k]);
		}
		cout << "【" << filepath << "】" << " [" << data[0] << " " << data[1] << "] [" << data[2] << " " << data[3] << "]" << endl;
		getchar();
	}

    return 0;
}


