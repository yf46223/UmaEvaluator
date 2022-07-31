// CRegisterSkillDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "UmaEvaluator.h"
#include "afxdialogex.h"
#include "CRegisterSkillDlg.h"


// CRegisterSkillDlg ダイアログ

IMPLEMENT_DYNAMIC(CRegisterSkillDlg, CDialogEx)

CRegisterSkillDlg::CRegisterSkillDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REGISTER_SKILL, pParent)
{

}

CRegisterSkillDlg::~CRegisterSkillDlg()
{
}

void CRegisterSkillDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SKILL_NAME, m_editSkillName);
}


BEGIN_MESSAGE_MAP(CRegisterSkillDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CRegisterSkillDlg::OnBnClickedOk)
END_MESSAGE_MAP()

bool CRegisterSkillDlg::Setup(CSkill& skill)
{
    m_sName = L"";

    cv::imshow("Skill Image", skill.img);

    bool b = (DoModal() == IDOK);

    if (b) {
        skill.sName = m_sName;
    }

    cv::destroyAllWindows();

    return b;
}



// CRegisterSkillDlg メッセージ ハンドラー




void CRegisterSkillDlg::OnBnClickedOk()
{
    CString cs;
    m_editSkillName.GetWindowTextW(cs);
    m_sName = cs.GetString();

    // TODO: ここにコントロール通知ハンドラー コードを追加します。
    CDialogEx::OnOK();
}
