
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
}

BEGIN_MESSAGE_MAP(CUmaEvaluatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUmaEvaluatorDlg::OnBnClickedButton1)
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

	CString w, h;
	w.Format(_T("%d"), width);
	h.Format(_T("%d"), height);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText(w);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(h);

	POINT ppt;
	ppt.x = 0;
	ppt.y = 0;
	::ClientToScreen(hWindow, &ppt);

	cv::Mat desktop = GetDesktopImage();

	return cv::Mat(desktop, cv::Rect(ppt.x, ppt.y, width, height));
}

bool CUmaEvaluatorDlg::MatchImage(const cv::Mat& img, const cv::Mat& img_ref)
{
	cv::Mat result;
	cv::matchTemplate(img, img_ref, result, cv::TM_CCORR_NORMED);

	double d;
	cv::minMaxLoc(result, &d);
	return (d > 0.99);
}

void CUmaEvaluatorDlg::OnBnClickedButton1()
{
	const int DEFAULT_WIDTH  = 408;
	const int DEFAULT_HEIGHT = 725;
/*
	cv::Mat img = GetUmaWindowImage();
	if (img.empty()) 
		return;

	cv::Mat imgResize;
	cv::resize(img, imgResize, cv::Size(DEFAULT_WIDTH, DEFAULT_HEIGHT));

	cv::imwrite("C:\\tmp\\uma\\finish.jpg", img_resize);
*/

	cv::Mat img_finish = cv::imread("C:\\tmp\\uma\\finish.jpg");
	cv::Mat img_status(img_finish, cv::Rect(210, 165, 80, 20));

	cv::Mat img_status_ref = cv::imread("C:\\tmp\\uma\\status.jpg");

	if( MatchImage(img_status, img_status_ref) ) {
		cv::Mat img_turf (img_finish, cv::Rect(311, 338, 12, 13));
		cv::Mat img_dart (img_finish, cv::Rect(374, 338, 12, 13));
		cv::Mat img_short(img_finish, cv::Rect(311, 363, 12, 13));

		const std::string TEKISEI[8] = { "S", "A", "B", "C", "D", "E", "F", "G" };

		for (int i = 0; i < 8; ++i) {
			std::string sRefFile = "C:\\work\\uma\\UmaEvaluator\\x64\\Debug\\img\\" + TEKISEI[i] + ".jpg";
			cv::Mat img_tekisei = cv::imread(sRefFile.c_str());
			if (MatchImage(img_turf, img_tekisei)) {
				((CComboBox*)GetDlgItem(IDC_COMBO_TURF))->SetCurSel(i);
				break;
			}
		}

		for (int i = 0; i < 8; ++i) {
			std::string sRefFile = "C:\\work\\uma\\UmaEvaluator\\x64\\Debug\\img\\" + TEKISEI[i] + ".jpg";
			cv::Mat img_tekisei = cv::imread(sRefFile.c_str());
			if (MatchImage(img_dart, img_tekisei)) {
				((CComboBox*)GetDlgItem(IDC_COMBO_DART))->SetCurSel(i);
				break;
			}
		}
	}

}
