
// UmaEvaluatorDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "UmaEvaluator.h"
#include "UmaEvaluatorDlg.h"
#include "afxdialogex.h"
#include <winuser.h>
#include <fstream>
#include "CDialogAddSkillManually.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

const int MAX_STATUS_POINT = 2000;

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUmaEvaluatorDlg ダイアログ



CUmaEvaluatorDlg::CUmaEvaluatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UMAEVALUATOR_DIALOG, pParent), m_bOnUpdateSkillList(false), m_timerID(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUmaEvaluatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STAR, m_comboStar);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_editSpeed);
	DDX_Control(pDX, IDC_EDIT_STAMINA, m_editStamina);
	DDX_Control(pDX, IDC_EDIT_POWER, m_editPower);
	DDX_Control(pDX, IDC_EDIT_KONJOU, m_editKonjou);
	DDX_Control(pDX, IDC_EDIT_KASHIKOSA, m_editKashikosa);
	DDX_Control(pDX, IDC_COMBO_TURF, m_comboTurf);
	DDX_Control(pDX, IDC_COMBO_DART, m_comboDart);
	DDX_Control(pDX, IDC_COMBO_SHORT, m_comboShort);
	DDX_Control(pDX, IDC_COMBO_MILE, m_comboMile);
	DDX_Control(pDX, IDC_COMBO_MIDDLE, m_comboMiddle);
	DDX_Control(pDX, IDC_COMBO_LONG, m_comboLong);
	DDX_Control(pDX, IDC_COMBO_NIGE, m_comboNige);
	DDX_Control(pDX, IDC_COMBO_SENKOU, m_comboSenkou);
	DDX_Control(pDX, IDC_COMBO_SASHI, m_comboSashi);
	DDX_Control(pDX, IDC_COMBO_OIKOMI, m_comboOikomi);
	DDX_Control(pDX, IDC_EDIT_SKILL_PT, m_editSkillPt);
	DDX_Control(pDX, IDC_LIST_CTRL_SKILL_OBTAIN, m_listCtrlSkillObtain);
	DDX_Control(pDX, IDC_LIST_CTRL_SKILL_CANDIDATE, m_listCtrlSkillCandidate);
	DDX_Control(pDX, IDC_STATIC_STATUS_EVAL, m_stStatusPoint);
	DDX_Control(pDX, IDC_COMBO_UNIQUE_SKILL_LEVEL, m_comboUniqueSkillLv);
	DDX_Control(pDX, IDC_STATIC_SKILL_EVAL, m_stSkillEval);
	DDX_Control(pDX, IDC_STATIC_TOTAL_EVAL, m_stTotalEval);
	DDX_Control(pDX, IDC_STATIC_SKILL_PT_USED, m_stSkillPtUsed);
	DDX_Control(pDX, IDC_STATIC_SKILL_PT_REMAIN, m_stSkillPtRemain);
	DDX_Control(pDX, IDC_CHECK_KIREMONO, m_checkKiremono);
	DDX_Control(pDX, IDC_BUTTON_DETECT, m_buttonDetect);
	DDX_Control(pDX, IDC_CHECK_DART, m_checkDart);
	DDX_Control(pDX, IDC_CHECK_SHORT, m_checkShort);
	DDX_Control(pDX, IDC_CHECK_MILE, m_checkMile);
	DDX_Control(pDX, IDC_CHECK_MIDDLE, m_checkMiddle);
	DDX_Control(pDX, IDC_CHECK_LONG, m_checkLong);
	DDX_Control(pDX, IDC_CHECK_NIGE, m_checkNige);
	DDX_Control(pDX, IDC_CHECK_SENKOU, m_checkSenkou);
	DDX_Control(pDX, IDC_CHECK_SASHI, m_checkSashi);
	DDX_Control(pDX, IDC_CHECK_OIKOMI, m_checkOikomi);
	DDX_Control(pDX, IDC_STATIC_SKILL_IMAGE_HOVER, m_picCtrlSkillImageHover);
	DDX_Control(pDX, IDC_LIST_CTRL_SKILL_ACQUIRED, m_listCtrlSkillAcquired);
	DDX_Control(pDX, IDC_STATIC_SKILL_EVAL_AQUIRED, m_stSkillAcquiredEval);
}

BEGIN_MESSAGE_MAP(CUmaEvaluatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CUmaEvaluatorDlg::OnBnClickedButtonDetect)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_REGISTRATION, &CUmaEvaluatorDlg::OnBnClickedButtonSkillRegistration)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRL_SKILL_CANDIDATE, &CUmaEvaluatorDlg::OnLvnItemchangedListCtrlSkillCandidate)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CTRL_SKILL_CANDIDATE, &CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillCandidate)
	ON_BN_CLICKED(IDC_BUTTON_TO_OBTAIN, &CUmaEvaluatorDlg::OnBnClickedButtonToObtain)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRL_SKILL_OBTAIN, &CUmaEvaluatorDlg::OnLvnItemchangedListCtrlSkillObtain)
	ON_BN_CLICKED(IDC_BUTTON_TO_CANDIDATE, &CUmaEvaluatorDlg::OnBnClickedButtonToCandidate)
	ON_EN_CHANGE(IDC_EDIT_SPEED, &CUmaEvaluatorDlg::OnEnChangeEditSpeed)
	ON_EN_CHANGE(IDC_EDIT_STAMINA, &CUmaEvaluatorDlg::OnEnChangeEditStamina)
	ON_EN_CHANGE(IDC_EDIT_POWER, &CUmaEvaluatorDlg::OnEnChangeEditPower)
	ON_EN_CHANGE(IDC_EDIT_KONJOU, &CUmaEvaluatorDlg::OnEnChangeEditKonjou)
	ON_EN_CHANGE(IDC_EDIT_KASHIKOSA, &CUmaEvaluatorDlg::OnEnChangeEditKashikosa)
	ON_CBN_SELCHANGE(IDC_COMBO_STAR, &CUmaEvaluatorDlg::OnCbnSelchangeComboStar)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIQUE_SKILL_LEVEL, &CUmaEvaluatorDlg::OnCbnSelchangeComboUniqueSkillLevel)
	ON_BN_CLICKED(IDC_CHECK_KIREMONO, &CUmaEvaluatorDlg::OnBnClickedCheckKiremono)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_DART, &CUmaEvaluatorDlg::OnBnClickedCheckDart)
	ON_BN_CLICKED(IDC_CHECK_SHORT, &CUmaEvaluatorDlg::OnBnClickedCheckShort)
	ON_BN_CLICKED(IDC_CHECK_MILE, &CUmaEvaluatorDlg::OnBnClickedCheckMile)
	ON_BN_CLICKED(IDC_CHECK_MIDDLE, &CUmaEvaluatorDlg::OnBnClickedCheckMiddle)
	ON_BN_CLICKED(IDC_CHECK_LONG, &CUmaEvaluatorDlg::OnBnClickedCheckLong)
	ON_BN_CLICKED(IDC_CHECK_NIGE, &CUmaEvaluatorDlg::OnBnClickedCheckNige)
	ON_BN_CLICKED(IDC_CHECK_SENKOU, &CUmaEvaluatorDlg::OnBnClickedCheckSenkou)
	ON_BN_CLICKED(IDC_CHECK_SASHI, &CUmaEvaluatorDlg::OnBnClickedCheckSashi)
	ON_BN_CLICKED(IDC_CHECK_OIKOMI, &CUmaEvaluatorDlg::OnBnClickedCheckOikomi)
	ON_BN_CLICKED(IDC_BUTTON_UNCHECK_UNDER_B, &CUmaEvaluatorDlg::OnBnClickedButtonUncheckUnderB)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CTRL_SKILL_CANDIDATE, &CUmaEvaluatorDlg::OnCustomdrawListCtrlSkillCandidate)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CTRL_SKILL_OBTAIN, &CUmaEvaluatorDlg::OnCustomdrawListCtrlSkillObtain)
	ON_BN_CLICKED(IDC_BUTTON_MAXIMIZE_EVAL, &CUmaEvaluatorDlg::OnBnClickedButtonMaximizeEval)
	ON_NOTIFY(LVN_HOTTRACK, IDC_LIST_CTRL_SKILL_CANDIDATE, &CUmaEvaluatorDlg::OnLvnHotTrackListCtrlSkillCandidate)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_REGISTRATION_ACQUIRED, &CUmaEvaluatorDlg::OnBnClickedButtonSkillRegistrationAcquired)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CTRL_SKILL_ACQUIRED, &CUmaEvaluatorDlg::OnNMCustomdrawListCtrlSkillAcquired)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CTRL_SKILL_ACQUIRED, &CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillAcquired)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CTRL_SKILL_ACQUIRED, &CUmaEvaluatorDlg::OnLvnItemchangedListCtrlSkillAcquired)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CTRL_SKILL_OBTAIN, &CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillObtain)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_SKILLS, &CUmaEvaluatorDlg::OnBnClickedButtonClearSkills)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SKILL_MANUALLY, &CUmaEvaluatorDlg::OnBnClickedButtonAddSkillManually)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SKILL_ACQUIRED_MANUALLY, &CUmaEvaluatorDlg::OnBnClickedButtonAddSkillAcquiredManually)
END_MESSAGE_MAP()


