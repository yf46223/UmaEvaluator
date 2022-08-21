
// UmaEvaluatorDlg.h : ヘッダー ファイル
//

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>
#include <string>

#include "CRegisterSkillDlg.h"

using namespace std;

// CUmaEvaluatorDlg ダイアログ
class CUmaEvaluatorDlg : public CDialogEx
{
// コンストラクション
public:
	CUmaEvaluatorDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UMAEVALUATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

private:
	cv::Mat GetDesktopImage();
	cv::Mat GetUmaWindowImage();
	bool MatchImage(const cv::Mat& img, const cv::Mat& img_ref, double crit = 0.995);
	wstring GetExeDir();
	wstring GetImgDir() { return GetExeDir() + L"img\\"; }
	int GetTekisei(const cv::Mat img_ref[8], const cv::Mat& img);
	int GetNumberOCR(const cv::Mat& img);
	void ReadSkillCSV();
	void SaveSkillCSV();
	void ReadSkillLv();
	int GetImageLv(const cv::Mat& img);

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnBnClickedButtonSkillRegistration();
	CListBox m_listSkills;
	CComboBox m_comboStar;
	CEdit m_editSpeed;
	CEdit m_editStamina;
	CEdit m_editPower;
	CEdit m_editKonjou;
	CEdit m_editKashikosa;
	CComboBox m_comboTurf;
	CComboBox m_comboDart;
	CComboBox m_comboShort;
	CComboBox m_comboMile;
	CComboBox m_comboMiddle;
	CComboBox m_comboLong;
	CComboBox m_comboNige;
	CComboBox m_comboSenkou;
	CComboBox m_comboSashi;
	CComboBox m_comboOikomi;
	CEdit m_editSkillPt;

private:
	vector<CSkill> m_skills;
	vector<cv::Mat> m_skillLv;
};
