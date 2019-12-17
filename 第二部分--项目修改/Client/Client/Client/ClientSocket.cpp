// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientSocket.h"
#include "ClientDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
	m_pDlg=NULL;
}

CClientSocket::~CClientSocket()
{
	m_pDlg=NULL;
}


// CClientSocket 成员函数


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnClose(nErrorCode);
	if(nErrorCode == 0){m_pDlg->onClose();}
}


void CClientSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnConnect(nErrorCode);
	if(nErrorCode == 0){m_pDlg->onConnect();}
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnReceive(nErrorCode);
	if(nErrorCode == 0){m_pDlg->onReceived();}
}

void CClientSocket::setParentDlg(CClientDlg* pDlg)
{
	m_pDlg = pDlg;
}