// CUmaEvaluatorDlg メッセージ ハンドラー
BOOL CUmaEvaluatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	m_listCtrlSkillCandidate.InsertColumn(0, L"適性"    , LVCFMT_LEFT, 40);
	m_listCtrlSkillCandidate.InsertColumn(1, L"スキル名", LVCFMT_LEFT, 100);
	m_listCtrlSkillCandidate.InsertColumn(2, L"Lv"      , LVCFMT_LEFT, 30);
	m_listCtrlSkillCandidate.InsertColumn(3, L"取得Pt"  , LVCFMT_LEFT, 50);
	m_listCtrlSkillCandidate.InsertColumn(4, L"評価点"  , LVCFMT_LEFT, 50);
	m_listCtrlSkillCandidate.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_listCtrlSkillObtain.InsertColumn(0, L"適性"    , LVCFMT_LEFT, 40);
	m_listCtrlSkillObtain.InsertColumn(1, L"スキル名", LVCFMT_LEFT, 100);
	m_listCtrlSkillObtain.InsertColumn(2, L"Lv"      , LVCFMT_LEFT, 30);
	m_listCtrlSkillObtain.InsertColumn(3, L"取得Pt"  , LVCFMT_LEFT, 50);
	m_listCtrlSkillObtain.InsertColumn(4, L"評価点"  , LVCFMT_LEFT, 50);
	m_listCtrlSkillObtain.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_listCtrlSkillAcquired.InsertColumn(0, L"適性", LVCFMT_LEFT, 40);
	m_listCtrlSkillAcquired.InsertColumn(1, L"スキル名", LVCFMT_LEFT, 100);
	m_listCtrlSkillAcquired.InsertColumn(2, L"評価点", LVCFMT_LEFT, 50);
	m_listCtrlSkillAcquired.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_checkDart.SetCheck(BST_CHECKED);
	m_checkShort.SetCheck(BST_CHECKED);
	m_checkMile.SetCheck(BST_CHECKED);
	m_checkMiddle.SetCheck(BST_CHECKED);
	m_checkLong.SetCheck(BST_CHECKED);
	m_checkNige.SetCheck(BST_CHECKED);
	m_checkSenkou.SetCheck(BST_CHECKED);
	m_checkSashi.SetCheck(BST_CHECKED);
	m_checkOikomi.SetCheck(BST_CHECKED);

	ReadSkillTSV();
	ReadSkillLv();
	ReadStatusPointTSV();
	ReadUniqLv();
	
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CUmaEvaluatorDlg::ReadSkillTSV()
{
	// スキル情報の読み込み
	wstring sDataDir = GetDataDir();
	wstring sSkillDir = sDataDir + L"skills\\";
	wstring sFileTSV = sDataDir + L"skills.txt";
	wifstream ifs(sFileTSV);

	auto Loc = locale("Japanese");
	auto L = ifs.imbue(Loc);

	m_skills.clear();
	vector<wstring> vsSubSkill;

	wstring line;
	while (getline(ifs, line)) {

		CSkill skill;

		wstringstream iss(line);
		wstring s;
		getline(iss, s, L'\t'); skill.idx = stoi(s);
		getline(iss, s, L'\t'); skill.nPt = stoi(s);
		getline(iss, s, L'\t'); skill.nEval = stoi(s);
		getline(iss, s, L'\t'); skill.SetTypeFromStr(s);
		getline(iss, s, L'\t'); skill.SetTekiseiFromStr(s);
		getline(iss, s, L'\t'); skill.sName = s;
		getline(iss, s, L'\t');
		if (s == L"") {
			if (skill.sName.substr(skill.sName.length() - 1) == L"◎") {
				s = skill.sName.substr(0, skill.sName.length() - 1) + L"◯";
			}
		}
		vsSubSkill.push_back(s);

		{
			wstring sFilePNG = sSkillDir + to_wstring(skill.idx) + L".png";
			skill.img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
		}

		{
			wstring sFilePNG = sSkillDir + L"a" + to_wstring(skill.idx) + L".png";
			skill.img_acquired = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
		}

		m_skills.push_back(skill);
	}

	for (int i = 0; i < vsSubSkill.size(); ++i) {
		if (vsSubSkill[i] == L"")
			continue;
		for (int j = 0; j < m_skills.size(); ++j) {
			if (m_skills[j].sName == vsSubSkill[i]) {
				m_skills[i].iSubSkill = j;
				break;
			}
		}
	}

	for (int i = 0; i < m_skills.size(); ++i) {
		if (!m_skills[i].img.empty()) {
			cv::Mat img_title(m_skills[i].img, cv::Rect(60, 4, 120, 17));
			cv::Mat img_title_resize;
			cv::resize(img_title, img_title_resize, cv::Size(240, 34));
			m_skills[i].img_title = img_title_resize;
		}
		if (!m_skills[i].img_acquired.empty()) {
			cv::Mat img_title(m_skills[i].img_acquired, cv::Rect(60, 4, 120, 17));
			cv::Mat img_title_resize;
			cv::resize(img_title, img_title_resize, cv::Size(240, 34));
			m_skills[i].img_acquired_title = img_title_resize;
		}
	}

	ifs.imbue(L);
	ifs.close();
}

void CUmaEvaluatorDlg::ReadSkillLv()
{
	m_skillLv.clear();

	// スキルレベル画像の読み込み
	wstring sImgDir = GetImgDir();

	for (int i = 0; i < 6; ++i) {
		wstring si = to_wstring(i);
		wstring sFilePNG = sImgDir + L"Lv" + si + L".png";
		cv::Mat img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
		m_skillLv.push_back(img);
	}

	wstring sFilePNG = sImgDir + L"Lv0_gold.png";
	cv::Mat img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
	m_skillLv.push_back(img);
}

void CUmaEvaluatorDlg::ReadUniqLv()
{
	m_uniqLv.clear();

	// 固有スキルレベル画像の読み込み
	wstring sImgDir = GetImgDir();

	for (int i = 0; i < 6; ++i) {
		wstring si = to_wstring(i+1);
		wstring sFilePNG = sImgDir + L"uniqLv" + si + L".png";
		cv::Mat img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
		m_uniqLv.push_back(img);
	}
}

void CUmaEvaluatorDlg::ReadStatusPointTSV()
{
	m_vnStatusPoint.resize(MAX_STATUS_POINT + 1);

	wstring sDataDir = GetDataDir();
	wstring sFileTSV = sDataDir + L"status_point.txt";
	wifstream ifs(sFileTSV);

	auto Loc = locale("Japanese");
	auto L = ifs.imbue(Loc);

	wstring line;
	while (getline(ifs, line)) {

		CSkill skill;

		wstringstream iss(line);
		wstring s;
		getline(iss, s, L'\t');
		int i = stoi(s);
		getline(iss, s, L'\t');
		int nPt = stoi(s);

		if (0 <= i && i <= MAX_STATUS_POINT) {
			m_vnStatusPoint[i] = nPt;
		}
	}

	ifs.imbue(L);
	ifs.close();
}

void CUmaEvaluatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CUmaEvaluatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CUmaEvaluatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



cv::Mat CUmaEvaluatorDlg::GetDesktopImage() const
{
	// モニターサイズ取得
	HWND desktop = ::GetDesktopWindow();
	RECT rect;
	::GetWindowRect(desktop, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// DIBの情報を設定する
	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = -height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24; //cv::Matの画像をアルファチャンネル有りにする場合はは32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	LPDWORD lpPixel;
	HDC hDC = ::GetDC(desktop);
	HBITMAP hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
	HDC hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC, hBitmap);

	cv::Mat img;
	img.create(height, width, CV_8UC3); //RGBのみ。アルファちゃんねるを加えるにはCV_8UN4

	//hDCの画像（スクリーンショット）をhMemDCにコピーする
	BitBlt(hMemDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
	// hMemDCの内容をcv::Matの画像（monitor_img）にコピー
	GetDIBits(hMemDC, hBitmap, 0, height, img.data, (BITMAPINFO*)&bmpInfo, DIB_RGB_COLORS);

	//メモリ開放
	::ReleaseDC(desktop, hDC);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);

	return img;
}

cv::Mat CUmaEvaluatorDlg::GetUmaWindowImage() const
{
	WCHAR umamusume[] = { L"umamusume" };

	WCHAR title[256];
	HWND hWindow = ::GetForegroundWindow();
	while (hWindow != NULL) {
		int len = ::GetWindowText(hWindow, title, 256);
		DWORD style = GetWindowLong(hWindow, GWL_STYLE);
		if ((style & WS_VISIBLE) != 0 && wcscmp(title, umamusume) == 0) {
			break;
		}
		hWindow = ::GetNextWindow(hWindow, GW_HWNDNEXT);
	}
	if (hWindow == NULL) {
		return cv::Mat();
	}

	RECT rc;
	::GetClientRect(hWindow, &rc);

	int width = rc.right;
	int height = rc.bottom;

	POINT ppt;
	ppt.x = 0;
	ppt.y = 0;
	::ClientToScreen(hWindow, &ppt);

	cv::Mat desktop = GetDesktopImage();

	return cv::Mat(desktop, cv::Rect(ppt.x, ppt.y, width, height));
}

double MatchImageRel(const cv::Mat& img_templ, const cv::Mat& img_ref)
{
	cv::Mat result;
	cv::matchTemplate(img_ref, img_templ, result, cv::TM_CCORR_NORMED);

	double dMin, dMax;
	cv::minMaxLoc(result, &dMin, &dMax);
	return dMax;
}

bool CUmaEvaluatorDlg::MatchImage(const cv::Mat& img_templ, const cv::Mat& img, double crit) const
{
	double d = MatchImageRel(img_templ, img);
	return (d > crit);
}



