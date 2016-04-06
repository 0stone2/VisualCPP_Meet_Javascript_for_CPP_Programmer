
// JsSampleDlg.cpp : 구현 파일
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
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CJsSampleDlg 대화 상자



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


// CJsSampleDlg 메시지 처리기

BOOL CJsSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CJsSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
int cxIcon = GetSystemMetrics(SM_CXICON);
int cyIcon = GetSystemMetrics(SM_CYICON);
CRect rect;
GetClientRect(&rect);
int x = (rect.Width() - cxIcon + 1) / 2;
int y = (rect.Height() - cyIcon + 1) / 2;

// 아이콘을 그립니다.
dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		nError = JsPointerToString(L"self", wcslen(L"self"), &(argument_1[0]));	// 모든 함수의 첫번째 인자는 항상 thisArg다

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

		// 함수의 리턴값 확인하기
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


		// 함수의 리턴값 확인하기
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

		// 함수의 리턴값 확인하기
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
