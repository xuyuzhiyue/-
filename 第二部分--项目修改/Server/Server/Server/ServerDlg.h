// ServerDlg.h : 头文件
//

#pragma once
#include "ServerSocket.h"


// CServerDlg 对话框
class CServerDlg : public CDialogEx
{
// 构造
public:
	CServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strServerName;
	int m_nServerPort;
	CString m_strToClient;
//	CListBox m_listReceived;
//	CListBox m_listSent;
	afx_msg void OnClickedButtonCloselisten();
	afx_msg void OnClickedButtonListen();
	afx_msg void OnClickedButtonSend();
	CServerSocket m_sServerSocket;
	CServerSocket m_sClientSocket;
	void onClose(void);
	void onAccept(void);
	void onReceived(void);
	CListBox m_listSent;
	CListBox m_listReceived;
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnBnClickedButton1Close();
	afx_msg void OnBnClickedButtonQuestion();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedLiulan();
	afx_msg void OnBnClickedButton3();
};
