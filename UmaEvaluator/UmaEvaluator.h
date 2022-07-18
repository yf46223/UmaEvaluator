
// UmaEvaluator.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CUmaEvaluatorApp:
// このクラスの実装については、UmaEvaluator.cpp を参照してください
//

class CUmaEvaluatorApp : public CWinApp
{
public:
	CUmaEvaluatorApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CUmaEvaluatorApp theApp;
