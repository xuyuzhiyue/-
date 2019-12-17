
// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CClientDlg �Ի���




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strServerName = _T("");
	m_nServerPort = 0;
	m_strToServer = _T("");
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_strServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_nServerPort);
	DDV_MinMaxInt(pDX, m_nServerPort, 1024, 49151);
	//  DDX_Text(pDX, IDC_EDIT_TOSERVER, m_strtoServer);
	DDX_Text(pDX, IDC_EDIT_TOSERVER, m_strToServer);
	DDX_Control(pDX, IDC_LIST_SENT, m_listSent);
	DDX_Control(pDX, IDC_LIST_RECEIVED, m_listReceived);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CClientDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CClientDlg::OnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CClientDlg::OnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, &CClientDlg::OnBnClickedButtonRemove)
	
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_strServerName="localhost";
	m_nServerPort=1024;
	UpdateData(FALSE);
	m_sClientSocket.setParentDlg(this);
	GetDlgItem(IDC_EDIT_TOSERVER) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND) -> EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_SERVERNAME) -> EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT) -> EnableWindow(FALSE);
	m_sClientSocket.Create();
	m_sClientSocket.Connect(m_strServerName,m_nServerPort);
}


void CClientDlg::OnClickedButtonDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	onClose();
}


void CClientDlg::OnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nMsgLen;
	int nSentLen;
	UpdateData(TRUE);
	if(!m_strToServer.IsEmpty())
	{
		nMsgLen = m_strToServer.GetLength() * sizeof(m_strToServer);
		nSentLen = m_sClientSocket.Send(m_strToServer,nMsgLen);
		if(nSentLen != SOCKET_ERROR)
		{
			m_listSent.AddString(m_strToServer);
			UpdateData(FALSE);
		}else{
			AfxMessageBox(LPCTSTR("�ͻ����������������Ϣ���ִ���"),MB_OK | MB_ICONSTOP);
		}
		m_strToServer.Empty();
		UpdateData(FALSE);
	}
}

//�ͻ����Ѿ����ӵ���������
void CClientDlg::onConnect(void)
{
	GetDlgItem(IDC_EDIT_TOSERVER) -> EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DISCONNECT) -> EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND) -> EnableWindow(TRUE);
}

void CClientDlg::onReceived(void)
{
	TCHAR buff[4096];
	int nBufferSize=4096;
	int nReceivedLen;
	CString strReceived;

	nReceivedLen=m_sClientSocket.Receive(buff,nBufferSize);
	if(nReceivedLen !=SOCKET_ERROR)
	{
		buff[nReceivedLen]=_T('\0');
		CString szTemp(buff);
		strReceived=szTemp;
		m_listReceived.AddString(strReceived);
		UpdateData(FALSE);
	}else{
		AfxMessageBox(LPCTSTR("�ͻ����ӷ�����������Ϣ���ִ���"),MB_OK | MB_ICONSTOP);
	}
}

void CClientDlg::onClose(void)
{
	m_sClientSocket.Close();
	GetDlgItem(IDC_EDIT_TOSERVER) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND) -> EnableWindow(FALSE);

	//��������б���Ϣ
	while(m_listSent.GetCount()!=0){m_listSent.DeleteString(0);}
	while(m_listReceived.GetCount()!=0){m_listSent.DeleteString(0);}
	GetDlgItem(IDC_EDIT_SERVERNAME) -> EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME) -> EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT) -> EnableWindow(FALSE);
}

void CClientDlg::OnBnClickedButtonRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_TOSERVER)->SetWindowText(_T(""));

}


void CClientDlg::OnBnClickedButton1Close()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(1); 
}


void CClientDlg::OnBnClickedButtonQuestion()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	system("start explorer http://www.baidu.com");
}
