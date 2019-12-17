// ServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"
#include "ServerDlg.h"


// CServerSocket

CServerSocket::CServerSocket()
{
	m_pDlg = NULL;
}

CServerSocket::~CServerSocket()
{
	m_pDlg = NULL;
}


// CServerSocket ��Ա����

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnAccept(nErrorCode);
	if(nErrorCode == 0){m_pDlg -> onAccept();}
}

void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnClose(nErrorCode);
	if(nErrorCode == 0){m_pDlg -> onClose();}
}

void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnReceive(nErrorCode);
	if(nErrorCode == 0){m_pDlg -> onReceived();}
}
void CServerSocket::setParentDlg(CServerDlg * pDlg)
{
	m_pDlg = pDlg;
}