wstring CUmaEvaluatorDlg::GetExeDir() const
{
	TCHAR path[MAX_PATH];
	if (!::GetModuleFileName(NULL, path, MAX_PATH))
		return L"";

	CString csPath = path;
	wstring sPath = csPath.GetBuffer();

	const size_t i = sPath.rfind('\\');
	if (wstring::npos == i)
		return L"";

	wstring sDir = sPath.substr(0, i+1);

	return sDir;
}

int CUmaEvaluatorDlg::GetTekisei(const cv::Mat& img) const
{
	double R_REF[8] = { 240.0, 244.3, 244.0, 207.9, 196.6, 231.3, 222.7, 214.8 };
	double G_REF[8] = { 222.9, 212.4, 203.1, 233.4, 225.2, 201.3, 220.6, 214.5 };
	double B_REF[8] = { 184.7, 190.7, 215.7, 199.9, 243.1, 240.7, 241.8, 215.4 };

	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	for (int j = 0; j < img.rows; ++j) {
		for (int k = 0; k < img.cols; ++k) {
			cv::Vec3b pix = img.at<cv::Vec3b>(cv::Point(k, j));
			b += pix[0];
			g += pix[1];
			r += pix[2];
		}
	}
	r /= img.rows * img.cols;
	g /= img.rows * img.cols;
	b /= img.rows * img.cols;

	int iMin = 0;
	double dMin = 255.0 * 255.0 * 3.0;
	for (int i = 0; i < 8; ++i) {
		double rd = R_REF[i] - r;
		double gd = G_REF[i] - g;
		double bd = B_REF[i] - b;
		double d = rd * rd + gd * gd + bd * bd;
		if (d < dMin) {
			iMin = i;
			dMin = d;
		}
	}

	return iMin;
}

int CUmaEvaluatorDlg::GetNumberOCR(const cv::Mat& img) const
{
#ifdef _DEBUG
	return -1;
#endif

	wstring sBinDir = GetExeDir();
	wstring sTessDir = sBinDir + L"tessdata-4.1.0";
	string s(sTessDir.begin(), sTessDir.end());

	static auto ocr = cv::text::OCRTesseract::create(s.c_str(), "eng", "0123456789");

	string text;
	vector<cv::Rect> boxes;
	vector<string> words;
	vector<float> confidences;

	cv::Mat img_gray;
	cv::cvtColor(img, img_gray, cv::COLOR_RGB2GRAY);

	ocr->run(img_gray, text, &boxes, &words, &confidences);

	int n = -1;
	try {
		n = stoi(text);
	}
	catch (...) {
	}

	return n;
}

int CUmaEvaluatorDlg::GetSkillLvFromImage(const cv::Mat& img) const
{
	double dMax = 0.0;
	int iMax = 0;
	for (int i = 0; i < m_skillLv.size(); ++i) {
		double d = MatchImageRel(img, m_skillLv[i]);
		if (d > dMax) {
			dMax = d;
			iMax = i;
		}
	}

	if (iMax == 6) iMax = 0;

	return iMax;
}


int CUmaEvaluatorDlg::GetUniqLvFromImage(const cv::Mat& img) const
{
	double dMax = 0.0;
	int iMax = 0;
	for (int i = 0; i < m_uniqLv.size(); ++i) {
		double d = MatchImageRel(img, m_uniqLv[i]);
		if (d > dMax) {
			dMax = d;
			iMax = i;
		}
	}

	return iMax + 1;
}

int CUmaEvaluatorDlg::GetSkillFromImage(const cv::Mat& img) const
{
	cv::Mat img_title(img, cv::Rect(60, 5, 120, 15));

	//解像度が低いと誤検出が多いので倍のサイズにする
	cv::Mat img_title_resize;
	cv::resize(img_title, img_title_resize, cv::Size(240, 30));

	double dMax = 0.0;
	int iMax = -1;
	for (int i = 0; i < m_skills.size(); ++i) {
		if (m_skills[i].img.empty())
			continue;

		double d = MatchImageRel(img_title_resize, m_skills[i].img_title);
		if (d > max(dMax, 0.99)) {
			dMax = d;
			iMax = i;
		}
	}

	return iMax;
}

int CUmaEvaluatorDlg::GetSkillFromAcquiredImage(const cv::Mat& img) const
{
	cv::Mat img_title(img, cv::Rect(60, 5, 120, 15));

	//解像度が低いと誤検出が多いので倍のサイズにする
	cv::Mat img_title_resize;
	cv::resize(img_title, img_title_resize, cv::Size(240, 30));

	double dMax = 0.0;
	int iMax = -1;
	for (int i = 0; i < m_skills.size(); ++i) {
		if (m_skills[i].img_acquired.empty())
			continue;

		double d = MatchImageRel(img_title_resize, m_skills[i].img_acquired_title);
		if (d > max(dMax, 0.99)) {
			dMax = d;
			iMax = i;
		}
	}

	return iMax;
}

vector<pair<cv::Mat, bool> > CUmaEvaluatorDlg::GetSkillImages(const cv::Mat img_finish) const
{
	wstring sImgDir = GetImgDir();

	cv::Mat img_plus(img_finish, cv::Rect(390, 320, 35, 280));

	wstring sFilePNG = sImgDir + L"plus.png";
	cv::Mat img_plus_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	sFilePNG = sImgDir + L"plus_gold.png";
	cv::Mat img_plus_gold_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	map<int, bool> miPlusY; 
	for (int i = 0; i < 4; ++i) {
		cv::Mat result;
		cv::matchTemplate(img_plus, img_plus_ref, result, cv::TM_CCORR_NORMED);

		double d;
		cv::Point p;
		cv::minMaxLoc(result, NULL, &d, NULL, &p);

		if (d < 0.99)
			break;

		miPlusY.insert(pair<int, bool>(p.y, false));

		cv::Point p1(35, p.y + 35);
		cv::rectangle(img_plus, p, p1, cv::Scalar(0, 0, 0), cv::FILLED);
	}

	for (int i = 0; i < 4; ++i) {
		cv::Mat result;
		cv::matchTemplate(img_plus, img_plus_gold_ref, result, cv::TM_CCORR_NORMED);

		double d;
		cv::Point p;
		cv::minMaxLoc(result, NULL, &d, NULL, &p);

		if (d < 0.99)
			break;

		miPlusY.insert(pair<int, bool>(p.y, true));

		cv::Point p1(35, p.y + 35);
		cv::rectangle(img_plus, p, p1, cv::Scalar(0, 0, 0), cv::FILLED);
	}

	vector<pair<cv::Mat, bool> > vImages;
	for (map<int, bool>::iterator it = miPlusY.begin(); it != miPlusY.end(); ++it) {
		cv::Mat img(img_finish, cv::Rect(20, it->first + 290, 410, 95));
		vImages.push_back(pair<cv::Mat, bool>(img, it->second));
	}

	return vImages;
}

vector<cv::Mat> CUmaEvaluatorDlg::GetSkillImagesAcquired(const cv::Mat img_finish) const
{
	wstring sImgDir = GetImgDir();

	// 固有スキルはいれたくないので２番めから検出
	cv::Mat img_acquired(img_finish, cv::Rect(345, 350, 40, 240));

	wstring sFilePNG = sImgDir + L"acquired.png";
	cv::Mat img_acquired_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	set<int> siAcquiredY;
	for (int i = 0; i < 3; ++i) {
		cv::Mat result;
		cv::matchTemplate(img_acquired, img_acquired_ref, result, cv::TM_CCORR_NORMED);

		double d;
		cv::Point p;
		cv::minMaxLoc(result, NULL, &d, NULL, &p);

		if (d < 0.99)
			break;

		siAcquiredY.insert(p.y);

		cv::Point p1(40, p.y + 10);
		cv::rectangle(img_acquired, p, p1, cv::Scalar(0, 0, 0), cv::FILLED);
	}

	vector<cv::Mat> vImages;
	for (set<int>::iterator it = siAcquiredY.begin(); it != siAcquiredY.end(); ++it) {
		cv::Mat img(img_finish, cv::Rect(20, *it + 310, 410, 95));
		vImages.push_back(img);
	}

	return vImages;
}

CString CUmaEvaluatorDlg::WS2CS(const wstring& ws) const
{
	CString cs;
	cs.Format(_T("%s"), ws.c_str());
	return cs;
}

CString CUmaEvaluatorDlg::Int2CS(int n) const
{
	CString cs;
	cs.Format(_T("%d"), n);
	return cs;
}

void CUmaEvaluatorDlg::OnBnClickedButtonDetect()
{
	CString cs;
	m_buttonDetect.GetWindowTextW(cs);
	if (cs == L"検出") {
		m_timerID = SetTimer(1, 1000, NULL);
		m_buttonDetect.SetWindowTextW(L"停止");
	}
	else {
		KillTimer(m_timerID);
		m_buttonDetect.SetWindowTextW(L"検出");
	}
}

