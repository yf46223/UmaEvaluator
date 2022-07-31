#pragma once

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class CSkill
{
public:
	int idx;
	wstring sName;
	cv::Mat img;

public:
	CSkill() : idx(0) {}
};

