
// GraphLab1.h : GraphLab1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGraphLab1App:
// �йش����ʵ�֣������ GraphLab1.cpp
//

class CGraphLab1App : public CWinApp
{
public:
	CGraphLab1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGraphLab1App theApp;
