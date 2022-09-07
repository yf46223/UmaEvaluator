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
	L"橙",
	L"青",
	L"赤",
	L"緑",
};

enum SKILL_TEKISEI {
	SKILL_TEKISEI_NONE,
	SKILL_TEKISEI_TURF,
	SKILL_TEKISEI_DART,
	SKILL_TEKISEI_SHORT,
	SKILL_TEKISEI_MILE,
	SKILL_TEKISEI_MIDDLE,
	SKILL_TEKISEI_LONG,
	SKILL_TEKISEI_NIGE,
	SKILL_TEKISEI_SENKOU,
	SKILL_TEKISEI_SASHI,
	SKILL_TEKISEI_OIKOMI,
	SKILL_TEKISEI_SIZE,
};

const wstring SKILL_TEKISEI_STR[] = {
	L"",
	L"芝",
	L"ダート",
	L"短距離",
	L"マイル",
	L"中距離",
	L"長距離",
	L"逃げ",
	L"先行",
	L"差し",
	L"追込",
};

class CSkill
{
public:
	int idx;
	wstring sName;
	int nPt;
	int nEval;
	SKILL_TYPE type;
	SKILL_TEKISEI tekisei;
	cv::Mat img;
	cv::Mat img_title;
	int iSubSkill;

public:
	CSkill() : idx(0), nPt(0), nEval(0), type(SKILL_TYPE_UNKNOWN), iSubSkill(-1) {}

	void SetTypeFromStr(const wstring& s) {
		for (int i = 0; i < SKILL_TYPE_SIZE; ++i)
			if (s == SKILL_TYPE_STR[i]) {
				type = SKILL_TYPE(i);
				return;
			}
	}

	void SetTekiseiFromStr(const wstring& s) {
		for (int i = 0; i < SKILL_TEKISEI_SIZE; ++i)
			if (s == SKILL_TEKISEI_STR[i]) {
				tekisei = SKILL_TEKISEI(i);
				return;
			}
	}

	wstring GetTekiseiStr() const {
		return SKILL_TEKISEI_STR[tekisei];
	}
};

