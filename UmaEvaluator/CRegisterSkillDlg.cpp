// CRegisterSkillDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "UmaEvaluator.h"
#include "afxdialogex.h"
#include "CRegisterSkillDlg.h"


// CRegisterSkillDlg ダイアログ

IMPLEMENT_DYNAMIC(CRegisterSkillDlg, CDialogEx)

CRegisterSkillDlg::CRegisterSkillDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REGISTER_SKILL, pParent),
    m_nPt(0), m_nEval(0)
{

}

CRegisterSkillDlg::~CRegisterSkillDlg()
{
}

void CRegisterSkillDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SKILL_NAME, m_editSkillName);
    DDX_Control(pDX, IDC_EDIT_PT, m_editPt);
    DDX_Control(pDX, IDC_EDIT_EVAL, m_editEval);
}


BEGIN_MESSAGE_MAP(CRegisterSkillDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CRegisterSkillDlg::OnBnClickedOk)
END_MESSAGE_MAP()

bool CRegisterSkillDlg::Setup(CSkill& skill)
{
    m_sName = L"";
    m_nPt = 0;
    m_nEval = 0;

    cv::imshow("Skill Image", skill.img);

    bool b = (DoModal() == IDOK);

    if (b) {
        skill.sName = m_sName;
        skill.nPt = m_nPt;
        skill.nEval = m_nEval;
    }

    cv::destroyAllWindows();

    return b;
}



// CRegisterSkillDlg メッセージ ハンドラー




void CRegisterSkillDlg::OnBnClickedOk()
{
    {
        CString cs;
        m_editSkillName.GetWindowTextW(cs);
        wstring sName = cs.GetString();

        if (sName == L"") {
            MessageBox(L"スキル名を入力してください。");
            return;
        }

        m_sName = sName;
    }

    {
        CString cs;
        m_editPt.GetWindowTextW(cs);
        wstring sPt = cs.GetString();

        int nPt = 0;
        try {
            nPt = std::stoi(sPt);
        }
        catch (...) {
        }

        if (nPt <= 0) {
            MessageBox(L"スキル取得ポイントの値が不正です。");
            return;
        }
        m_nPt = nPt;
    }

    {
        CString cs;
        m_editEval.GetWindowTextW(cs);
        wstring sEval = cs.GetString();

        int nEval = 0;
        try {
            nEval = std::stoi(sEval);
        }
        catch (...) {
        }

        if (nEval <= 0) {
            MessageBox(L"評価点の値が不正です。");
            return;
        }
        m_nEval = nEval;
    }

    // TODO: ここにコントロール通知ハンドラー コードを追加します。
    CDialogEx::OnOK();
}
