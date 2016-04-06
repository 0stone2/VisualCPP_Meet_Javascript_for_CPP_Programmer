
// JsSampleDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "JsSample.h"
#include "JsSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "ChakraCore.h" //C:\Script\ChakraCore\lib\Jsrt
#pragma comment (lib, "C:/Script/ChakraCore/Build/VcBuild/bin/x86_release/ChakraCore.lib")


wchar_t * LoadJSFile(wchar_t *pszJSFile);
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CJsSampleDlg ��ȭ ����



CJsSampleDlg::CJsSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_JSSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJsSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJsSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CJsSampleDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CJsSampleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CJsSampleDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CJsSampleDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CJsSampleDlg �޽��� ó����

BOOL CJsSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CJsSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CJsSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
int cxIcon = GetSystemMetrics(SM_CXICON);
int cyIcon = GetSystemMetrics(SM_CYICON);
CRect rect;
GetClientRect(&rect);
int x = (rect.Width() - cxIcon + 1) / 2;
int y = (rect.Height() - cyIcon + 1) / 2;

// �������� �׸��ϴ�.
dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CJsSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



wchar_t * LoadJSFile(wchar_t *pszJSFile)
{
	BOOL bSuccess{ FALSE };
	wchar_t *pJSContents{ NULL };

	HANDLE	hJSFile{ INVALID_HANDLE_VALUE };
	DWORD	dwSize{ 0 };
	DWORD	NumberOfBytesRead{ 0 };

	__try {
		hJSFile = CreateFile(pszJSFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hJSFile) __leave;

		dwSize = GetFileSize(hJSFile, NULL);
		if (0 == dwSize) __leave;

		pJSContents = (wchar_t *)malloc(dwSize + 2);
		if (NULL == pJSContents) __leave;
		ZeroMemory(pJSContents, dwSize + 2);

		ReadFile(hJSFile, pJSContents, dwSize, &NumberOfBytesRead, NULL);
		if (NumberOfBytesRead != dwSize) __leave;

		bSuccess = TRUE;
	}
	__finally {
		if (INVALID_HANDLE_VALUE != hJSFile) CloseHandle(hJSFile);
		if (FALSE == bSuccess)
		{
			if (NULL != pJSContents) free(pJSContents);
		}
	}

	return pJSContents;
}

void CJsSampleDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bSuccess = FALSE;

	JsErrorCode nError;
	JsRuntimeHandle Runtime = JS_INVALID_RUNTIME_HANDLE;
	JsContextRef Context = JS_INVALID_REFERENCE;
	unsigned SourceContext = 0;

	wchar_t *pszScript = NULL;
	wchar_t *srcUri = L"";
	JsValueRef Result;

	__try {
		pszScript = LoadJSFile(L"./Script/Sample01.js");
		if (NULL == pszScript) __leave;

		JsCreateRuntime(JsRuntimeAttributeNone, NULL, &Runtime);
		if (JS_INVALID_RUNTIME_HANDLE == Runtime) __leave;

		JsCreateContext(Runtime, &Context);
		if (JS_INVALID_REFERENCE == Context) __leave;

		JsSetCurrentContext(Context);

		nError = JsRunScript(pszScript + 1, SourceContext++, srcUri, &Result);
		if (JsNoError != nError) __leave;

		bSuccess = TRUE;
	}
	__finally {
		if (NULL != pszScript) free(pszScript);

		if (JS_INVALID_RUNTIME_HANDLE != Runtime)
		{
			JsSetCurrentContext(JS_INVALID_REFERENCE);
			JsDisposeRuntime(Runtime);
		}
	
	}
}

void CJsSampleDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bSuccess = FALSE;

	JsErrorCode		nError;
	JsRuntimeHandle Runtime = JS_INVALID_RUNTIME_HANDLE;
	JsContextRef	Context = JS_INVALID_REFERENCE;
	unsigned		SourceContext = 0;

	wchar_t *		pszScript = NULL;
	wchar_t *		srcUri = L"";
	JsValueRef		Result;


	JsValueRef			GlobalObject;

	JsPropertyIdRef		WelcomMessage;
	JsValueType			WelcomMessage_Type;
	JsValueRef			WelcomMessage_Value;

	JsPropertyIdRef		WhoamI;
	JsValueType			WhoamI_Type;
	JsValueRef			WhoamI_Value;

	JsPropertyIdRef		Version;
	JsValueType			Version_Type;
	JsValueRef			Version_Value;

	size_t				nSize{ 0 };
	const wchar_t *		pszStringValue;
	int					nIntValue;

	wchar_t				szDbgString[MAX_PATH]{ 0, };

	__try {
		pszScript = LoadJSFile(L"./Script/Sample02.js");
		if (NULL == pszScript) __leave;

		JsCreateRuntime(JsRuntimeAttributeNone, NULL, &Runtime);
		if (JS_INVALID_RUNTIME_HANDLE == Runtime) __leave;

		JsCreateContext(Runtime, &Context);
		if (JS_INVALID_REFERENCE == Context) __leave;

		JsSetCurrentContext(Context);

		nError = JsRunScript(pszScript + 1, SourceContext++, srcUri, &Result);
		if (JsNoError != nError) __leave;



		nError = JsGetGlobalObject(&GlobalObject);

		nError = JsGetPropertyIdFromName(L"szWelcomMessage", &WelcomMessage);
		nError = JsGetProperty(GlobalObject, WelcomMessage, &WelcomMessage_Value);
		nError = JsGetValueType(WelcomMessage_Value, &WelcomMessage_Type);
		JsStringToPointer(WelcomMessage_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWelcomMessage = %s\n", pszStringValue);
		OutputDebugString(szDbgString);


		nError = JsGetPropertyIdFromName(L"szWhoamI", &WhoamI);
		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		nError = JsGetValueType(WhoamI_Value, &WhoamI_Type);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);


		JsPointerToString(L"New_Sample02.js", wcslen(L"New_Sample02.js"), &WhoamI_Value);
		nError = JsSetProperty(GlobalObject, WhoamI, WhoamI_Value, true);

		nError = JsGetPropertyIdFromName(L"szWhoamI", &WhoamI);
		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		nError = JsGetValueType(WhoamI_Value, &WhoamI_Type);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);


		nError = JsGetPropertyIdFromName(L"nVersion", &Version);
		nError = JsGetProperty(GlobalObject, Version, &Version_Value);
		nError = JsGetValueType(Version_Value, &Version_Type);
		JsNumberToInt(Version_Value, &nIntValue);
		swprintf_s(szDbgString, L"nVersion = %d\n", nIntValue);
		OutputDebugString(szDbgString);




		bSuccess = TRUE;
	}
	__finally {
		if (NULL != pszScript) free(pszScript);

		if (JS_INVALID_RUNTIME_HANDLE != Runtime)
		{
			JsSetCurrentContext(JS_INVALID_REFERENCE);
			JsDisposeRuntime(Runtime);
		}

	}
}


void CJsSampleDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bSuccess = FALSE;

	JsErrorCode		nError;
	JsRuntimeHandle Runtime = JS_INVALID_RUNTIME_HANDLE;
	JsContextRef	Context = JS_INVALID_REFERENCE;
	unsigned		SourceContext = 0;

	wchar_t *		pszScript = NULL;
	wchar_t *		srcUri = L"";
	JsValueRef		Result;



	JsValueRef			GlobalObject;

	JsPropertyIdRef		WelcomMessage;
	JsValueType			WelcomMessage_Type;
	JsValueRef			WelcomMessage_Value;

	JsPropertyIdRef		WhoamI;
	JsValueType			WhoamI_Type;
	JsValueRef			WhoamI_Value;

	size_t				nSize{ 0 };
	const wchar_t *		pszStringValue;

	wchar_t				szDbgString[MAX_PATH]{ 0, };

	__try {
		pszScript = LoadJSFile(L"./Script/Sample03.js");
		if (NULL == pszScript) __leave;

		JsCreateRuntime(JsRuntimeAttributeNone, NULL, &Runtime);
		if (JS_INVALID_RUNTIME_HANDLE == Runtime) __leave;

		JsCreateContext(Runtime, &Context);
		if (JS_INVALID_REFERENCE == Context) __leave;

		JsSetCurrentContext(Context);

		nError = JsRunScript(pszScript + 1, SourceContext++, srcUri, &Result);
		if (JsNoError != nError) __leave;




		nError = JsGetGlobalObject(&GlobalObject);


		nError = JsGetPropertyIdFromName(L"szWelcomMessage", &WelcomMessage);
		nError = JsGetProperty(GlobalObject, WelcomMessage, &WelcomMessage_Value);
		nError = JsGetValueType(WelcomMessage_Value, &WelcomMessage_Type);
		JsStringToPointer(WelcomMessage_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWelcomMessage = %s\n", pszStringValue);
		OutputDebugString(szDbgString);


		nError = JsGetPropertyIdFromName(L"szWhoamI", &WhoamI);
		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		nError = JsGetValueType(WhoamI_Value, &WhoamI_Type);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);


		////////////////////////////////////////////////////////////////////////////////////////
		//
		// myfunc_1
		// 
		OutputDebugString(L"\n\nfunction call : myfunc_1 \n");
		JsValueRef argument_1[1];
		nError = JsPointerToString(L"self", wcslen(L"self"), &(argument_1[0]));	// ��� �Լ��� ù��° ���ڴ� �׻� thisArg��

		JsPropertyIdRef		myfunc_1;
		JsValueType			myfunc_1_Type;
		JsValueRef			myfunc_1_Value;


		nError = JsGetPropertyIdFromName(L"myfunc_1", &myfunc_1);
		nError = JsGetProperty(GlobalObject, myfunc_1, &myfunc_1_Value);
		nError = JsGetValueType(myfunc_1_Value, &myfunc_1_Type);
		nError = JsCallFunction(myfunc_1_Value, argument_1, 1, &Result);

		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);

		////////////////////////////////////////////////////////////////////////////////////////
		//
		// myfunc_2
		// 
		OutputDebugString(L"\n\nfunction call : myfunc_2 \n");
		JsValueRef argument_2[1];
		nError = JsPointerToString(L"self", wcslen(L"self"), &(argument_2[0]));

		JsPropertyIdRef		myfunc_2;
		JsValueType			myfunc_2_Type;
		JsValueRef			myfunc_2_Value;


		nError = JsGetPropertyIdFromName(L"myfunc_2", &myfunc_2);
		nError = JsGetProperty(GlobalObject, myfunc_2, &myfunc_2_Value);
		nError = JsGetValueType(myfunc_2_Value, &myfunc_2_Type);
		nError = JsCallFunction(myfunc_2_Value, argument_2, 1, &Result);

		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);

		// �Լ��� ���ϰ� Ȯ���ϱ�
		JsStringToPointer(Result, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"return value = %s\n", pszStringValue);
		OutputDebugString(szDbgString);

		////////////////////////////////////////////////////////////////////////////////////////
		//
		// myfunc_3
		// 
		OutputDebugString(L"\n\nfunction call : myfunc_3 \n");
		JsValueRef argument_3[2];
		nError = JsPointerToString(L"self", wcslen(L"self"), &(argument_3[0]));
		nError = JsPointerToString(L"myfunc_3", wcslen(L"myfunc_3"), &(argument_3[1]));

		JsPropertyIdRef		myfunc_3;
		JsValueType			myfunc_3_Type;
		JsValueRef			myfunc_3_Value;


		nError = JsGetPropertyIdFromName(L"myfunc_3", &myfunc_3);
		nError = JsGetProperty(GlobalObject, myfunc_3, &myfunc_3_Value);
		nError = JsGetValueType(myfunc_3_Value, &myfunc_3_Type);
		nError = JsCallFunction(myfunc_3_Value, argument_3, 2, &Result);


		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);


		// �Լ��� ���ϰ� Ȯ���ϱ�
		JsValueType			Result_Type;
		JsValueRef			nIndex;
		JsValueRef			ReturnValue;
		bool				bSuccess{ false };

		nError = JsGetValueType(Result, &Result_Type);

		JsIntToNumber(0, &nIndex);
		nError = JsGetIndexedProperty(Result, nIndex, &ReturnValue);
		JsStringToPointer(ReturnValue, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"return value 1 = %s\n", pszStringValue);
		OutputDebugString(szDbgString);

		JsIntToNumber(1, &nIndex);
		nError = JsGetIndexedProperty(Result, nIndex, &ReturnValue);
		JsBooleanToBool(ReturnValue, &bSuccess);
		swprintf_s(szDbgString, L"return value 2 = %s\n", (true == bSuccess) ? L"true" : L"false");
		OutputDebugString(szDbgString);
		
		////////////////////////////////////////////////////////////////////////////////////////
		//
		// myfunc_4
		// 
		OutputDebugString(L"\n\nfunction call : myfunc_4 \n");
		JsValueRef argument_4[3];
		nError = JsPointerToString(L"self", wcslen(L"self"), &(argument_4[0]));
		nError = JsPointerToString(L"myfunc_4", wcslen(L"myfunc_4"), &(argument_4[1]));
		nError = JsBoolToBoolean(false, &(argument_4[2]));

		JsPropertyIdRef		myfunc_4;
		JsValueType			myfunc_4_Type;
		JsValueRef			myfunc_4_Value;


		nError = JsGetPropertyIdFromName(L"myfunc_4", &myfunc_4);
		nError = JsGetProperty(GlobalObject, myfunc_4, &myfunc_4_Value);
		nError = JsGetValueType(myfunc_4_Value, &myfunc_4_Type);
		nError = JsCallFunction(myfunc_4_Value, argument_4, 3, &Result);

		nError = JsGetProperty(GlobalObject, WhoamI, &WhoamI_Value);
		JsStringToPointer(WhoamI_Value, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"szWhoamI = %s\n", pszStringValue);
		OutputDebugString(szDbgString);

		// �Լ��� ���ϰ� Ȯ���ϱ�
		nError = JsGetValueType(Result, &Result_Type);

		JsIntToNumber(0, &nIndex);
		nError = JsGetIndexedProperty(Result, nIndex, &ReturnValue);
		JsStringToPointer(ReturnValue, &pszStringValue, &nSize);
		swprintf_s(szDbgString, L"return value 1 = %s\n", pszStringValue);
		OutputDebugString(szDbgString);

		JsIntToNumber(1, &nIndex);
		nError = JsGetIndexedProperty(Result, nIndex, &ReturnValue);
		JsBooleanToBool(ReturnValue, &bSuccess);
		swprintf_s(szDbgString, L"return value 2 = %s\n", (true == bSuccess) ? L"true" : L"false");
		OutputDebugString(szDbgString);


		bSuccess = TRUE;
	}
	__finally {
		if (NULL != pszScript) free(pszScript);

		if (JS_INVALID_RUNTIME_HANDLE != Runtime)
		{
			JsSetCurrentContext(JS_INVALID_REFERENCE);
			JsDisposeRuntime(Runtime);
		}

	}

}





