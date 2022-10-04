#include "pch.h"
#include "CUtil.h"

#include <fstream>

cv::Mat CUtil::ReadPNG(const wstring& sFilePNG)
{
	string s = WStringToString(sFilePNG);
	return cv::imread(s.c_str());
}

void CUtil::WritePNG(const cv::Mat& img, const wstring& sFilePNG)
{
	string s = WStringToString(sFilePNG);
	cv::imwrite(s.c_str(), img);
}

string CUtil::WStringToString(const wstring& ws)
{
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, ws.c_str(), -1, (char*)NULL, 0, NULL, NULL);
	CHAR* cpMultiByte = new CHAR[iBufferSize];
	WideCharToMultiByte(CP_OEMCP, 0, ws.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);
	string s(cpMultiByte, cpMultiByte + iBufferSize - 1);
	delete[] cpMultiByte;
	return s;
}

