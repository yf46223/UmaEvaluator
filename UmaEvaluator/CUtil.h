#pragma once

#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class CUtil
{
public:
	static cv::Mat ReadPNG(const wstring& sFilePNG);
	static void WritePNG(const cv::Mat& img, const wstring& sFilePNG);
	static string WStringToString(const wstring& ws);
};

