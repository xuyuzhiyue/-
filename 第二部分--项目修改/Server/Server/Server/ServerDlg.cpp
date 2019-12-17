// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 对话框




CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strServerName = _T("");
	m_nServerPort = 0;
	m_strToClient = _T("");
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	DDX_Text(pDX, IDC_EDIT_TOCLIENT, m_strToClient);
	//  DDX_Control(pDX, IDC_LIST_RECEIVED, m_listSent);
	//  DDX_Control(pDX, IDC_LIST_SENT, m_listReceived);
	DDX_Control(pDX, IDC_LIST_SENT, m_listSent);
	DDX_Control(pDX, IDC_LIST_RECEIVED, m_listReceived);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CServerDlg::OnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSELISTEN, &CServerDlg::OnClickedButtonCloselisten)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CServerDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CServerDlg::OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON1_CLOSE, &CServerDlg::OnBnClickedButton1Close)
	
	
	ON_BN_CLICKED(IDC_LIULAN, &CServerDlg::OnBnClickedLiulan)
	ON_BN_CLICKED(IDC_BUTTON3, &CServerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_strServerName = "localhost";
	m_nServerPort = 1024;
	UpdateData(FALSE);
	m_sServerSocket.setParentDlg(this);
	m_sClientSocket.setParentDlg(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerDlg::OnClickedButtonCloselisten()
{
	// TODO: 在此添加控件通知处理程序代码
	onClose();
}

void CServerDlg::OnClickedButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN) -> EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME) -> EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT) -> EnableWindow(FALSE);
	m_sServerSocket.Create(m_nServerPort);
	m_sServerSocket.Listen();

	GetDlgItem(IDC_EDIT_TOCLIENT) ->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN) ->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND) ->EnableWindow(TRUE);
}

void CServerDlg::OnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	int nMsgLen;
	int nSentLen;
	UpdateData(TRUE);
	if(!m_strToClient.IsEmpty())
	{
		nMsgLen = m_strToClient.GetLength() * sizeof(m_strToClient);
		nSentLen = m_sClientSocket.Send(m_strToClient,nMsgLen);
		if(nSentLen != SOCKET_ERROR){
			m_listSent.AddString(m_strToClient);
			UpdateData(FALSE);
		}else{
			AfxMessageBox(LPCTSTR("服务器向客户机发送信息出现错误！"),MB_OK|MB_ICONSTOP);
		}
		m_strToClient.Empty();
		UpdateData(FALSE);
	}
}

void CServerDlg::onClose(void)
{
	m_listReceived.AddString(CString("服务器收到了OnClose信息"));
	m_sClientSocket.Close();
	m_sServerSocket.Close();

	GetDlgItem(IDC_EDIT_TOCLIENT) ->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN) ->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND) ->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME) -> EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT) -> EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN) -> EnableWindow(TRUE);
}
void CServerDlg::onAccept(void)
{
	m_listReceived.AddString(CString("服务器收到了OnAccept信息"));
	m_sServerSocket.Accept(m_sClientSocket);
	GetDlgItem(IDC_EDIT_TOCLIENT) -> EnableWindow(TRUE);	
	GetDlgItem(IDC_BUTTON_SEND) -> EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSELISTEN) -> EnableWindow(TRUE);
	
}

void CServerDlg::onReceived(void)
{
	TCHAR buff[4096];
	int nBufferSize=4096;
	int nReceivedLen;
	CString strReceived;

	m_listReceived.AddString(CString("服务器收到了OnReceived信息"));
	nReceivedLen=m_sClientSocket.Receive(buff,nBufferSize);
	if(nReceivedLen != SOCKET_ERROR)
	{
		buff[nReceivedLen] = _T('\0');
		CString szTemp(buff);
		strReceived=szTemp;
		m_listReceived.AddString(strReceived);
		UpdateData(FALSE);
	}else{
		AfxMessageBox(LPCTSTR("客户机从服务器接收信息出现错误！"),MB_OK | MB_ICONSTOP);
	}
}

void CServerDlg::OnBnClickedButtonRemove()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_TOCLIENT)->SetWindowText(_T(""));
	
}


void CServerDlg::OnBnClickedButton1Close()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(1); 
}


void CServerDlg::OnBnClickedButtonQuestion()
{
	// TODO: 在此添加控件通知处理程序代码
	system("start explorer http://www.baidu.com");
}




void CServerDlg::OnBnClickedLiulan()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open_img(TRUE,
						NULL, 
						NULL,
						OFN_OVERWRITEPROMPT,
						_T("图片文件(*.png; *.jpg; *.jpeg)|*.png; *.jpg; *.jpeg|bmp文件(*.bmp)|*.bmp||"),//指定要打开的文件类型
						NULL);
	if(open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_EDIT_TOCLIENT, img_select);//img_select为选择的文件的路径，IDC_IMGSELECTEDIT为edit控件名称


}

}

void CServerDlg::OnBnClickedButton3()
{
		// TODO: Add your control notification handler code here
	CFileDialog filedlg(false);        					//定义文件对话框对象
//filedlg.m_ofn.lpstrFileTitle="我是谁";				//在对话框中显示接收到的文件名
filedlg.DoModal();	
}
