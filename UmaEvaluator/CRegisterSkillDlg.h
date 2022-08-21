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

public:
	bool Setup(CSkill& skill);

private:
	wstring m_sName;
	int  m_nPt;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editSkillName;
	afx_msg void OnBnClickedOk();
	CEdit m_editPt;
};
