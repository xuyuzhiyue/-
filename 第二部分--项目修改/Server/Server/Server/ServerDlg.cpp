// ServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
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


// CServerDlg �Ի���




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


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
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
	m_strServerName = "localhost";
	m_nServerPort = 1024;
	UpdateData(FALSE);
	m_sServerSocket.setParentDlg(this);
	m_sClientSocket.setParentDlg(this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerDlg::OnClickedButtonCloselisten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	onClose();
}

void CServerDlg::OnClickedButtonListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			AfxMessageBox(LPCTSTR("��������ͻ���������Ϣ���ִ���"),MB_OK|MB_ICONSTOP);
		}
		m_strToClient.Empty();
		UpdateData(FALSE);
	}
}

void CServerDlg::onClose(void)
{
	m_listReceived.AddString(CString("�������յ���OnClose��Ϣ"));
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
	m_listReceived.AddString(CString("�������յ���OnAccept��Ϣ"));
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

	m_listReceived.AddString(CString("�������յ���OnReceived��Ϣ"));
	nReceivedLen=m_sClientSocket.Receive(buff,nBufferSize);
	if(nReceivedLen != SOCKET_ERROR)
	{
		buff[nReceivedLen] = _T('\0');
		CString szTemp(buff);
		strReceived=szTemp;
		m_listReceived.AddString(strReceived);
		UpdateData(FALSE);
	}else{
		AfxMessageBox(LPCTSTR("�ͻ����ӷ�����������Ϣ���ִ���"),MB_OK | MB_ICONSTOP);
	}
}

void CServerDlg::OnBnClickedButtonRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_TOCLIENT)->SetWindowText(_T(""));
	
}


void CServerDlg::OnBnClickedButton1Close()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(1); 
}


void CServerDlg::OnBnClickedButtonQuestion()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	system("start explorer http://www.baidu.com");
}




void CServerDlg::OnBnClickedLiulan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog open_img(TRUE,
						NULL, 
						NULL,
						OFN_OVERWRITEPROMPT,
						_T("ͼƬ�ļ�(*.png; *.jpg; *.jpeg)|*.png; *.jpg; *.jpeg|bmp�ļ�(*.bmp)|*.bmp||"),//ָ��Ҫ�򿪵��ļ�����
						NULL);
	if(open_img.DoModal() == IDOK)
	{
		CString img_select;
		img_select = open_img.GetPathName();
		SetDlgItemText(IDC_EDIT_TOCLIENT, img_select);//img_selectΪѡ����ļ���·����IDC_IMGSELECTEDITΪedit�ؼ�����


}

}

void CServerDlg::OnBnClickedButton3()
{
		// TODO: Add your control notification handler code here
	CFileDialog filedlg(false);        					//�����ļ��Ի������
//filedlg.m_ofn.lpstrFileTitle="����˭";				//�ڶԻ�������ʾ���յ����ļ���
filedlg.DoModal();	
}
