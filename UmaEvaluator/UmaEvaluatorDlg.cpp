
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

	m_listCtrlSkillCandidate.InsertColumn(0, L"スキル名", LVCFMT_LEFT, 100);
	m_listCtrlSkillCandidate.InsertColumn(1, L"ヒントLv", LVCFMT_LEFT, 50);
	m_listCtrlSkillCandidate.InsertColumn(2, L"取得Pt"  , LVCFMT_LEFT, 50);
	m_listCtrlSkillCandidate.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_listCtrlSkillObtain.InsertColumn(0, L"スキル名", LVCFMT_LEFT, 100);
	m_listCtrlSkillObtain.InsertColumn(1, L"ヒントLv", LVCFMT_LEFT, 50);
	m_listCtrlSkillObtain.InsertColumn(2, L"取得Pt", LVCFMT_LEFT, 50);
	m_listCtrlSkillObtain.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	ReadSkillCSV();
	ReadSkillLv();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CUmaEvaluatorDlg::ReadSkillCSV()
{
	// スキル情報の読み込み
	wstring sImgDir = GetImgDir();
	wstring sSkillDir = sImgDir + L"skills\\";
	wstring sFileCSV = sSkillDir + L"skills.csv";
	wifstream ifs(sFileCSV);

	auto Loc = locale("Japanese");
	auto L = ifs.imbue(Loc);

	wstring line;
	while (getline(ifs, line)) {

		CSkill skill;

		wstringstream iss(line);
		wstring sIdx, sPt, sName;
		getline(iss, sIdx, L'\t');
		skill.idx = stoi(sIdx);
		getline(iss, sPt, L'\t');
		skill.nPt = stoi(sPt);
		getline(iss, sName, L'\t');
		skill.sName = sName;
		wstring sFilePNG = sSkillDir + sIdx + L".png";
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

void CUmaEvaluatorDlg::SaveSkillCSV()
{
	// スキル情報の書き込み
	wstring sImgDir = GetImgDir();
	wstring sSkillDir = sImgDir + L"skills\\";
	wstring sFileCSV = sSkillDir + L"skills.csv";
	wofstream ofs(sFileCSV);

	auto Loc = locale("Japanese");
	auto L = ofs.imbue(Loc);

	for (int i = 0; i < m_skills.size(); ++i) {
		const CSkill& skill = m_skills[i];
		ofs << skill.idx << "\t" << skill.nPt << "\t" << skill.sName << endl;
	}

	ofs.imbue(L);
	ofs.close();
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



cv::Mat CUmaEvaluatorDlg::GetDesktopImage()
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

cv::Mat CUmaEvaluatorDlg::GetUmaWindowImage()
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

bool CUmaEvaluatorDlg::MatchImage(const cv::Mat& img, const cv::Mat& img_ref, double crit)
{
	double d = MatchImageRel(img, img_ref);
	return (d > crit);
}



wstring CUmaEvaluatorDlg::GetExeDir()
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

int CUmaEvaluatorDlg::GetTekisei(const cv::Mat img_ref[8], const cv::Mat& img)
{
	double dMax = 0.0;
	int iMax = 9;
	for (int i = 0; i < 8; ++i) {
		double d = MatchImageRel(img, img_ref[i]);
		if (d > dMax) {
			dMax = d;
			iMax = i;
		}
	}

	return iMax;
}

int CUmaEvaluatorDlg::GetNumberOCR(const cv::Mat& img)
{
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

	int n = atoi(text.c_str());

	return n;
}

int CUmaEvaluatorDlg::GetImageLv(const cv::Mat& img)
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

int CUmaEvaluatorDlg::GetImageSkill(const cv::Mat& img)
{
	cv::Mat img_title(img, cv::Rect(60, 5, 100, 15));

	double dMax = 0.0;
	int iMax = -1;
	for (int i = 0; i < m_skills.size(); ++i) {
		cv::Mat img_title_ref(m_skills[i].img, cv::Rect(60, 5, 100, 15));
		double d = MatchImageRel(img_title, img_title_ref);
		if (d > max(dMax, 0.98) ) {
			dMax = d;
			iMax = i;
		}
	}

	return iMax;
}

vector<pair<cv::Mat, bool> > CUmaEvaluatorDlg::GetSkillImages(const cv::Mat img_finish)
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

CString CUmaEvaluatorDlg::WS2CS(const wstring& ws)
{
	CString cs;
	cs.Format(_T("%s"), ws.c_str());
	return cs;
}

CString CUmaEvaluatorDlg::Int2CS(int n)
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

	// 育成完了確認
	cv::Mat img_kanryou_kakunin(img_finish, cv::Rect(15, 5, 90, 15));
	wstring sFilePNG = sImgDir + L"kanryou_kakunin.png";
	cv::Mat img_kanryou_kakunin_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

	if (MatchImage(img_kanryou_kakunin, img_kanryou_kakunin_ref)) {

		// 星
		{
			int nStar = 0;
			int l = 35;
			for (int i = 0; i < 5; ++i) {
				cv::Vec3b pix = img_finish.at<cv::Vec3b>(cv::Point(l, 450));
				int b = pix[0];
				if (150 < b) break;
				++nStar;
				l += 25;
			}
			if (0 < nStar) {
				m_comboStar.SetCurSel(nStar - 1);
			}
		}

		// ステータス
		cv::Mat img_status(img_finish, cv::Rect(230, 180, 80, 20));
		wstring sFilePNG = sImgDir + L"status.png";
		cv::Mat img_status_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

		if (MatchImage(img_status, img_status_ref)) {
			cv::Mat img_status_detail(img_finish, cv::Rect(240, 240, 70, 110));
			wstring sFilePNG = sImgDir + L"status_detail.png";
			cv::Mat img_status_detail_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

			if (MatchImage(img_status_detail, img_status_detail_ref)) {

				CEdit* edits[5] = { &m_editSpeed, &m_editStamina, &m_editPower, &m_editKonjou, &m_editKashikosa };
				int RECT_TOP[5] = { 232, 255, 279, 302, 326 };

				for (int i = 0; i < 5; ++i) {
					cv::Rect rect(345, RECT_TOP[i], 60, 28);

					cv::Mat img(img_finish, rect);

					int n = GetNumberOCR(img);

					edits[i]->SetWindowTextW(Int2CS(n));
				}
			}

			CComboBox* combos[10] = {
				&m_comboTurf, &m_comboDart,
				&m_comboShort, &m_comboMile, &m_comboMiddle, &m_comboLong,
				&m_comboNige, &m_comboSenkou, &m_comboSashi, &m_comboOikomi
			};

			int RECT_RIGHT[2] = { 343, 413 };
			int RECT_TOP[5] = { 373, 401, 423, 455, 477 };

			const wstring TEKISEI[8] = { L"S", L"A", L"B", L"C", L"D", L"E", L"F", L"G" };

			cv::Mat img_tekisei[8];
			for (int i = 0; i < 8; ++i) {
				wstring sRefFile = sImgDir + TEKISEI[i] + L".png";
				img_tekisei[i] = cv::imread(string(sRefFile.begin(), sRefFile.end()));
			}

			for (int i = 0; i < 10; ++i) {
				int r = RECT_RIGHT[i % 2];
				int t = RECT_TOP[i / 2];
				cv::Mat img(img_finish, cv::Rect(r, t, 14, 14));
				int j = GetTekisei(img_tekisei, img);
				combos[i]->SetCurSel(j);
			}
		}
	}

	else {
		cv::Mat img_skill_select(img_finish, cv::Rect(0, 0, 100, 25));
		wstring sFilePNG = sImgDir + L"skill_select.png";
		cv::Mat img_skill_select_ref = cv::imread(string(sFilePNG.begin(), sFilePNG.end()));

		// スキル取得
		if (MatchImage(img_skill_select, img_skill_select_ref)) {

			cv::Mat img_skill_pt(img_finish, cv::Rect(330, 250, 70, 25));

			int n = GetNumberOCR(img_skill_pt);
			m_editSkillPt.SetWindowTextW(Int2CS(n));

			vector<pair<cv::Mat, bool> > vImages = GetSkillImages(img_finish);

			for (int i = 0; i < vImages.size(); ++i) {

				const cv::Mat& img_skill_frame = vImages[i].first;
				cv::Mat img_skill(img_skill_frame, cv::Rect(5, 5, 280, 90));

				int iSkill = GetImageSkill(img_skill);
				if (iSkill < 0)
					continue;

				cv::Mat img_Lv(img_skill_frame, cv::Rect(365, 2, 10, 15));
				int iLv = GetImageLv(img_Lv);

				bool bFound = false;
				for (int j = 0; j < m_vSkills.size(); ++j) {
					if (m_vSkills[j].iSkill == iSkill) {
						bFound = true;
						break;
					}
				}
				if (!bFound) {
					m_vSkills.push_back(CSkillItem(iSkill, iLv));
				}
			}
			UpdateSkillList();
		}
	}
}

void CUmaEvaluatorDlg::UpdateSkillList()
{
	m_bOnUpdateSkillList = true;

	m_listCtrlSkillCandidate.DeleteAllItems();
	m_listCtrlSkillObtain.DeleteAllItems();
	int iCandidate = 0;
	int iObtain = 0;
	for (int i = 0; i < m_vSkills.size(); ++i) {
		const CSkill& skill = m_skills[m_vSkills[i].iSkill];
		const wstring& ws = skill.sName;
		int iLv = m_vSkills[i].iLv;
		int nPt = skill.nPt;
		if (iLv == 1) nPt = int(nPt * 0.9);
		if (iLv == 2) nPt = int(nPt * 0.8);
		if (iLv == 3) nPt = int(nPt * 0.7);
		if (iLv == 4) nPt = int(nPt * 0.65);
		if (iLv == 5) nPt = int(nPt * 0.6);

		if (m_vSkills[i].bObtain) {
			m_listCtrlSkillObtain.InsertItem(iObtain, WS2CS(ws));
			m_listCtrlSkillObtain.SetItemText(iObtain, 1, Int2CS(iLv));
			m_listCtrlSkillObtain.SetItemText(iObtain, 2, Int2CS(nPt));
			if (m_vSkills[i].bSelected) {
				m_listCtrlSkillObtain.SetItemState(iObtain, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			}
			++iObtain;
		}
		else {
			m_listCtrlSkillCandidate.InsertItem(iCandidate, WS2CS(ws));
			m_listCtrlSkillCandidate.SetItemText(iCandidate, 1, Int2CS(iLv));
			m_listCtrlSkillCandidate.SetItemText(iCandidate, 2, Int2CS(nPt));
			if (m_vSkills[i].bSelected) {
				m_listCtrlSkillCandidate.SetItemState(iCandidate, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			}
			++iCandidate;
		}
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
		CSkill skill;
		skill.img = img_skill;

		if (dlg.Setup(skill)) {
			int kDup = -1;
			for (int k = 0; k < m_skills.size(); ++k) {
				if (m_skills[k].sName == skill.sName) {
					kDup = k;
					break;
				}
			}
			if (kDup > -1) {
				int n = MessageBox(L"同名のスキルが存在します。上書きしますか？", L"スキル登録", MB_YESNO);
				if (n != IDYES) {
					continue;
				}

				skill.idx = m_skills[kDup].idx;
				m_skills[kDup] = skill;
			}
			else {
				int idxMax = 0;
				for (int k = 0; k < m_skills.size(); ++k) {
					idxMax = max(idxMax, m_skills[k].idx);
				}
				skill.idx = idxMax + 1;

				m_skills.push_back(skill);
			}

			wstring sIdx = to_wstring(skill.idx);
			wstring sSkillDir = sImgDir + L"skills\\";
			wstring sFilePNG = sSkillDir + sIdx + L".png";
			cv::imwrite(string(sFilePNG.begin(), sFilePNG.end()), img_skill);

			SaveSkillCSV();
		}
	}
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
	for (int i = 0; i < m_vSkills.size(); ++i) {
		if (m_vSkills[i].bObtain)
			continue;
		++iCandidate;
		m_vSkills[i].bSelected = (siSelected.find(iCandidate) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnLvnKeydownListCtrlSkillCandidate(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);

	if (pLVKeyDow->wVKey == VK_DELETE)
	{
		vector<CSkillItem> skillsNew;
		for (int i = 0; i <  m_vSkills.size(); ++i) {
			if (m_vSkills[i].bObtain || !m_vSkills[i].bSelected) {
				skillsNew.push_back(m_vSkills[i]);
			}
		}
		m_vSkills = skillsNew;

		UpdateSkillList();
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonToObtain()
{
	for (int i = 0; i < m_vSkills.size(); ++i) {
		if (!m_vSkills[i].bObtain && m_vSkills[i].bSelected) {
			m_vSkills[i].bObtain = true;
		}
	}
	UpdateSkillList();
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
	for (int i = 0; i < m_vSkills.size(); ++i) {
		if (!m_vSkills[i].bObtain)
			continue;
		++iObtain;
		m_vSkills[i].bSelected = (siSelected.find(iObtain) != siSelected.end());
	}

	*pResult = 0;
}


void CUmaEvaluatorDlg::OnBnClickedButtonToCandidate()
{
	for (int i = 0; i < m_vSkills.size(); ++i) {
		if (m_vSkills[i].bObtain && m_vSkills[i].bSelected) {
			m_vSkills[i].bObtain = false;
		}
	}
	UpdateSkillList();
}
