
// JsSample.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CJsSampleApp:
// �� Ŭ������ ������ ���ؼ��� JsSample.cpp�� �����Ͻʽÿ�.
//

class CJsSampleApp : public CWinApp
{
public:
	CJsSampleApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CJsSampleApp theApp;