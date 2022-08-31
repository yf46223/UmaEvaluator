
// UmaEvaluatorDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "UmaEvaluator.h"
#include "UmaEvaluatorDlg.h"
#include "afxdialogex.h"
#include <winuser.h>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

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
	: CDialogEx(IDD_UMAEVALUATOR_DIALOG, pParent), m_bOnUpdateSkillList(false)
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

	ReadSkillTSV();
	ReadSkillLv();
	ReadStatusPointTSV();
	ReadUniqLv();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CUmaEvaluatorDlg::ReadSkillTSV()
{
	// スキル情報の読み込み
	wstring sImgDir = GetImgDir();
	wstring sSkillDir = sImgDir + L"skills\\";
	wstring sFileTSV = sSkillDir + L"skills.txt";
	wifstream ifs(sFileTSV);

	auto Loc = locale("Japanese");
	auto L = ifs.imbue(Loc);

	m_skills.clear();

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

		wstring sFilePNG = sSkillDir + to_wstring(skill.idx) + L".png";
		skill.img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

		m_skills.push_back(skill);
	}

	ifs.imbue(L);
	ifs.close();
}

void CUmaEvaluatorDlg::ReadSkillLv()
{
	m_skillLv.clear();

	// スキルレベル画像の読み込み
	wstring sImgDir = GetImgDir();
	wstring sSkillDir = sImgDir + L"skills\\";

	for (int i = 0; i < 6; ++i) {
		wstring si = to_wstring(i);
		wstring sFilePNG = sSkillDir + L"Lv" + si + L".png";
		cv::Mat img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
		m_skillLv.push_back(img);
	}
}

void CUmaEvaluatorDlg::ReadUniqLv()
{
	m_uniqLv.clear();

	// 固有スキルレベル画像の読み込み
	wstring sImgDir = GetImgDir();
	wstring sSkillDir = sImgDir + L"skills\\";

	for (int i = 0; i < 6; ++i) {
		wstring si = to_wstring(i+1);
		wstring sFilePNG = sSkillDir + L"uniqLv" + si + L".png";
		cv::Mat img = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));
		m_uniqLv.push_back(img);
	}
}

