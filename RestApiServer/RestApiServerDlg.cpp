
// RestApiServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RestApiServer.h"
#include "RestApiServerDlg.h"
#include "afxdialogex.h"

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


// CRestApiServerDlg 대화 상자



CRestApiServerDlg::CRestApiServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESTAPISERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRestApiServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
}

BEGIN_MESSAGE_MAP(CRestApiServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START_SERVER, &CRestApiServerDlg::OnBnClickedBtnStartServer)
END_MESSAGE_MAP()


// CRestApiServerDlg 메시지 처리기

BOOL CRestApiServerDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRestApiServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRestApiServerDlg::OnPaint()
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
HCURSOR CRestApiServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRestApiServerDlg::display_json(json::value const& jvalue, utility::string_t const& prefix)
{
	wcout << prefix << jvalue.serialize() << endl;
}

void CRestApiServerDlg::DisplayOutput(CString taskType, utility::string_t key, utility::string_t value)
{
	CString strFirst(key.c_str());
	CString strSecond(value.c_str());
	CString strDebug = taskType + L" (" + strFirst + L", " + strSecond + L")";
	OutputDebugString(strDebug);
}

void CRestApiServerDlg::handle_get(http_request request)
{
	OutputDebugString(L"\nhandle GET\n");

	auto answer = json::value::object();

	for (auto const& p : dictionary)
	{
		answer[p.first] = json::value::string(p.second);
	}

	display_json(json::value::null(), L"R: ");
	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
}

void CRestApiServerDlg::handle_request(http_request request, function<void(json::value const&, json::value&)> action)
{
	auto answer = json::value::object();

	request.extract_json()
		.then([=, &answer, &action](pplx::task<json::value> task) {
			try
			{
				auto const&  jvalue = task.get();
				display_json(jvalue , L"R: ");

				if (!jvalue.is_null())
				{
					action(jvalue, answer);
				}
			}
			catch (http_exception const& e)
			{
				wcout << e.what() << endl;
			}
		})
		.wait();


	display_json(answer, L"S: ");
	request.reply(status_codes::OK, answer);
}

void CRestApiServerDlg::handle_post(http_request request)
{
	OutputDebugString(L"\nhandle POST\n");

	handle_request(
		request,
		[=](json::value const& jvalue, json::value& answer)
		{
			for (auto const& e : jvalue.as_array())
			{
				if (e.is_string())
				{
					auto key = e.as_string();
					auto pos = dictionary.find(key);

					if (pos == dictionary.end())
					{
						answer[key] = json::value::string(L"<nil>");
					}
					else
					{
						answer[pos->first] = json::value::string(pos->second);
					}
				}
			}
		}
	);
}


void CRestApiServerDlg::handle_put(http_request request)
{
	OutputDebugString(L"\nhandle PUT\n");

	handle_request(
		request,
		[=](json::value const& jvalue, json::value& answer)
		{
			for (auto const& e : jvalue.as_object())
			{
				if (e.second.is_string())
				{
					auto key = e.first;
					auto value = e.second.as_string();

					if (dictionary.find(key) == dictionary.end())
					{
						//TRACE_ACTION(L"[added]", key, value);
						DisplayOutput(L"[added]", key, value);
						answer[key] = json::value::string(L"<put>");
					}
					else
					{
						//TRACE_ACTION(L"[updated]", key, value);
						DisplayOutput(L"[updated]", key, value);
						answer[key] = json::value::string(L"<updated>");
					}

					dictionary[key] = value;
				}
			}
		}
	);
}

void CRestApiServerDlg::handle_del(http_request request)
{
	OutputDebugString(L"\nhandle DEL\n");

	handle_request(
		request,
		[=](json::value const& jvalue, json::value& answer)
		{
			set<utility::string_t> keys;
			for (auto const& e : jvalue.as_array())
			{
				if (e.is_string())
				{
					auto key = e.as_string();

					auto pos = dictionary.find(key);
					if (pos == dictionary.end())
					{
						answer[key] = json::value::string(L"<failed>");
					}
					else
					{
						//TRACE_ACTION(L"[deleted]", pos->first, pos->second);
						DisplayOutput(L"[deleted]", pos->first, pos->second);

						answer[key] = json::value::string(L"<deleted>");
						keys.insert(key);
					}
				}
			}

			for (auto const& key : keys)
				dictionary.erase(key);
		}
	);
}

UINT CRestApiServerDlg::ServerThread(LPVOID _pMain)
{
	CRestApiServerDlg* pMainDlg = (CRestApiServerDlg*)_pMain;

	pMainDlg->Listener();

	return 0;
}

void CRestApiServerDlg::Listener()
{
	CString address;
	m_editAddress.GetWindowText(address);
	utility::string_t _address(address);
	http_listener listener(_address);

	listener.support(methods::GET, std::bind(&CRestApiServerDlg::handle_get, this, std::placeholders::_1));
	listener.support(methods::POST, std::bind(&CRestApiServerDlg::handle_post, this, std::placeholders::_1));
	listener.support(methods::PUT, std::bind(&CRestApiServerDlg::handle_put, this, std::placeholders::_1));
	listener.support(methods::DEL, std::bind(&CRestApiServerDlg::handle_del, this, std::placeholders::_1));	

	try
	{
		listener
			.open()
			.then([&listener]() {OutputDebugString(L"\nstarting to listen\n");})
			.wait();

		while (true);

		listener.close();
	}
	catch (exception const& e)
	{
		wcout << e.what() << endl;
	}
}

void CRestApiServerDlg::SetListenThread()
{
	m_pServerThread = AfxBeginThread(ServerThread, this);
}

void CRestApiServerDlg::OnBnClickedBtnStartServer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetListenThread();
}
