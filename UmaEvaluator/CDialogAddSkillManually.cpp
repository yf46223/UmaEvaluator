// CDialogAddSkillManually.cpp : 実装ファイル
//

#include "pch.h"
#include "UmaEvaluator.h"
#include "afxdialogex.h"
#include "CDialogAddSkillManually.h"


// CDialogAddSkillManually ダイアログ

IMPLEMENT_DYNAMIC(CDialogAddSkillManually, CDialogEx)

CDialogAddSkillManually::CDialogAddSkillManually(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_SKILL_MANUALLY, pParent)
{

}

CDialogAddSkillManually::~CDialogAddSkillManually()
{
}

void CDialogAddSkillManually::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_NARROW, m_editNarrow);
    DDX_Control(pDX, IDC_LIST_SKILLS, m_listCtrlSkills);
    DDX_Control(pDX, IDC_COMBO_HINT_LEVEL, m_comboHintLv);
}


BEGIN_MESSAGE_MAP(CDialogAddSkillManually, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDialogAddSkillManually::OnBnClickedOk)
    ON_EN_CHANGE(IDC_EDIT_NARROW, &CDialogAddSkillManually::OnEnChangeEditNarrow)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_SKILLS, &CDialogAddSkillManually::OnNMDblclkListSkills)
END_MESSAGE_MAP()


// CDialogAddSkillManually メッセージ ハンドラー

BOOL CDialogAddSkillManually::OnInitDialog()
{
    BOOL b = CDialogEx::OnInitDialog();

    m_listCtrlSkills.InsertColumn(0, L"スキル名", LVCFMT_LEFT, 300);
    m_listCtrlSkills.SetExtendedStyle(LVS_EX_FULLROWSELECT);

    UpdateList();

    return b;
}

bool CDialogAddSkillManually::Setup(const vector<CSkill>& skills, int& iSkill, int& nHintLv)
{
    iSkill = -1;
    nHintLv = -1;

    m_iSkill = -1;
    m_nHintLv = -1;
    m_skills = skills;

    if (DoModal() != IDOK)
        return false;

    iSkill = m_iSkill;
    nHintLv = m_nHintLv;

    return true;
}

static CString WS2CS(const wstring& ws)
{
    CString cs;
    cs.Format(_T("%s"), ws.c_str());
    return cs;
}

void CDialogAddSkillManually::UpdateList()
{
    CString cs;
    m_editNarrow.GetWindowTextW(cs);
    wstring ws(cs);
    bool bNarrow = (ws != L"");

    m_listCtrlSkills.DeleteAllItems();
    for (int i = 0; i < m_skills.size(); ++i) {
        if (bNarrow) {
            if (m_skills[i].sName.find(ws) == wstring::npos)
                continue;
        }
        m_listCtrlSkills.InsertItem(i, WS2CS(m_skills[i].sName));
    }
}

void CDialogAddSkillManually::OnBnClickedOk()
{
    CString cs;
    m_listCtrlSkills.GetWindowTextW(cs);

    POSITION pos = m_listCtrlSkills.GetFirstSelectedItemPosition();
    if (!pos) {
        MessageBox(L"スキル名を選択してください。");
        return;
    }

    if (m_comboHintLv.GetCurSel() < 0) {
        MessageBox(L"ヒントレベルを選択してください。");
        return;
    }

    int nItem = m_listCtrlSkills.GetNextSelectedItem(pos);
    cs = m_listCtrlSkills.GetItemText(nItem, 0);
    wstring ws(cs);
    for (int i = 0; i < m_skills.size(); ++i) {
        if (ws == m_skills[i].sName) {
            m_iSkill = i;
            break;
        }
    }

    m_nHintLv = m_comboHintLv.GetCurSel();

    CDialogEx::OnOK();
}


void CDialogAddSkillManually::OnEnChangeEditNarrow()
{
    UpdateList();
}


void CDialogAddSkillManually::OnNMDblclkListSkills(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    int nItem = pNMItemActivate->iItem;

    if (nItem < 0) {
        *pResult = 0;
        return;
    }

    if (m_comboHintLv.GetCurSel() < 0) {
        MessageBox(L"ヒントレベルを選択してください。");
        return;
    }

    CString cs = m_listCtrlSkills.GetItemText(nItem, 0);
    wstring ws(cs);
    for (int i = 0; i < m_skills.size(); ++i) {
        if (ws == m_skills[i].sName) {
            m_iSkill = i;
            break;
        }
    }

    *pResult = 0;

    EndDialog(IDOK);
}