JsValueRef CALLBACK DbgString(
	_In_ JsValueRef callee,
	_In_ bool isConstructCall,
	_In_ JsValueRef *arguments,
	_In_ unsigned short argumentCount,
	_In_opt_ void *callbackState)
{
	JsErrorCode		nError;
	int				nIndex{ 0 };
	JsValueRef		ReturnValue;
	JsValueType		ArgumentType;
	const wchar_t * pszDbgString;
	size_t			nSize;

	for (nIndex = 1; nIndex < argumentCount; nIndex++)
	{
		nError = JsGetValueType(arguments[nIndex], &ArgumentType);
		if (JsString == ArgumentType)
		{
			JsStringToPointer(arguments[nIndex], &pszDbgString, &nSize);
			if (nSize > 0)
				OutputDebugStringW(pszDbgString);
		}
	}

	return JS_INVALID_REFERENCE;
}

JsValueRef CALLBACK Sum(
	_In_ JsValueRef callee,
	_In_ bool isConstructCall,
	_In_ JsValueRef *arguments,
	_In_ unsigned short argumentCount,
	_In_opt_ void *callbackState)
{
	JsErrorCode		nError;
	int				nIndex{ 0 };

	JsValueRef		ReturnValue;
	JsValueType		ArgumentType;
	int				nSum{ 0 };
	int				nStart{ 0 };
	int				nEnd{ 0 };

	nError = JsGetValueType(arguments[1], &ArgumentType);
	if (JsNumber == ArgumentType)
	{
		JsNumberToInt(arguments[1], &nStart);
	}
	nError = JsGetValueType(arguments[2], &ArgumentType);
	if (JsNumber == ArgumentType)
	{
		JsNumberToInt(arguments[2], &nEnd);
	}

	if (nStart <= nEnd)
	{
		for (nIndex = nStart; nIndex <= nEnd; nIndex++)
		{
			nSum += nIndex;
		}
	}
	else
	{
		for (nIndex = nEnd; nIndex <= nStart; nIndex++)
		{
			nSum += nIndex;
		}
	}


	JsIntToNumber(nSum, &ReturnValue);
	return ReturnValue;
}

void CJsSampleDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL bSuccess = FALSE;

	JsErrorCode		nError;
	JsRuntimeHandle Runtime = JS_INVALID_RUNTIME_HANDLE;
	JsContextRef	Context = JS_INVALID_REFERENCE;
	unsigned		SourceContext = 0;

	JsValueRef		GlobalObject;
	JsValueRef		Function;
	JsValueRef		FunctionName;
	JsPropertyIdRef FunctionId;
	void *			callbackState = NULL;


	wchar_t *		pszScript = NULL;
	wchar_t *		srcUri = L"";
	JsValueRef		Result;

	__try {
		pszScript = LoadJSFile(L"./Script/Sample04.js");
		if (NULL == pszScript) __leave;

		JsCreateRuntime(JsRuntimeAttributeNone, NULL, &Runtime);
		if (JS_INVALID_RUNTIME_HANDLE == Runtime) __leave;

		JsCreateContext(Runtime, &Context);
		if (JS_INVALID_REFERENCE == Context) __leave;

		JsSetCurrentContext(Context);

		nError = JsGetGlobalObject(&GlobalObject);

		JsPointerToString(L"DbgString", wcslen(L"DbgString"), &(FunctionName));
		JsGetPropertyIdFromName(L"DbgString", &FunctionId);
		nError = JsCreateNamedFunction(FunctionName, (JsNativeFunction)DbgString, callbackState, &Function);
		JsSetProperty(GlobalObject, FunctionId, Function, true);

		JsPointerToString(L"Sum", wcslen(L"Sum"), &(FunctionName));
		JsGetPropertyIdFromName(L"Sum", &FunctionId);
		nError = JsCreateNamedFunction(FunctionName, (JsNativeFunction)Sum, callbackState, &Function);
		JsSetProperty(GlobalObject, FunctionId, Function, true);

		nError = JsRunScript(pszScript + 1, SourceContext++, srcUri, &Result);
		if (JsNoError != nError) __leave;

		bSuccess = TRUE;
	}
	__finally {
		if (NULL != pszScript) free(pszScript);

		if (JS_INVALID_RUNTIME_HANDLE != Runtime)
		{
			JsSetCurrentContext(JS_INVALID_REFERENCE);
			JsDisposeRuntime(Runtime);
		}

	}

}
