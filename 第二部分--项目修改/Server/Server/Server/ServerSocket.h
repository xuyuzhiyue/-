#pragma once

// CServerSocket ����Ŀ��

class CServerDlg;

class CServerSocket : public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);

private:
	CServerDlg * m_pDlg;
public:
	void setParentDlg(CServerDlg * pDlg);
};


