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
    m_idx(-1)
{
}

CRegisterSkillDlg::~CRegisterSkillDlg()
{
}

void CRegisterSkillDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SKILLS, m_listCtrlSkills);
}

// CUmaEvaluatorDlg メッセージ ハンドラー
BOOL CRegisterSkillDlg::OnInitDialog()
{
    BOOL b = CDialogEx::OnInitDialog();

    m_listCtrlSkills.InsertColumn(0, L"スキル名", LVCFMT_LEFT, 300);
    m_listCtrlSkills.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    UpdateList();

    return b;
}



BEGIN_MESSAGE_MAP(CRegisterSkillDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CRegisterSkillDlg::OnBnClickedOk)
END_MESSAGE_MAP()

int CRegisterSkillDlg::Setup(const cv::Mat& img, const vector<CSkill>& skills)
{
    m_idx = -1;
    m_skills = skills;

    cv::imshow("Skill Image", img);

    int idx = (DoModal() == IDOK) ? m_idx : -1;

    cv::destroyAllWindows();

    return idx;
}

// CRegisterSkillDlg メッセージ ハンドラー

void CRegisterSkillDlg::OnBnClickedOk()
{
    CString cs;
    m_listCtrlSkills.GetWindowTextW(cs);

    POSITION pos = m_listCtrlSkills.GetFirstSelectedItemPosition();
    if (!pos) {
        MessageBox(L"スキル名を選択してください。");
        return;
    }

    int nItem = m_listCtrlSkills.GetNextSelectedItem(pos);
    cs = m_listCtrlSkills.GetItemText(nItem, 0);
    wstring ws(cs);
    for (int i = 0; i < m_skills.size(); ++i) {
        if (ws == m_skills[i].sName) {
            m_idx = m_skills[i].idx;
            break;
        }
    }

    // TODO: ここにコントロール通知ハンドラー コードを追加します。
    CDialogEx::OnOK();
}

static CString WS2CS(const wstring& ws)
{
    CString cs;
    cs.Format(_T("%s"), ws.c_str());
    return cs;
}

void CRegisterSkillDlg::UpdateList()
{
    m_listCtrlSkills.DeleteAllItems();
    for (int i = 0; i < m_skills.size(); ++i) {
        m_listCtrlSkills.InsertItem(i, WS2CS(m_skills[i].sName));
    }
}
