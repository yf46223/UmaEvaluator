
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
	CSkillItem() : iSkill(0), iLv(0), bObtain(false), bSelected(false)
	{
	}

	CSkillItem(int iSkill_, int iLv_) : iSkill(iSkill_), iLv(iLv_), bObtain(false), bSelected(false)
	{
	}

public:
	int iSkill;
	int iLv;
	bool bObtain;
	bool bSelected;
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
	cv::Mat GetDesktopImage();
	cv::Mat GetUmaWindowImage();
	bool MatchImage(const cv::Mat& img, const cv::Mat& img_ref, double crit = 0.995);
	wstring GetExeDir();
	wstring GetImgDir() { return GetExeDir() + L"img\\"; }
	int GetTekisei(const cv::Mat img_ref[8], const cv::Mat& img);
	int GetNumberOCR(const cv::Mat& img);
	void ReadSkillTSV();
	void SaveSkillTSV();
	void ReadSkillLv();
	void ReadUniqLv();
	void ReadStatusPointTSV();
	int GetImageSkillLv(const cv::Mat& img);
	int GetImageUniqLv(const cv::Mat& img);
	int GetImageSkill(const cv::Mat& img);
	vector<pair<cv::Mat, bool> > GetSkillImages(const cv::Mat img_finish);
	CString WS2CS(const wstring& ws);
	CString Int2CS(int n);
	void UpdateSkillList();
	void UpdateStatusPoint();

private:
	vector<CSkill> m_skills;
	vector<cv::Mat> m_skillLv;
	vector<cv::Mat> m_uniqLv;
	vector<int> m_vnStatusPoint;

	vector<CSkillItem> m_vSkills;
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
};