void CUmaEvaluatorDlg::Detect()
{
	const int DEFAULT_WIDTH = 450;
	const int DEFAULT_HEIGHT = 800;

	wstring sImgDir = GetImgDir();

	cv::Mat img = GetUmaWindowImage();

	if (img.empty())
		return;

	cv::Mat img_finish;
	cv::resize(img, img_finish, cv::Size(DEFAULT_WIDTH, DEFAULT_HEIGHT));

	// ウマ娘詳細
	cv::Mat img_detail(img_finish, cv::Rect(170, 30, 110, 25));
	wstring sFilePNG = sImgDir + L"detail_bar.png";
	cv::Mat img_detail_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	if (MatchImage(img_detail, img_detail_ref)) {

		{ // 星
			int nStar = 0;
			int l = 59;
			for (int i = 0; i < 5; ++i) {
				cv::Vec3b pix = img_finish.at<cv::Vec3b>(cv::Point(l, 170));
				int b = pix[0];
				if (150 < b) break;
				++nStar;
				l += 15;
			}
			if (0 < nStar) {
				m_comboStar.SetCurSel(nStar - 1);
			}
		}

		{ // ステータス
			CEdit* edits[5] = { &m_editSpeed, &m_editStamina, &m_editPower, &m_editKonjou, &m_editKashikosa };
			int RECT_LEFT[5] = { 49, 131, 215, 299, 383 };

			for (int i = 0; i < 5; ++i) {
				// 左と上下に多めにとって、白く塗りつぶす
				cv::Rect rect(RECT_LEFT[i] - 10, 210 - 10, 58, 17 + 20);
				cv::Mat img(img_finish, rect);

				{
						cv::Rect rect_fill(0, 0, 10, 17 + 20);
						cv::rectangle(img, rect_fill, cv::Scalar(255, 255, 255), cv::FILLED);
				}

				{
					cv::Rect rect_fill(0, 0, 58, 10);
					cv::rectangle(img, rect_fill, cv::Scalar(255, 255, 255), cv::FILLED);
				}

				{
					cv::Rect rect_fill(0, 17 + 20 - 10, 58, 10);
					cv::rectangle(img, rect_fill, cv::Scalar(255, 255, 255), cv::FILLED);
				}

				int n = GetNumberOCR(img);
				if( n >= 0 ) {
					edits[i]->SetWindowTextW(Int2CS(n));
				}
			}
		}

		{ // 適正
			CComboBox* combos[10] = {
				&m_comboTurf, &m_comboDart,
				&m_comboShort, &m_comboMile, &m_comboMiddle, &m_comboLong,
				&m_comboNige, &m_comboSenkou, &m_comboSashi, &m_comboOikomi
			};

			int RECT_LEFT[4] = { 150, 233, 316, 399 };
			int RECT_TOP[3] = { 255, 280, 305 };

			int i = 0;
			for (int iRow = 0; iRow < 3; ++iRow) {
				for (int iCol = 0; iCol < 4; ++iCol) {
					if (iRow == 0 && iCol == 2)
						break;
					int l = RECT_LEFT[iCol];
					int t = RECT_TOP[iRow];
					cv::Mat img(img_finish, cv::Rect(l, t, 20, 15));

					int j = GetTekisei(img);
					combos[i]->SetCurSel(j);

					++i;
				}
			}
		}

		{ // 切れ者
			cv::Mat img_condition(img_finish, cv::Rect(65, 390, 110, 15));
			wstring sFilePNG = sImgDir + L"condition_bar.png";
			cv::Mat img_condition_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

			if (MatchImage(img_condition, img_condition_ref)) {

				cv::Mat img_condition_frame(img_finish, cv::Rect(0, 410, 450, 390));

				wstring sFilePNG = sImgDir + L"kiremono.png";
				cv::Mat img_kiremono = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

				if (MatchImage(img_kiremono, img_condition_frame)) {
					m_checkKiremono.SetCheck(BST_CHECKED);
				}
			}

			UpdateSkillList();
		}

		{ // 固有スキルレベル
			cv::Mat img_skill(img_finish, cv::Rect(310, 390, 45, 15));
			wstring sFilePNG = sImgDir + L"skill_bar.png";
			cv::Mat img_skill_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

			if (MatchImage(img_skill, img_skill_ref)) {

				cv::Mat img_UniqLv(img_finish, cv::Rect(210, 440, 10, 15));

				int n = GetUniqLvFromImage(img_UniqLv);
				m_comboUniqueSkillLv.SetCurSel(n - 1);
			}
		}

		UpdateEval();
		return;
	}

	{ // スキル取得
		cv::Mat img_skill_select(img_finish, cv::Rect(15, 5, 100, 15));
		wstring sFilePNG = sImgDir + L"skill_select.png";
		cv::Mat img_skill_select_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

		if (MatchImage(img_skill_select, img_skill_select_ref)) {

			cv::Mat img_skill_pt(img_finish, cv::Rect(330, 250, 70, 25));

			int n = GetNumberOCR(img_skill_pt);
			if (n >= 0) {
				m_editSkillPt.SetWindowTextW(Int2CS(n));
			}

			{ // 未取得スキル
				vector<pair<cv::Mat, bool> > vImages = GetSkillImages(img_finish);

				for (int i = 0; i < vImages.size(); ++i) {

					const cv::Mat& img_skill_frame = vImages[i].first;
					cv::Mat img_skill(img_skill_frame, cv::Rect(5, 5, 280, 90));

					int iSkill = GetSkillFromImage(img_skill);
					if (iSkill < 0)
						continue;

					vector<int> viSkills;

					//○スキルなら◎スキルもあれば追加
					if (m_skills[iSkill].sName.substr(m_skills[iSkill].sName.length() - 1) == L"◯") {
						int iDoubleCircle = -1;
						for (int j = 0; j < m_skills.size(); ++j) {
							if (m_skills[j].iSubSkill == iSkill && m_skills[j].sName.substr(m_skills[j].sName.length() - 1) == L"◎") {
								iDoubleCircle = j;
								break;
							}
						}
						if (iDoubleCircle > -1) {
							viSkills.push_back(iDoubleCircle);
						}
					}
					viSkills.push_back(iSkill);

					//◎スキルなら○スキルを獲得済みスキルに追加
					if (m_skills[iSkill].sName.substr(m_skills[iSkill].sName.length() - 1) == L"◎") {
						int iSubSkill = m_skills[iSkill].iSubSkill;
						if (iSubSkill > -1) {
							bool bFound = false;
							for (int j = 0; j < m_vSkillItemsAcquired.size(); ++j) {
								if (m_vSkillItemsAcquired[j].iSkill == iSubSkill) {
									bFound = true;
									break;
								}
							}
							if (!bFound) {
								AddSkillItemAcquired(CSkillItem(iSubSkill, -1));
							}
						}
					}

					cv::Mat img_Lv(img_skill_frame, cv::Rect(365, 2, 10, 15));
					int iLv = GetSkillLvFromImage(img_Lv);

					for (int j = 0; j < viSkills.size(); ++j) {
						int iSkill = viSkills[j];
						bool bFound = false;
						for (int j = 0; j < m_vSkillItems.size(); ++j) {
							if (m_vSkillItems[j].iSkill == iSkill) {
								bFound = true;
								break;
							}
						}
						if (!bFound) {
							AddSkillItemCandidate(CSkillItem(iSkill, iLv));
						}
					}
				}
			}

			{ // 獲得済みスキル
				vector<cv::Mat> vImages = GetSkillImagesAcquired(img_finish);

				for (int i = 0; i < vImages.size(); ++i) {

					const cv::Mat& img_skill_frame = vImages[i];
					cv::Mat img_skill(img_skill_frame, cv::Rect(5, 5, 280, 90));

					int iSkill = GetSkillFromAcquiredImage(img_skill);
					if (iSkill < 0)
						continue;

					bool bFound = false;
					for (int j = 0; j < m_vSkillItemsAcquired.size(); ++j) {
						if (m_vSkillItemsAcquired[j].iSkill == iSkill) {
							bFound = true;
							break;
						}
					}
					if (!bFound) {
						AddSkillItemAcquired(CSkillItem(iSkill, -1));

						//◎スキルなら○スキルを獲得済みスキルに追加
						if (m_skills[iSkill].sName.substr(m_skills[iSkill].sName.length() - 1) == L"◎") {
							int iSubSkill = m_skills[iSkill].iSubSkill;
							if (iSubSkill > -1) {
								bool bFound = false;
								for (int j = 0; j < m_vSkillItemsAcquired.size(); ++j) {
									if (m_vSkillItemsAcquired[j].iSkill == iSubSkill) {
										bFound = true;
										break;
									}
								}
								if (!bFound) {
									AddSkillItemAcquired(CSkillItem(iSubSkill, -1));
								}
							}
						}

					}
				}
			}
		}
	}
}

void CUmaEvaluatorDlg::AddSkillItemCandidate(const CSkillItem& skillItem)
{
	m_bOnUpdateSkillList = true;

	m_vSkillItems.push_back(skillItem);

	int iSkill = skillItem.iSkill;
	int iLv = skillItem.iLv;
	const CSkill& skill = m_skills[iSkill];

	const wstring& wsName = skill.sName;

	int nPt = GetSkillObtainPt(skillItem);

	wstring wsTekisei = skill.GetTekiseiStr();
	int nEval = GetEvalOfSkill(skill);

	int n = m_listCtrlSkillCandidate.GetItemCount();
	m_listCtrlSkillCandidate.InsertItem(n, WS2CS(wsTekisei));
	m_listCtrlSkillCandidate.SetItemText(n, 1, WS2CS(wsName));
	m_listCtrlSkillCandidate.SetItemText(n, 2, Int2CS(iLv));
	m_listCtrlSkillCandidate.SetItemText(n, 3, Int2CS(nPt));
	m_listCtrlSkillCandidate.SetItemText(n, 4, Int2CS(nEval));

	CRect rc;
	m_listCtrlSkillCandidate.GetItemRect(0, &rc, LVIR_BOUNDS);//行高さ
	int index = m_listCtrlSkillCandidate.GetTopIndex();//現在行
	int offset = rc.Height() * (m_listCtrlSkillCandidate.GetItemCount() - 1 - index);//10行へオフセット計算
	CSize cs;
	cs.cx = 0;
	cs.cy = offset;
	if (offset) {
		m_listCtrlSkillCandidate.Scroll(cs);
	}

	m_bOnUpdateSkillList = false;
}

