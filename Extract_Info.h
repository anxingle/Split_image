
// Extract_Info.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExtract_InfoApp: 
// �йش����ʵ�֣������ Extract_Info.cpp
//

class CExtract_InfoApp : public CWinApp
{
public:
	CExtract_InfoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExtract_InfoApp theApp;