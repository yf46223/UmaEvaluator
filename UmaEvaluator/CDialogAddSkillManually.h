#pragma once
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
#include "CSkill.h"

// CDialogAddSkillManually ダイアログ

class CDialogAddSkillManually : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAddSkillManually)

public:
	CDialogAddSkillManually(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CDialogAddSkillManually();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SKILL_MANUALLY };
#endif

protected:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

public:
	bool Setup(const vector<CSkill>& skills, int& iSkill, int& nHintLv);
	void UpdateList();

private:
	int m_iSkill;
	int m_nHintLv;
	vector<CSkill> m_skills;
public:
	afx_msg void OnBnClickedOk();
	CEdit m_editNarrow;
	CListCtrl m_listCtrlSkills;
	afx_msg void OnEnChangeEditNarrow();
	CComboBox m_comboHintLv;
	afx_msg void OnNMDblclkListSkills(NMHDR* pNMHDR, LRESULT* pResult);
};