void CUmaEvaluatorDlg::AddSkillItemAcquired(const CSkillItem& skillItem)
{
	m_bOnUpdateSkillList = true;

	m_vSkillItemsAcquired.push_back(skillItem);

	int iSkill = skillItem.iSkill;
	int iLv = skillItem.iLv;
	const CSkill& skill = m_skills[iSkill];

	const wstring& wsName = skill.sName;

	wstring wsTekisei = skill.GetTekiseiStr();
	int nEval = GetEvalOfSkill(skill);

	int n = m_listCtrlSkillAcquired.GetItemCount();
	m_listCtrlSkillAcquired.InsertItem(n, WS2CS(wsTekisei));
	m_listCtrlSkillAcquired.SetItemText(n, 1, WS2CS(wsName));
	m_listCtrlSkillAcquired.SetItemText(n, 2, Int2CS(nEval));

	CRect rc;
	m_listCtrlSkillAcquired.GetItemRect(0, &rc, LVIR_BOUNDS);//行高さ
	int index = m_listCtrlSkillAcquired.GetTopIndex();//現在行
	int offset = rc.Height() * (m_listCtrlSkillAcquired.GetItemCount() - 1 - index);//10行へオフセット計算
	CSize cs;
	cs.cx = 0;
	cs.cy = offset;
	if (offset) {
		m_listCtrlSkillAcquired.Scroll(cs);
	}

	UpdateEval();
		
	m_bOnUpdateSkillList = false;
}

int CUmaEvaluatorDlg::GetSkillObtainPt(const CSkillItem& skillItem) const
{
	int iSkill = skillItem.iSkill;
	int iLv = skillItem.iLv;
	const CSkill& skill = m_skills[skillItem.iSkill];
	int nPt = skill.nPt;

	// nPtは10の倍数なのでLv4のときに0.5の端数が出る可能性がある
	int nTenth = nPt / 10;
	int nReduce = 0;
	if (iLv == 1) nReduce = nTenth;
	if (iLv == 2) nReduce = nTenth * 2;
	if (iLv == 3) nReduce = nTenth * 3;
	if (iLv == 4) nReduce = int(round(nTenth * 3.5 + 0.1));
	if (iLv == 5) nReduce = nTenth * 4;
	nPt -= nReduce;

	if( m_checkKiremono.GetCheck() == BST_CHECKED ) {
		nPt -= nTenth;
	}

	return nPt;
}

int CUmaEvaluatorDlg::GetEvalOfSkill(const CSkill& skill) const
{
	int nEval = skill.nEval;
	if (skill.tekisei.empty())
		return nEval;

	const CComboBox* combos[SKILL_TEKISEI_SIZE] = {
		&m_comboTurf,& m_comboDart,
		&m_comboShort, &m_comboMile, &m_comboMiddle, &m_comboLong,
		&m_comboNige, &m_comboSenkou, &m_comboSashi, &m_comboOikomi
	};

	double d = 1.0;
	set<SKILL_TEKISEI>::iterator it = skill.tekisei.begin();
	for (; it != skill.tekisei.end(); ++it) {
		if (*it == SKILL_TEKISEI_TURF) continue;
		if (*it == SKILL_TEKISEI_DART) continue;
		int iSel = combos[*it]->GetCurSel();
		switch (iSel) {
		case 0:
		case 1:
			d *= 1.1;
			break;
		case 2:
		case 3:
			d *= 0.9;
			break;
		case 4:
		case 5:
		case 6:
			d *= 0.8;
			break;
		case 7:
			d *= 0.7;
			break;
		}
	}

	// 上位スキルの場合は、下位スキルと合算して適性係数をかけた後に下位スキルの分を引く
	if (skill.iSubSkill > -1) {
		int nEvalSub = m_skills[skill.iSubSkill].nEval;
		return int(round((nEval+nEvalSub) * d)) - int(round(nEvalSub * d));
	}
	else {
		return int(round(nEval * d));
	}
}

void CUmaEvaluatorDlg::UpdateSkillList()
{
	m_bOnUpdateSkillList = true;

	int nPtUsed = 0;

	m_listCtrlSkillCandidate.DeleteAllItems();
	m_listCtrlSkillObtain.DeleteAllItems();
	int iCandidate = 0;
	int iObtain = 0;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bHidden)
			continue;
		int iSkill = m_vSkillItems[i].iSkill;
		int iLv = m_vSkillItems[i].iLv;
		const CSkill& skill = m_skills[iSkill];

		const wstring& wsName = skill.sName;

		int nPt = GetSkillObtainPt(m_vSkillItems[i]);

		wstring wsTekisei = skill.GetTekiseiStr();
		int nEval = GetEvalOfSkill(skill);

		if (m_vSkillItems[i].bObtain) {
			m_listCtrlSkillObtain.InsertItem(iObtain, WS2CS(wsTekisei));
			m_listCtrlSkillObtain.SetItemText(iObtain, 1, WS2CS(wsName));
			m_listCtrlSkillObtain.SetItemText(iObtain, 2, Int2CS(iLv));
			m_listCtrlSkillObtain.SetItemText(iObtain, 3, Int2CS(nPt));
			m_listCtrlSkillObtain.SetItemText(iObtain, 4, Int2CS(nEval));
			if (m_vSkillItems[i].bSelected) {
				m_listCtrlSkillObtain.SetItemState(iObtain, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			}
			++iObtain;

			nPtUsed += nPt;
		}
		else {
			m_listCtrlSkillCandidate.InsertItem(iCandidate, WS2CS(wsTekisei));
			m_listCtrlSkillCandidate.SetItemText(iCandidate, 1, WS2CS(wsName));
			m_listCtrlSkillCandidate.SetItemText(iCandidate, 2, Int2CS(iLv));
			m_listCtrlSkillCandidate.SetItemText(iCandidate, 3, Int2CS(nPt));
			m_listCtrlSkillCandidate.SetItemText(iCandidate, 4, Int2CS(nEval));
			if (m_vSkillItems[i].bSelected) {
				m_listCtrlSkillCandidate.SetItemState(iCandidate, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			}
			++iCandidate;
		}
	}

	m_listCtrlSkillAcquired.DeleteAllItems();
	for (int i = 0; i < m_vSkillItemsAcquired.size(); ++i) {
		int iSkill = m_vSkillItemsAcquired[i].iSkill;
		const CSkill& skill = m_skills[iSkill];

		const wstring& wsName = skill.sName;

		wstring wsTekisei = skill.GetTekiseiStr();
		int nEval = GetEvalOfSkill(skill);

		m_listCtrlSkillAcquired.InsertItem(i, WS2CS(wsTekisei));
		m_listCtrlSkillAcquired.SetItemText(i, 1, WS2CS(wsName));
		m_listCtrlSkillAcquired.SetItemText(i, 2, Int2CS(nEval));
	}

	m_stSkillPtUsed.SetWindowTextW(L"使用スキルPt：" + Int2CS(nPtUsed));

	CString cs;
	m_editSkillPt.GetWindowTextW(cs);
	if (cs != L"") {
		int nSkillPt = _ttoi(cs);
		int nPtRemain = nSkillPt - nPtUsed;
		m_stSkillPtRemain.SetWindowTextW(L"残りスキルPt：" + Int2CS(nPtRemain));
	}
	else {
		m_stSkillPtRemain.SetWindowTextW(L"残りスキルPt：");
	}

	m_bOnUpdateSkillList = false;

}

void CUmaEvaluatorDlg::OnBnClickedButtonSkillRegistration()
{
	const int DEFAULT_WIDTH = 450;
	const int DEFAULT_HEIGHT = 800;

	wstring sDataDir = GetDataDir();
	wstring sImgDir = GetImgDir();

	cv::Mat img = GetUmaWindowImage();
	if (img.empty())
		return;

	cv::Mat img_finish;
	cv::resize(img, img_finish, cv::Size(DEFAULT_WIDTH, DEFAULT_HEIGHT));

	cv::Mat img_skill_select(img_finish, cv::Rect(0, 0, 100, 25));
	wstring sFilePNG = sImgDir + L"skill_select.png";
	cv::Mat img_skill_select_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	// スキル取得
	if (!MatchImage(img_skill_select, img_skill_select_ref)) {
		MessageBox(L"スキル取得画面を表示してください。");
		return;
	}

	vector<pair<cv::Mat, bool> > vImages = GetSkillImages(img_finish);

	for (int i = 0; i < vImages.size(); ++i) {

		const cv::Mat& img_skill_frame = vImages[i].first;

		cv::Mat img_skill(img_skill_frame, cv::Rect(5, 5, 280, 90));

		CRegisterSkillDlg dlg;

		int idx = dlg.Setup(img_skill, m_skills);
		if (idx < 0)
			continue;

		wstring sSkillDir = sDataDir + L"skills\\";
		wstring sFilePNG = sSkillDir + to_wstring(idx)+ L".png";
		cv::imwrite(string(sFilePNG.begin(), sFilePNG.end()), img_skill);
	}

	ReadSkillTSV();
}


