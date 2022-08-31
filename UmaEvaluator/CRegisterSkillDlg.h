#pragma once
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include "CSkill.h"

// CRegisterSkillDlg ダイアログ

class CRegisterSkillDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterSkillDlg)

public:
	CRegisterSkillDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CRegisterSkillDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTER_SKILL };
#endif

protected:
	virtual BOOL OnInitDialog();

public:
	int Setup(const cv::Mat& img, const vector<CSkill>& skills);
	void UpdateList();

private:
	int m_idx;
	vector<CSkill> m_skills;
	CBitmap m_bmp;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_listCtrlSkills;
	CStatic m_picCtrlSkillImage;
	CEdit m_editNarrow;
	afx_msg void OnEnChangeEditNarrow();
};
