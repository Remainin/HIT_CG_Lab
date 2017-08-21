
// GraphLab1.h : GraphLab1 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CGraphLab1App:
// 有关此类的实现，请参阅 GraphLab1.cpp
//

class CGraphLab1App : public CWinApp
{
public:
	CGraphLab1App();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphLab1App theApp;
