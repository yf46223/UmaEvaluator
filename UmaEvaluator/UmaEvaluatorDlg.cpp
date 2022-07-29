
// UmaEvaluatorDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "UmaEvaluator.h"
#include "UmaEvaluatorDlg.h"
#include "afxdialogex.h"
#include <winuser.h>
#include <string>

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
	: CDialogEx(IDD_UMAEVALUATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUmaEvaluatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SKILL, m_listSkills);
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
}

BEGIN_MESSAGE_MAP(CUmaEvaluatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CUmaEvaluatorDlg::OnBnClickedButtonDetect)
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

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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

	double d;
	cv::minMaxLoc(result, &d);
	return d;
}

bool CUmaEvaluatorDlg::MatchImage(const cv::Mat& img, const cv::Mat& img_ref)
{
	double d = MatchImageRel(img, img_ref);
	return (d > 0.99);
}


string GetExeDir()
{
	TCHAR path[MAX_PATH];
	if (!::GetModuleFileName(NULL, path, MAX_PATH))
		return "";

	CString csPath = path;
	string sPath = CStringA(csPath).GetBuffer();

	const size_t i = sPath.rfind('\\');
	if (string::npos == i)
		return "";

	string sDir = sPath.substr(0, i+1);

	return sDir;
}

int GetTekisei(const cv::Mat img_ref[8], const cv::Mat& img)
{
	double dMax = DBL_MIN;
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

int GetNumberOCR(const cv::Mat& img)
{
	string sBinDir = GetExeDir();

	static auto ocr = cv::text::OCRTesseract::create((sBinDir + "tessdata-4.1.0").c_str(), "eng", "0123456789");

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

void CUmaEvaluatorDlg::OnBnClickedButtonDetect()
{
	const int DEFAULT_WIDTH = 450;
	const int DEFAULT_HEIGHT = 800;

	string sBinDir = GetExeDir();
	string sImgDir = sBinDir + "img\\";

	/*
	cv::Mat img = GetUmaWindowImage();
	if (img.empty())
		return;

	//cv::Mat img = cv::imread(sImgDir + "UMPD-MatikaneTannhauser-MNT03.jpg");

	cv::Mat img_resize;
	cv::resize(img, img_resize, cv::Size(DEFAULT_WIDTH, DEFAULT_HEIGHT));

	cv::imwrite(sImgDir + "skill_bakushin.png", img_resize);

	return;
	*/

	cv::Mat img_finish = cv::imread(sImgDir + "skill_bakushin2.png");
	//cv::Mat img_finish = cv::imread(sImgDir + "finish_spe.png");

	// 育成完了確認
	cv::Mat img_kanryou_kakunin(img_finish, cv::Rect(15, 5, 90, 15));
	cv::Mat img_kanryou_kakunin_ref = cv::imread(sImgDir + "kanryou_kakunin.png");

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
		cv::Mat img_status_ref = cv::imread(sImgDir + "status.png");

		if (MatchImage(img_status, img_status_ref)) {
			cv::Mat img_status_detail(img_finish, cv::Rect(240, 240, 70, 110));
			cv::Mat img_status_detail_ref = cv::imread(sImgDir + "status_detail.png");

			if (MatchImage(img_status_detail, img_status_detail_ref)) {

				CEdit* edits[5] = { &m_editSpeed, &m_editStamina, &m_editPower, &m_editKonjou, &m_editKashikosa };
				int RECT_TOP[5] = { 232, 255, 279, 302, 326 };

				for (int i = 0; i < 5; ++i) {
					cv::Rect rect(345, RECT_TOP[i], 60, 28);

					cv::Mat img(img_finish, rect);

					int n = GetNumberOCR(img);

					CString cs;
					cs.Format(_T("%d"), n);
					edits[i]->SetWindowTextW(cs);
				}
			}

			CComboBox* combos[10] = {
				&m_comboTurf, &m_comboDart,
				&m_comboShort, &m_comboMile, &m_comboMiddle, &m_comboLong,
				&m_comboNige, &m_comboSenkou, &m_comboSashi, &m_comboOikomi
			};

			int RECT_RIGHT[2] = { 343, 413 };
			int RECT_TOP[5] = { 373, 401, 423, 455, 477 };

			const string TEKISEI[8] = { "S", "A", "B", "C", "D", "E", "F", "G" };

			cv::Mat img_tekisei[8];
			for (int i = 0; i < 8; ++i) {
				string sRefFile = sImgDir + TEKISEI[i] + ".png";
				img_tekisei[i] = cv::imread(sRefFile);
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
		cv::Mat img_skill_select_ref = cv::imread(sImgDir + "skill_select.png");

		// スキル取得
		if (MatchImage(img_skill_select, img_skill_select_ref)) {
			cv::Mat img_skill_pt(img_finish, cv::Rect(330, 250, 70, 25));

			int n = GetNumberOCR(img_skill_pt);
			CString cs;
			cs.Format(_T("%d"), n);
			((CEdit*)GetDlgItem(IDC_EDIT_SKILL_PT))->SetWindowText(cs);

			cv::Mat img_plus(img_finish, cv::Rect(390, 320, 35, 350));
			cv::Mat img_plus_ref = cv::imread(sImgDir + "plus.png");

			vector<int> viPlusY;

			for (int i = 0; i < 5; ++i) {
				cv::Mat result;
				cv::matchTemplate(img_plus, img_plus_ref, result, cv::TM_CCORR_NORMED);

				double d;
				cv::Point p;
				cv::minMaxLoc(result, NULL, &d, NULL, &p);

				if (d < 0.99)
					break;

				viPlusY.push_back(p.y);

				cv::Point p1(35, p.y + 35);
				cv::rectangle(img_plus, p, p1, cv::Scalar(0, 0, 0), cv::FILLED);
			}
		}
	}
}