void CUmaEvaluatorDlg::ReadStatusPointTSV()
{
	m_vnStatusPoint.resize(1201);

	wstring sImgDir = GetImgDir();
	wstring sFileTSV = sImgDir + L"status_point.txt";
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

		if (0 <= i && i <= 1200) {
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

double MatchImageRel(const cv::Mat& img, const cv::Mat& img_ref)
{
	cv::Mat result;
	cv::matchTemplate(img, img_ref, result, cv::TM_CCORR_NORMED);

	double dMin, dMax;
	cv::minMaxLoc(result, &dMin, &dMax);
	return dMax;
}

bool CUmaEvaluatorDlg::MatchImage(const cv::Mat& img, const cv::Mat& img_ref, double crit) const
{
	double d = MatchImageRel(img, img_ref);
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

int CUmaEvaluatorDlg::GetImageSkillLv(const cv::Mat& img) const
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

	return iMax;
}

int CUmaEvaluatorDlg::GetImageUniqLv(const cv::Mat& img) const
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

int CUmaEvaluatorDlg::GetImageSkill(const cv::Mat& img) const
{
	cv::Mat img_title(img, cv::Rect(60, 5, 100, 15));

	double dMax = 0.0;
	int iMax = -1;
	for (int i = 0; i < m_skills.size(); ++i) {
		if (m_skills[i].img.empty())
			continue;
		cv::Mat img_title_ref(m_skills[i].img, cv::Rect(60, 5, 100, 15));
		double d = MatchImageRel(img_title, img_title_ref);
		if (d > max(dMax, 0.98) ) {
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
	for (int i = 0; i < 5; ++i) {
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

	for (int i = 0; i < 5; ++i) {
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
	const int DEFAULT_WIDTH = 450;
	const int DEFAULT_HEIGHT = 800;

	wstring sBinDir = GetExeDir();
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

				cv::Mat img_UniqLv(img_finish, cv::Rect(195, 440, 25, 15));

				int n = GetImageUniqLv(img_UniqLv);
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

			vector<pair<cv::Mat, bool> > vImages = GetSkillImages(img_finish);

			for (int i = 0; i < vImages.size(); ++i) {

				const cv::Mat& img_skill_frame = vImages[i].first;
				cv::Mat img_skill(img_skill_frame, cv::Rect(5, 5, 280, 90));

				int iSkill = GetImageSkill(img_skill);
				if (iSkill < 0)
					continue;

				cv::Mat img_Lv(img_skill_frame, cv::Rect(365, 2, 10, 15));
				int iLv = GetImageSkillLv(img_Lv);

				bool bFound = false;
				for (int j = 0; j < m_vSkillItems.size(); ++j) {
					if (m_vSkillItems[j].iSkill == iSkill) {
						bFound = true;
						break;
					}
				}
				if (!bFound) {
					m_vSkillItems.push_back(CSkillItem(iSkill, iLv));
				}
			}
			UpdateSkillList();
		}
	}
}

int CUmaEvaluatorDlg::GetSkillObtainPt(const CSkillItem& skillItem) const
{
	int iSkill = skillItem.iSkill;
	int iLv = skillItem.iLv;
	const CSkill& skill = m_skills[skillItem.iSkill];
	int nPt = skill.nPt;
	if (iLv == 1) nPt = int(nPt * 0.9);
	if (iLv == 2) nPt = int(nPt * 0.8);
	if (iLv == 3) nPt = int(nPt * 0.7);
	if (iLv == 4) nPt = int(nPt * 0.65);
	if (iLv == 5) nPt = int(nPt * 0.6);

	if( m_checkKiremono.GetCheck() == BST_CHECKED ) {
		nPt -= int(skill.nPt * 0.1);
	}

	return nPt;
}

int CUmaEvaluatorDlg::GetEvalOfSkill(const CSkill& skill) const
{
	int nEval = skill.nEval;
	if (skill.tekisei == SKILL_TEKISEI_NONE)
		return nEval;

	const CComboBox* combos[SKILL_TEKISEI_SIZE] = {
		NULL, &m_comboTurf,& m_comboDart,
		&m_comboShort, &m_comboMile, &m_comboMiddle, &m_comboLong,
		&m_comboNige, &m_comboSenkou, &m_comboSashi, &m_comboOikomi
	};
	int iSel = -1;
	for (int j = SKILL_TEKISEI_SHORT; j < SKILL_TEKISEI_SIZE; ++j) {
		if (skill.tekisei == j) iSel = combos[j]->GetCurSel();
	}
	double d = 1.0;
	switch (iSel) {
	case 0:
	case 1:
		d =  1.1;
		break;
	case 2:
	case 3:
		d = 0.9;
		break;
	case 4:
	case 5:
	case 6:
		d = 0.8;
		break;
	case 7:
		d = 0.7;
		break;
	}

	return int(round(nEval * d));
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
		int iSkill = m_vSkillItems[i].iSkill;
		int iLv = m_vSkillItems[i].iLv;
		const CSkill& skill = m_skills[iSkill];
		const wstring& wsName = skill.sName;

		int nPt = GetSkillObtainPt(m_vSkillItems[i]);

		wstring wsTekisei = skill.GetTekiseiStr();
		wsTekisei = wsTekisei.substr(0, 1);
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

	wstring sBinDir = GetExeDir();
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

		wstring sSkillDir = sImgDir + L"skills\\";
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
		++iCandidate;
		m_vSkillItems[i].bSelected = (siSelected.find(iCandidate) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	if (pLVKeyDow->wVKey == VK_DELETE)
	{
		vector<CSkillItem> skillsNew;
		for (int i = 0; i < m_vSkillItems.size(); ++i) {
			if (m_vSkillItems[i].bObtain || !m_vSkillItems[i].bSelected) {
				skillsNew.push_back(m_vSkillItems[i]);
			}
		}
		m_vSkillItems = skillsNew;

		UpdateSkillList();
		UpdateEval();
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonToObtain()
{
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
		++iObtain;
		m_vSkillItems[i].bSelected = (siSelected.find(iObtain) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonToCandidate()
{
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

	if (nEvalStatusUniq > -1 && nEvalSkill > -1) {
		int nEvalTotal = nEvalStatusUniq + nEvalSkill;
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

		if (0 < n && n <= 1200) {
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
		int iSkill = m_vSkillItems[i].iSkill;
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
