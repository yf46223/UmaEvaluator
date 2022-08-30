#pragma once

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

enum SKILL_TYPE {
	SKILL_TYPE_UNKNOWN = -1,
	SKILL_TYPE_ORANGE,
	SKILL_TYPE_BLUE,
	SKILL_TYPE_RED,
	SKILL_TYPE_GREEN,
	SKILL_TYPE_SIZE,
};

const wstring SKILL_TYPE_STR[] = {
	L"",
	L"ûÚ",
	L"ê¬",
	L"ê‘",
	L"óŒ",
};

class CSkill
{
public:
	int idx;
	wstring sName;
	int nPt;
	int nEval;
	SKILL_TYPE type;
	cv::Mat img;

public:
	CSkill() : idx(0), nPt(0), nEval(0), type(SKILL_TYPE_UNKNOWN) {}

	void SetTypeFromStr(const wstring& s) {
		for (int i = 0; i < SKILL_TYPE_SIZE; ++i)
			if (s == SKILL_TYPE_STR[i]) {
				type = SKILL_TYPE(i);
				return;
			}
	}
};