void CUmaEvaluatorDlg::OnLvnItemchangedListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_bOnUpdateSkillList)
		return;

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	set<int> siSelected;
	POSITION pos = m_listCtrlSkillCandidate.GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = m_listCtrlSkillCandidate.GetNextSelectedItem(pos);
		siSelected.insert(nItem);
	}

	int iCandidate = -1;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bObtain)
			continue;
		if (m_vSkillItems[i].bHidden)
			continue;
		++iCandidate;
		m_vSkillItems[i].bSelected = (siSelected.find(iCandidate) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	if (pLVKeyDow->wVKey != VK_DELETE) {
		*pResult = 0;
		return;
	}

	m_bOnUpdateSkillList = true;

	vector<int> viCandidate;
	int iCandidate = 0;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (!m_vSkillItems[i].bObtain && !m_vSkillItems[i].bHidden) {
			if (m_vSkillItems[i].bSelected)
				viCandidate.push_back(iCandidate);
			++iCandidate;
		}
	}
	for (int i = (int)viCandidate.size() - 1; i > -1; --i) {
		int iCandidate = viCandidate[i];
		m_listCtrlSkillCandidate.DeleteItem(iCandidate);
	}

	vector<CSkillItem> skillsNew;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bObtain || !m_vSkillItems[i].bSelected || m_vSkillItems[i].bHidden) {
			skillsNew.push_back(m_vSkillItems[i]);
		}
	}
	m_vSkillItems = skillsNew;

	m_bOnUpdateSkillList = false;

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonToObtain()
{
	// 上位スキルで下位スキルが存在する場合は選択して移動させる
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bObtain) continue;
		if (!m_vSkillItems[i].bSelected) continue;
		if (m_vSkillItems[i].bHidden) continue;

		int iSkill = m_vSkillItems[i].iSkill;
		const CSkill& skill = m_skills[iSkill];
		if (skill.iSubSkill == -1) continue;

		for (int j = 0; j < m_vSkillItems.size(); ++j) {
			if (m_vSkillItems[j].bObtain) continue;

			if (m_vSkillItems[j].iSkill == skill.iSubSkill ) {
				m_vSkillItems[j].bSelected = true;
			}
		}
	}

	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (!m_vSkillItems[i].bObtain && m_vSkillItems[i].bSelected) {
			m_vSkillItems[i].bObtain = true;
		}
	}

	UpdateSkillList();
	UpdateEval();

}


void CUmaEvaluatorDlg::OnLvnItemchangedListCtrlSkillObtain(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_bOnUpdateSkillList)
		return;
 
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	set<int> siSelected;
	POSITION pos = m_listCtrlSkillObtain.GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = m_listCtrlSkillObtain.GetNextSelectedItem(pos);
		siSelected.insert(nItem);
	}

	int iObtain = -1;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (!m_vSkillItems[i].bObtain)
			continue;
		if (m_vSkillItems[i].bHidden)
			continue;
		++iObtain;
		m_vSkillItems[i].bSelected = (siSelected.find(iObtain) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonToCandidate()
{
	// 下位スキルで上位スキルが存在する場合は選択して移動させる
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (!m_vSkillItems[i].bObtain) continue;
		if (!m_vSkillItems[i].bSelected) continue;
		if (m_vSkillItems[i].bHidden) continue;

		int iSkill = m_vSkillItems[i].iSkill;
		const CSkill& skill = m_skills[iSkill];

		for (int j = 0; j < m_vSkillItems.size(); ++j) {
			if (!m_vSkillItems[j].bObtain) continue;

			int iUpperSkill = m_vSkillItems[j].iSkill;
			const CSkill& skillUpper = m_skills[iUpperSkill];
			if (skillUpper.iSubSkill == iSkill) {
				m_vSkillItems[j].bSelected = true;
			}
		}
	}

	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bObtain && m_vSkillItems[i].bSelected) {
			m_vSkillItems[i].bObtain = false;
		}
	}

	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnEnChangeEditSpeed()
{
	UpdateEval();
}



void CUmaEvaluatorDlg::OnEnChangeEditStamina()
{
	UpdateEval();
}


void CUmaEvaluatorDlg::OnEnChangeEditPower()
{
	UpdateEval();
}


void CUmaEvaluatorDlg::OnEnChangeEditKonjou()
{
	UpdateEval();
}


void CUmaEvaluatorDlg::OnEnChangeEditKashikosa()
{
	UpdateEval();
}

void CUmaEvaluatorDlg::UpdateEval()
{
	int nEvalStatusUniq = GetStatusUniqEval();
	if (nEvalStatusUniq > -1) {
		m_stStatusPoint.SetWindowTextW(L"ステータス・固有スキル評価点：" + Int2CS(nEvalStatusUniq));
	}
	else {
		m_stStatusPoint.SetWindowTextW(L"ステータス・固有スキル評価点：");
	}

	int nEvalSkill = GetSkillEval();
	if (nEvalSkill > -1) {
		m_stSkillEval.SetWindowTextW(L"取得スキル評価点：" + Int2CS(nEvalSkill));
	}
	else {
		m_stSkillEval.SetWindowTextW(L"取得スキル評価点：");
	}

	int nEvalSkillAcquired = GetSkillAcquiredEval();
	if (nEvalSkillAcquired > -1) {
		m_stSkillAcquiredEval.SetWindowTextW(L"獲得済みスキル評価点：" + Int2CS(nEvalSkillAcquired));
	}
	else {
		m_stSkillAcquiredEval.SetWindowTextW(L"獲得済みスキル評価点：");
	}

	if (nEvalStatusUniq > -1 && nEvalSkill > -1 && nEvalSkillAcquired > -1) {
		int nEvalTotal = nEvalStatusUniq + nEvalSkill + nEvalSkillAcquired;
		wstring sRank = GetRankFromEval(nEvalTotal);
		m_stTotalEval.SetWindowTextW(L"評価点合計：" + Int2CS(nEvalTotal) + " ランク：" + WS2CS(sRank));
	}
	else {
		m_stTotalEval.SetWindowTextW(L"評価点合計：");
	}
}

wstring CUmaEvaluatorDlg::GetRankFromEval(int nEval) const
{
	const int RANK_POINT[29] = {
		0, 300, 600, 900, 1300, 1800, 2300, 2900, 3500, 4900, 6500, 8200, 10000, 12100, // G-A+
		14500, 15900, 17500, 19200,  // S-SS+
		19600, 20000, 20400, 20800,  21200, 21600, 22100, 22500, 23000, 23400, // UG
		23900 // UF
	};
	const wstring RANK_STR[29] = {
		L"G", L"G+", L"F", L"F+", L"E", L"E+", L"D", L"D+", L"C", L"C+", L"B", L"B+", L"A", L"A+",
		L"S", L"S+", L"SS", L"SS+",
		L"UG", L"UG1", L"UG2", L"UG3", L"UG4", L"UG5", L"UG6", L"UG7", L"UG8", L"UG9",
		L">=UF",
	};

	int iRank = 0;
	for (int i = 0; i < 29; ++i) {
		if (RANK_POINT[i] <= nEval)
			iRank = i;
	}

	return RANK_STR[iRank];
}

int CUmaEvaluatorDlg::GetStatusUniqEval() const
{
	int nPt = 0;

	// ステータス評価点
	const CEdit* edits[5] = { &m_editSpeed, &m_editStamina, &m_editPower, &m_editKonjou, &m_editKashikosa };
	for (int i = 0; i < 5; ++i) {
		CString cs;
		edits[i]->GetWindowTextW(cs);
		int n = _ttoi(cs);

		if (0 <= n && n <= MAX_STATUS_POINT) {
			nPt += m_vnStatusPoint[n];
		}
		else {
			return -1;
		}
	}

	// 固有スキル評価点
	int iStar = m_comboStar.GetCurSel() + 1;
	int iLv = m_comboUniqueSkillLv.GetCurSel() + 1;
	if (iStar < 1) return -1;
	if (iLv < 1) return -1;

	if (iStar <= 2) {
		if (iLv == 1) nPt += 120;
		if (iLv == 2) nPt += 240;
		if (iLv == 3) nPt += 360;
		if (iLv == 4) nPt += 480;
		if (iLv == 5) nPt += 600;
		if (iLv == 6) return -1;
	}
	else {
		if (iLv == 1) nPt += 170;
		if (iLv == 2) nPt += 340;
		if (iLv == 3) nPt += 510;
		if (iLv == 4) nPt += 680;
		if (iLv == 5) nPt += 850;
		if (iLv == 6) nPt += 1020;
	}

	return nPt;
}

int CUmaEvaluatorDlg::GetSkillEval() const
{
	int nPt = 0;

	// 取得スキル評価点
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (!m_vSkillItems[i].bObtain)
			continue;
		if (m_vSkillItems[i].bHidden)
			continue;
		int iSkill = m_vSkillItems[i].iSkill;
		const CSkill& skill = m_skills[iSkill];
		int nEval = GetEvalOfSkill(skill);
		nPt += nEval;
	}

	return nPt;
}

int CUmaEvaluatorDlg::GetSkillAcquiredEval() const
{
	int nPt = 0;

	// 取得スキル評価点
	for (int i = 0; i < m_vSkillItemsAcquired.size(); ++i) {
		int iSkill = m_vSkillItemsAcquired[i].iSkill;
		const CSkill& skill = m_skills[iSkill];
		int nEval = GetEvalOfSkill(skill);
		nPt += nEval;
	}

	return nPt;
}

void CUmaEvaluatorDlg::OnCbnSelchangeComboStar()
{
	UpdateEval();
}


