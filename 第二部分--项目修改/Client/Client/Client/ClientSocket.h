#pragma once
class CClientDlg;

// CClientSocket ÃüÁîÄ¿±ê

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
//	virtual void AssertValid() const;
//	virtual void AssertValid() const;
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
private:
	CClientDlg* m_pDlg;
public:
	void setParentDlg(CClientDlg* pDlg);
};

