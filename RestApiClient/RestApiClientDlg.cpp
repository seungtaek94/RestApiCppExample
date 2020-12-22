
// RestApiClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RestApiClient.h"
#include "RestApiClientDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CRestApiClientDlg 대화 상자



CRestApiClientDlg::CRestApiClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESTAPICLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRestApiClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PUT_KEY, m_editPutKey);
	DDX_Control(pDX, IDC_EDIT_PUT_VALUE, m_editPutValue);
	DDX_Control(pDX, IDC_EDIT_DELETE_KEY, m_editDelKey);
	DDX_Control(pDX, IDC_EDIT_POST_KEY, m_editPostKey);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
}

BEGIN_MESSAGE_MAP(CRestApiClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_POST, &CRestApiClientDlg::OnBnClickedBtnPost)
	ON_BN_CLICKED(IDC_BTN_GET, &CRestApiClientDlg::OnBnClickedBtnGet)
	ON_BN_CLICKED(IDC_BTN_PUT, &CRestApiClientDlg::OnBnClickedBtnPut)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CRestApiClientDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CRestApiClientDlg 메시지 처리기

BOOL CRestApiClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_editAddress.SetWindowText(L"http://localhost:9090");
	m_editPostKey.SetWindowText(L"CAM");
	m_editPutKey.SetWindowText(L"CAM");
	m_editPutValue.SetWindowText(L"0");
	m_editDelKey.SetWindowText(L"CAM");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRestApiClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRestApiClientDlg::OnPaint()
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
HCURSOR CRestApiClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRestApiClientDlg::display_json(json::value const& jvalue, utility::string_t const& prefix)
{
	//wcout << prefix << jvalue.serialize() << endl;
	CString _key = prefix.c_str();
	CString _value = jvalue.serialize().c_str();
	OutputDebugString(_key + _value + L"\n");
}

pplx::task<http_response> CRestApiClientDlg::make_task_request(http_client& client, method mtd, json::value const& jvalue)
{
	return (mtd == methods::GET || mtd == methods::HEAD) ?
		client.request(mtd, L"/restdemo") :
		client.request(mtd, L"/restdemo", jvalue);
}

void CRestApiClientDlg::make_request(http_client& client, method mtd, json::value const& jvalue)
{
	make_task_request(client, mtd, jvalue)
		.then([=](http_response response)
			{
				if (response.status_code() == status_codes::OK)
				{
					return response.extract_json();
				}
				return pplx::task_from_result(json::value());
			}
		)
		.then([=](pplx::task<json::value> previousTask)
			{
				try
				{
					display_json(previousTask.get(), L"RESPONSE: ");
				}
				catch (http_exception const& e)
				{
					wcout << e.what() << endl;
				}
			}
		)
		.wait();
}


// POST - 해당 키를 가진 리소스를 생성, 값(Value)는 없음
void CRestApiClientDlg::OnBnClickedBtnPost()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString address;
	m_editAddress.GetWindowText(address);
	utility::string_t _address(address);

	http_client client(_address);

	auto getvalue = json::value::array();
	
	CString key;
	m_editPutKey.GetWindowText(key);
	utility::string_t _key(key);

	getvalue[0] = json::value::string(_key);
	
	//getvalue[0] = json::value::string(L"one");
	//getvalue[1] = json::value::string(L"two");
	//getvalue[2] = json::value::string(L"three");

	OutputDebugString(L"\nPOST (get some values)\n");
	display_json(getvalue, L"SEND: ");
	make_request(client, methods::POST, getvalue);
}

// GET - 리소스 조회
// 모든 리소스 서버로부터 key, value를 얻어옴.
void CRestApiClientDlg::OnBnClickedBtnGet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString address;
	m_editAddress.GetWindowText(address);
	utility::string_t _address(address);

	http_client client(_address);

	auto nullvalue = json::value::null();

	OutputDebugString(L"\nGET (get all values)\n");
	display_json(nullvalue, L"SEND: ");
	make_request(client, methods::GET, nullvalue);
}

// PUT - 리소스 수정
// 현재 없는 리소스라면 생성 및 값 할당.
// 있는 리소스라면 값 업데이트
void CRestApiClientDlg::OnBnClickedBtnPut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString address;
	m_editAddress.GetWindowText(address);
	utility::string_t _address(address);

	http_client client(_address);

	auto putvalue = json::value::object();
	CString key;
	CString value;

	m_editPutKey.GetWindowText(key);
	m_editPutValue.GetWindowText(value);

	utility::string_t _value(value);
	utility::string_t _key(key);
	
	putvalue[_key] = json::value::string(_value);

	//아래와 같이 key, value 쌍만 주어준다면 배열로 한번에 Request 가능.
	//putvalue[L"one"] = json::value::string(L"100");
	//putvalue[L"two"] = json::value::string(L"200");

	OutputDebugString(L"\nPUT (add values)\n");
	display_json(putvalue, L"SEND: ");
	make_request(client, methods::PUT, putvalue);
}

// DELETE - 리소스 제거
void CRestApiClientDlg::OnBnClickedBtnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString address;
	m_editAddress.GetWindowText(address);
	utility::string_t _address(address);

	http_client client(_address);

	auto delvalue = json::value::array();
	//delvalue[0] = json::value::string(L"one");

	CString key;
	m_editDelKey.GetWindowText(key);
	utility::string_t _key(key);

	delvalue[0] = json::value::string(_key);

	OutputDebugString(L"\nDELETE (delete values)\n");
	display_json(delvalue, L"SEND: ");
	make_request(client, methods::DEL, delvalue);
}
