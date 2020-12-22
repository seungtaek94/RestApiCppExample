
// RestApiClientDlg.h: 헤더 파일
//

#pragma once


// CRestApiClientDlg 대화 상자
class CRestApiClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CRestApiClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESTAPICLIENT_DIALOG };
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
	void display_json(json::value const& jvalue, utility::string_t const& prefix);
	pplx::task<http_response> make_task_request(http_client& client, method mtd, json::value const& jvalue);
	void make_request(http_client& client, method mtd, json::value const& jvalue);

	afx_msg void OnBnClickedBtnPost();
	afx_msg void OnBnClickedBtnGet();
	afx_msg void OnBnClickedBtnPut();
	afx_msg void OnBnClickedBtnDelete();

	CEdit m_editPutValue;
	CEdit m_editPutKey;
	CEdit m_editDelKey;
	CEdit m_editPostKey;
	CEdit m_editAddress;
};
