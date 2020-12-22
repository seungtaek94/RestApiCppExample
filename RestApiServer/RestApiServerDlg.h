
// RestApiServerDlg.h: 헤더 파일
//

#pragma once

// CRestApiServerDlg 대화 상자
class CRestApiServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CRestApiServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESTAPISERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnStartServer();


public:
	void display_json(json::value const& jvalue, utility::string_t const& prefix);
	void handle_get(http_request request);
	void handle_request(http_request request, function<void(json::value const&, json::value&)> action);
	void handle_post(http_request request);
	void handle_put(http_request request);
	void handle_del(http_request request);

	CWinThread* m_pServerThread;
	static UINT ServerThread(LPVOID _pMain);
	void SetListenThread();
	void Listener();

	void DisplayOutput(CString taskType, utility::string_t key, utility::string_t value);
	CEdit m_editAddress;
};