void CUmaEvaluatorDlg::OnCbnSelchangeComboUniqueSkillLevel()
{
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckKiremono()
{
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_timerID) {
		Detect();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CUmaEvaluatorDlg::HideSkillItems()
{
	bool bHideTekisei[SKILL_TEKISEI_SIZE] = {
		false,
		m_checkDart.GetCheck() == BST_UNCHECKED,
		m_checkShort.GetCheck() == BST_UNCHECKED,
		m_checkMile.GetCheck() == BST_UNCHECKED,
		m_checkMiddle.GetCheck() == BST_UNCHECKED,
		m_checkLong.GetCheck() == BST_UNCHECKED,
		m_checkNige.GetCheck() == BST_UNCHECKED,
		m_checkSenkou.GetCheck() == BST_UNCHECKED,
		m_checkSashi.GetCheck() == BST_UNCHECKED,
		m_checkOikomi.GetCheck() == BST_UNCHECKED,
	};

	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		int iSkill = m_vSkillItems[i].iSkill;
		const CSkill skill = m_skills[iSkill];
		bool bHidden = false;
		set<SKILL_TEKISEI>::iterator it = skill.tekisei.begin();
		for (; it != skill.tekisei.end(); ++it) {
			if (bHideTekisei[*it])
				bHidden = true;
		}
		m_vSkillItems[i].bHidden = bHidden;
	}
}


void CUmaEvaluatorDlg::OnBnClickedCheckDart()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckShort()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckMile()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckMiddle()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckLong()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckNige()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckSenkou()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckSashi()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedCheckOikomi()
{
	HideSkillItems();
	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CUmaEvaluatorDlg::OnBnClickedButtonUncheckUnderB()
{
	if (m_comboDart  .GetCurSel() > 1) m_checkDart  .SetCheck(BST_UNCHECKED);
	if (m_comboShort .GetCurSel() > 1) m_checkShort .SetCheck(BST_UNCHECKED);
	if (m_comboMile  .GetCurSel() > 1) m_checkMile  .SetCheck(BST_UNCHECKED);
	if (m_comboMiddle.GetCurSel() > 1) m_checkMiddle.SetCheck(BST_UNCHECKED);
	if (m_comboLong  .GetCurSel() > 1) m_checkLong  .SetCheck(BST_UNCHECKED);
	if (m_comboNige  .GetCurSel() > 1) m_checkNige  .SetCheck(BST_UNCHECKED);
	if (m_comboSenkou.GetCurSel() > 1) m_checkSenkou.SetCheck(BST_UNCHECKED);
	if (m_comboSashi .GetCurSel() > 1) m_checkSashi .SetCheck(BST_UNCHECKED);
	if (m_comboOikomi.GetCurSel() > 1) m_checkOikomi.SetCheck(BST_UNCHECKED);

	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnCustomdrawListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW lpLvCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	if (lpLvCustomDraw->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}

	if (lpLvCustomDraw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		SKILL_TYPE type = SKILL_TYPE_UNKNOWN;
		int j = 0;
		for (int i = 0; i < m_vSkillItems.size(); ++i) {
			if (m_vSkillItems[i].bHidden) continue;
			if (m_vSkillItems[i].bObtain) continue;
			if (lpLvCustomDraw->nmcd.dwItemSpec == j) {
				int iSkill = m_vSkillItems[i].iSkill;
				type = m_skills[iSkill].type;
				break;
			}
			++j;
		}

		switch (type) {
		case SKILL_TYPE_ORANGE: lpLvCustomDraw->clrTextBk = RGB(252, 195,  38); break;
		case SKILL_TYPE_BLUE  : lpLvCustomDraw->clrTextBk = RGB( 32, 220, 253); break;
		case SKILL_TYPE_RED   : lpLvCustomDraw->clrTextBk = RGB(254, 170, 169); break;
		case SKILL_TYPE_GREEN : lpLvCustomDraw->clrTextBk = RGB(188, 232,  54); break;
		default               : lpLvCustomDraw->clrTextBk = GetSysColor(COLOR_WINDOW);
		}

		*pResult = CDRF_NEWFONT;
		return;
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnCustomdrawListCtrlSkillObtain(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW lpLvCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	if (lpLvCustomDraw->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}

	if (lpLvCustomDraw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		SKILL_TYPE type = SKILL_TYPE_UNKNOWN;
		int j = 0;
		for (int i = 0; i < m_vSkillItems.size(); ++i) {
			if (m_vSkillItems[i].bHidden) continue;
			if (!m_vSkillItems[i].bObtain) continue;
			if (lpLvCustomDraw->nmcd.dwItemSpec == j) {
				int iSkill = m_vSkillItems[i].iSkill;
				type = m_skills[iSkill].type;
				break;
			}
			++j;
		}

		switch (type) {
		case SKILL_TYPE_ORANGE: lpLvCustomDraw->clrTextBk = RGB(252, 195, 38); break;
		case SKILL_TYPE_BLUE  : lpLvCustomDraw->clrTextBk = RGB(32, 220, 253); break;
		case SKILL_TYPE_RED   : lpLvCustomDraw->clrTextBk = RGB(254, 170, 169); break;
		case SKILL_TYPE_GREEN : lpLvCustomDraw->clrTextBk = RGB(188, 232, 54); break;
		default               : lpLvCustomDraw->clrTextBk = GetSysColor(COLOR_WINDOW);
		}

		*pResult = CDRF_NEWFONT;
		return;
	}

	*pResult = 0;
}

int CUmaEvaluatorDlg::SelectMaxEval(int nPt, const vector<int>& vnPt, const vector<int>& vnEval, const vector<int>& viDepend, vector<int>& viSelect)
{
	if (nPt <= 0 || vnPt.empty()) {
		viSelect.clear();
		return 0;
	}

	int n = (int)vnPt.size();

	// n-1番目のスキルを取らなかった場合
	int nEval1 = 0;
	vector<int> viSelect1;
	{
		vector<int> vnPtRest = vnPt;
		vector<int> vnEvalRest = vnEval;
		vector<int> viDependRest = viDepend;
		vnPtRest.pop_back();
		vnEvalRest.pop_back();
		viDependRest.pop_back();
		// n-1番目のスキルに上位スキルがある場合は除外
		for (int i = 0; i < n - 1; ++i) {
			if (viDependRest[i] == n - 1)
				vnPtRest[i] = 100000; // 取得Ptを大きくして実質除外
		}
		nEval1 = SelectMaxEval(nPt, vnPtRest, vnEvalRest, viDependRest, viSelect1);
	}

	// n-1番目のスキルを取った場合
	int nEval2 = 0;
	int iSub = -1;
	vector<int> viSelect2;
	{
		// n-1番目のスキルが上位スキルの場合は下位スキルも取る
		int nPtSub = 0;
		int nEvalSub = 0;
		if (-1 < viDepend[n-1] && viDepend[n - 1] < n - 1) {
			iSub = viDepend[n - 1];
			nEvalSub = vnEval[iSub];
			nPtSub = vnPt[iSub];
		}
		int nPtLast = vnPt[n - 1];
		if (nPt < nPtLast + nPtSub) {
			nEval2 = -1;
		}
		else {
			vector<int> vnPtRest = vnPt;
			vector<int> vnEvalRest = vnEval;
			vector<int> viDependRest = viDepend;
			vnPtRest.pop_back();
			vnEvalRest.pop_back();
			viDependRest.pop_back();
			nEval2 = vnEval[n-1] + nEvalSub + SelectMaxEval(nPt - nPtLast - nPtSub, vnPtRest, vnEvalRest, viDependRest, viSelect2);
		}
	}

	if (nEval1 > nEval2) {
		viSelect = viSelect1;
		return nEval1;
	}
	else {
		viSelect = viSelect2;
		viSelect.push_back(n - 1);
		if (iSub > -1)
			viSelect.push_back(iSub);
		return nEval2;
	}
}

void CUmaEvaluatorDlg::OnBnClickedButtonMaximizeEval()
{
	CString cs;
	m_editSkillPt.GetWindowTextW(cs);
	if (cs == L"") {
		MessageBox(L"スキルPtを入力してください。");
		return;
	}
	int nSkillPt = _ttoi(cs);

	int nPtUsed = 0;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if ( m_vSkillItems[i].bHidden) continue;
		if (!m_vSkillItems[i].bObtain) continue;
		int nPt = GetSkillObtainPt(m_vSkillItems[i]);
		nPtUsed += nPt;
	}

	int nPtRemain = nSkillPt - nPtUsed;

	vector<CSkillItem> vSkillItems = m_vSkillItems;

	// 残りポイントが1000以下になるまで評価点効率のいいものを確定する(上位スキルは含めない)
	set<int> siEfficients;
	{
		multimap<double, int> mmEfficiency;
		vector<int> vnPt(vSkillItems.size(), 0);
		for (int i = 0; i < vSkillItems.size(); ++i) {
			if (vSkillItems[i].bHidden) continue;
			if (vSkillItems[i].bObtain) continue;
			const CSkill& skill = m_skills[vSkillItems[i].iSkill];
			if (skill.iSubSkill > -1) continue;
			int nPt = GetSkillObtainPt(vSkillItems[i]);
			int nEval = GetEvalOfSkill(skill);
			double e = (double)nPt / (double)nEval; //昇順にするために逆数にする
			mmEfficiency.insert(pair<double, int>(e, i));
			vnPt[i] = nPt;
		}

		multimap<double, int>::iterator it = mmEfficiency.begin();
		for (; it != mmEfficiency.end(); ++it) {
			if (nPtRemain < 1000)
				break;
			int i = it->second;
			nPtRemain -= vnPt[i];
			siEfficients.insert(i);
			vSkillItems[i].bObtain = true;
		}
	}

	vector<int> viPart(vSkillItems.size(), -1);
	vector<int> vnPt;
	vector<int> vnEval;
	for (int i = 0; i < vSkillItems.size(); ++i) {
		if (vSkillItems[i].bHidden) continue;
		if (vSkillItems[i].bObtain) continue;
		const CSkill& skill = m_skills[vSkillItems[i].iSkill];
		int nPt = GetSkillObtainPt(vSkillItems[i]);
		int nEval = GetEvalOfSkill(skill);
		viPart[i] = (int)vnPt.size();
		vnPt.push_back(nPt);
		vnEval.push_back(nEval);
	}

	vector<int> viDepend(vnPt.size(), -1);
	for (int i = 0; i < vSkillItems.size(); ++i) {
		if (vSkillItems[i].bHidden) continue;
		if (vSkillItems[i].bObtain) continue;
		const CSkill& skill = m_skills[vSkillItems[i].iSkill];
		if (skill.iSubSkill == -1)
			continue;
		for (int j = 0; j < vSkillItems.size(); ++j) {
			if (vSkillItems[j].bHidden) continue;
			if (vSkillItems[j].bObtain) continue;
			if (vSkillItems[j].iSkill == skill.iSubSkill) {
				int iPart = viPart[i];
				int jPart = viPart[j];
				if (iPart > -1 && jPart > -1) {
					viDepend[iPart] = jPart;
				}
			}
		}
	}

	vector<int> viSelect;
	int nEval = SelectMaxEval(nPtRemain, vnPt, vnEval, viDepend, viSelect);

	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bHidden) continue;
		if (m_vSkillItems[i].bObtain) continue;
		m_vSkillItems[i].bSelected = false;
		if (siEfficients.find(i) != siEfficients.end())
			m_vSkillItems[i].bSelected = true;
		if (find(viSelect.begin(), viSelect.end(), viPart[i]) != viSelect.end())
			m_vSkillItems[i].bSelected = true;
	}

	UpdateSkillList();

}

void CUmaEvaluatorDlg::OnLvnHotTrackListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int iItem = pNMLV->iItem;
	if (iItem < 0) {
		*pResult = 0;
		return;
	}

	CString cs = m_listCtrlSkillCandidate.GetItemText(iItem, 1);
	wstring ws(cs);

	for (int i = 0; i < m_skills.size(); ++i) {
		if (m_skills[i].img.empty())
			continue;
		if (m_skills[i].sName == ws) {
			const cv::Mat& img = m_skills[i].img;

			// cv::Mat -> CBitmap
			char* ColorBuf = (char*)calloc(img.rows * img.rows * 4, sizeof(RGBQUAD));
			for (int y = 0; y < img.rows; y++) {
				for (int x = 0; x < img.cols; x++) {
					ColorBuf[y * img.cols * 4 + x * 4 + 0] = img.data[y * img.step + x * 3 + 0]; // B
					ColorBuf[y * img.cols * 4 + x * 4 + 1] = img.data[y * img.step + x * 3 + 1]; // G
					ColorBuf[y * img.cols * 4 + x * 4 + 2] = img.data[y * img.step + x * 3 + 2]; // R
					ColorBuf[y * img.cols * 4 + x * 4 + 3] = 0;
				}
			}

			CBitmap bmp;
			bmp.CreateBitmap(img.cols, img.rows, 1, 32, ColorBuf);
			free(ColorBuf);

			m_picCtrlSkillImageHover.SetBitmap(bmp);
			break;
		}
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonSkillRegistrationAcquired()
{
	const int DEFAULT_WIDTH = 450;
	const int DEFAULT_HEIGHT = 800;

	wstring sDataDir = GetDataDir();
	wstring sImgDir = GetImgDir();

	cv::Mat img = GetUmaWindowImage();
	if (img.empty())
		return;

	cv::Mat img_finish;
	cv::resize(img, img_finish, cv::Size(DEFAULT_WIDTH, DEFAULT_HEIGHT));

	cv::Mat img_skill_select(img_finish, cv::Rect(0, 0, 100, 25));
	wstring sFilePNG = sImgDir + L"skill_select.png";
	cv::Mat img_skill_select_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	// スキル取得
	if (!MatchImage(img_skill_select, img_skill_select_ref)) {
		MessageBox(L"スキル取得画面を表示してください。");
		return;
	}

	vector<cv::Mat> vImages = GetSkillImagesAcquired(img_finish);

	for (int i = 0; i < vImages.size(); ++i) {

		const cv::Mat& img_skill_frame = vImages[i];

		cv::Mat img_skill(img_skill_frame, cv::Rect(5, 5, 280, 90));

		CRegisterSkillDlg dlg;

		int idx = dlg.Setup(img_skill, m_skills);
		if (idx < 0)
			continue;

		wstring sSkillDir = sDataDir + L"skills\\";
		wstring sFilePNG = sSkillDir + L"a" + to_wstring(idx) + L".png";
		cv::imwrite(string(sFilePNG.begin(), sFilePNG.end()), img_skill);
	}

	ReadSkillTSV();
}


void CUmaEvaluatorDlg::OnNMCustomdrawListCtrlSkillAcquired(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVCUSTOMDRAW lpLvCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	if (lpLvCustomDraw->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}

	if (lpLvCustomDraw->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		SKILL_TYPE type = SKILL_TYPE_UNKNOWN;
		int j = 0;
		for (int i = 0; i < m_vSkillItemsAcquired.size(); ++i) {
			if (lpLvCustomDraw->nmcd.dwItemSpec == j) {
				int iSkill = m_vSkillItemsAcquired[i].iSkill;
				type = m_skills[iSkill].type;
				break;
			}
			++j;
		}

		switch (type) {
		case SKILL_TYPE_ORANGE: lpLvCustomDraw->clrTextBk = RGB(252, 195, 38); break;
		case SKILL_TYPE_BLUE: lpLvCustomDraw->clrTextBk = RGB(32, 220, 253); break;
		case SKILL_TYPE_RED: lpLvCustomDraw->clrTextBk = RGB(254, 170, 169); break;
		case SKILL_TYPE_GREEN: lpLvCustomDraw->clrTextBk = RGB(188, 232, 54); break;
		default: lpLvCustomDraw->clrTextBk = GetSysColor(COLOR_WINDOW);
		}

		*pResult = CDRF_NEWFONT;
		return;
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillAcquired(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	if (pLVKeyDow->wVKey != VK_DELETE) {
		*pResult = 0;
		return;
	}

	m_bOnUpdateSkillList = true;

	for (int i = (int)m_vSkillItemsAcquired.size() - 1; i > -1; --i) {
		if (m_vSkillItemsAcquired[i].bSelected) {
			m_listCtrlSkillAcquired.DeleteItem(i);
		}
	}

	vector<CSkillItem> skillsNew;
	for (int i = 0; i < m_vSkillItemsAcquired.size(); ++i) {
		if (!m_vSkillItemsAcquired[i].bSelected) {
			skillsNew.push_back(m_vSkillItemsAcquired[i]);
		}
	}
	m_vSkillItemsAcquired = skillsNew;

	UpdateEval();

	m_bOnUpdateSkillList = false;

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnLvnItemchangedListCtrlSkillAcquired(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_bOnUpdateSkillList)
		return;

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	set<int> siSelected;
	POSITION pos = m_listCtrlSkillAcquired.GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = m_listCtrlSkillAcquired.GetNextSelectedItem(pos);
		siSelected.insert(nItem);
	}

	for (int i = 0; i < m_vSkillItemsAcquired.size(); ++i) {
		m_vSkillItemsAcquired[i].bSelected = (siSelected.find(i) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillObtain(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	if (pLVKeyDow->wVKey != VK_DELETE) {
		*pResult = 0;
		return;
	}

	m_bOnUpdateSkillList = true;

	vector<int> viObtain;
	int iObtain = 0;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (m_vSkillItems[i].bObtain && !m_vSkillItems[i].bHidden) {
			if (m_vSkillItems[i].bSelected)
				viObtain.push_back(iObtain);
			++iObtain;
		}
	}
	for (int i = (int)viObtain.size() - 1; i > -1; --i) {
		int iObtain = viObtain[i];
		m_listCtrlSkillObtain.DeleteItem(iObtain);
	}

	vector<CSkillItem> skillsNew;
	for (int i = 0; i < m_vSkillItems.size(); ++i) {
		if (!m_vSkillItems[i].bObtain || !m_vSkillItems[i].bSelected || m_vSkillItems[i].bHidden) {
			skillsNew.push_back(m_vSkillItems[i]);
		}
	}
	m_vSkillItems = skillsNew;

	UpdateEval();

	m_bOnUpdateSkillList = false;

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonClearSkills()
{
	m_listCtrlSkillCandidate.DeleteAllItems();
	m_listCtrlSkillObtain.DeleteAllItems();
	m_listCtrlSkillAcquired.DeleteAllItems();

	m_vSkillItems.clear();
	m_vSkillItemsAcquired.clear();

	UpdateSkillList();
	UpdateEval();
}


void CUmaEvaluatorDlg::OnBnClickedButtonAddSkillManually()
{
	CDialogAddSkillManually dlg;

	int iSkill = -1;
	int nHintLv = -1;
	if ( !dlg.Setup(m_skills, iSkill, nHintLv) )
		return;

	AddSkillItemCandidate(CSkillItem(iSkill, nHintLv));
}


void CUmaEvaluatorDlg::OnBnClickedButtonAddSkillAcquiredManually()
{
	CDialogAddSkillManually dlg;

	int iSkill = -1;
	int nHintLv = -1;
	if (!dlg.Setup(m_skills, iSkill, nHintLv, true))
		return;

	AddSkillItemAcquired(CSkillItem(iSkill, -1));
}
