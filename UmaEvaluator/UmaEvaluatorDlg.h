
// UmaEvaluatorDlg.h : ヘッダー ファイル
//

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>
#include <string>

#include "CRegisterSkillDlg.h"

using namespace std;

struct CSkillItem
{
	CSkillItem() : iSkill(0), iLv(0), bObtain(false), bSelected(false), bHidden(false)
	{
	}

	CSkillItem(int iSkill_, int iLv_) : iSkill(iSkill_), iLv(iLv_), 
		bObtain(false), bSelected(false), bHidden(false)
	{
	}

public:
	int iSkill;
	int iLv;
	bool bObtain;
	bool bSelected;
	bool bHidden;
};

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
	cv::Mat GetDesktopImage() const;
	cv::Mat GetUmaWindowImage() const;
	bool MatchImage(const cv::Mat& img, const cv::Mat& img_ref, double crit = 0.995) const;
	wstring GetExeDir() const;
	wstring GetImgDir() const { return GetExeDir() + L"img\\"; }
	int GetTekisei(const cv::Mat& img) const;
	int GetNumberOCR(const cv::Mat& img) const;
	void ReadSkillTSV();
	void ReadSkillLv();
	void ReadUniqLv();
	void ReadStatusPointTSV();
	int GetImageSkillLv(const cv::Mat& img) const;
	int GetImageUniqLv(const cv::Mat& img) const;
	int GetImageSkill(const cv::Mat& img) const;
	vector<pair<cv::Mat, bool> > GetSkillImages(const cv::Mat img_finish) const;
	CString WS2CS(const wstring& ws) const;
	CString Int2CS(int n) const;
	void UpdateSkillList();
	void UpdateEval();
	int GetSkillObtainPt(const CSkillItem& skillItem) const;
	int GetStatusUniqEval() const;
	int GetSkillEval() const;
	wstring GetRankFromEval(int nEval) const;
	int GetEvalOfSkill(const CSkill& skill) const;
	void Detect();
	void HideSkillItems();
	int SelectMaxEval(int nPt, const vector<int>& vnPt, const vector<int>& vnEval, const vector<int>& viDepend, vector<int>& viSelect);

private:
	vector<CSkill> m_skills;
	vector<cv::Mat> m_skillLv;
	vector<cv::Mat> m_uniqLv;
	vector<int> m_vnStatusPoint;
	UINT_PTR m_timerID;

	vector<CSkillItem> m_vSkillItems;
	bool m_bOnUpdateSkillList;

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
	CListCtrl m_listCtrlSkillObtain;
	CListCtrl m_listCtrlSkillCandidate;
	afx_msg void OnLvnItemchangedListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnKeydownListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonToObtain();
	afx_msg void OnLvnItemchangedListCtrlSkillObtain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonToCandidate();
	afx_msg void OnEnChangeEditSpeed();
	afx_msg void OnEnChangeEditStamina();
	afx_msg void OnEnChangeEditPower();
	afx_msg void OnEnChangeEditKonjou();
	afx_msg void OnEnChangeEditKashikosa();
	CStatic m_stStatusPoint;
	afx_msg void OnCbnSelchangeComboStar();
	afx_msg void OnCbnSelchangeComboUniqueSkillLevel();
	CComboBox m_comboUniqueSkillLv;
	CStatic m_stSkillEval;
	CStatic m_stTotalEval;
	CStatic m_stSkillPtUsed;
	CStatic m_stSkillPtRemain;
	CButton m_checkKiremono;
	afx_msg void OnBnClickedCheckKiremono();
	CButton m_buttonDetect;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_checkTurf;
	CButton m_checkDart;
	CButton m_checkShort;
	CButton m_checkMile;
	CButton m_checkMiddle;
	CButton m_checkLong;
	CButton m_checkNige;
	CButton m_checkSenkou;
	CButton m_checkSashi;
	CButton m_checkOikomi;
	afx_msg void OnBnClickedCheckTurf();
	afx_msg void OnBnClickedCheckDart();
	afx_msg void OnBnClickedCheckShort();
	afx_msg void OnBnClickedCheckMile();
	afx_msg void OnBnClickedCheckMiddle();
	afx_msg void OnBnClickedCheckLong();
	afx_msg void OnBnClickedCheckNige();
	afx_msg void OnBnClickedCheckSenkou();
	afx_msg void OnBnClickedCheckSashi();
	afx_msg void OnBnClickedCheckOikomi();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonUncheckUnderB();
	afx_msg void OnCustomdrawListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawListCtrlSkillObtain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonMaximizeEval();
	afx_msg void OnLvnHotTrackListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult);
	CStatic m_picCtrlSkillImageHover;
};
