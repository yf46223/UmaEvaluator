#pragma once

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class CSkill
{
public:
	int idx;
	int nPt;
	int nEval;
	wstring sName;
	cv::Mat img;

public:
	CSkill() : idx(0), nPt(0), nEval(0) {}
};

