//  Created by Nijie on 2009/09/01.
//  Copyright (c) 2009 Nijie. All rights reserved.
//

#ifndef __IFNET_H_2009_0901__
#define __IFNET_H_2009_0901__

#ifdef WIN32
#include <WinSock2.h>

#ifdef   FXN_DLLCLASS
#define  DLLCLASS_DECL           __declspec(dllexport)   
#else
#define  DLLCLASS_DECL           __declspec(dllexport)   
#endif

#ifdef FXN_STATICLIB
#undef  DLLCLASS_DECL
#define DLLCLASS_DECL
#endif

#else
#define SOCKET UINT32
#define DLLCLASS_DECL
#define INVALID_SOCKET UINT32(-1)
#endif

#include "version.h"
#include "fxtype.h"

class FxConnection;

#define LINUX_NETTHREAD_COUNT   2   // linuxĬ�������߳���,WindowsĬ�ϲ���cpu������2��
#define MAX_CONNECTION_COUNT    1024
#define MAX_NETEVENT_PERSOCK    1024

enum ENetErrCode{
    NET_RECVBUFF_ERROR  = -7,
    NET_CONNECT_FAIL    = -6,
    NET_SYSTEM_ERROR    = -5, 
    NET_RECV_ERROR      = -4, 
    NET_SEND_ERROR      = -3, 
    NET_SEND_OVERFLOW   = -2,
    NET_PACKET_ERROR    = -1,
    NET_SUCCESS         = 0
};

enum ESessionOpt
{
    ESESSION_SENDLINGER = 1,    // �����ӳ٣�ֱ���ɹ�������30�κ�Ĭ�ϲ���
	ESESSION_TCP_NODELAY,		// TCP ѡ��Ƿ�����Nagle�㷨��Ĭ�Ϲرգ���������Magle�㷨
	ESESSION_RELEASE_LOWBUFF,	// �ͷŵײ�buff�����Բ��ͷ��Ա��ظ����ã����ô˽ӿ���Ϊ�˽����Щ����Buff�Ƚϴ������ֱȽ��ٵ����
};

enum ENetOpt
{
    ENET_MAX_CONNECTION = 1,    // ���������
    ENET_MAX_TOTALEVENT,        // ÿ��Socket������¼�����
};

class DLLCLASS_DECL FxSession	// �������ӻỰ��
{
public:
    FxSession();
    virtual ~FxSession();

    virtual void        OnConnect(void) = 0;						// �������ӳɹ��ص��ӿ�

    virtual void        OnClose(void) = 0;							// �������ӹرա��Ͽ��ص��ӿ�

    virtual void        OnError(UINT32 dwErrorNo) = 0;				// �������Ӵ���ص��ӿ�

    virtual void        OnRecv(const char* pBuf, UINT32 dwLen) = 0;	// ����������Ϣ���ջص��ӿ�

    virtual void        Release(void) = 0;							// �ûỰ���ͷŻص��ӿڣ��Ա�ﵽ�ڴ�������䣬�����ͷŵ�Ҫ��

    virtual char*       GetRecvBuf() = 0;							// ��ûỰ���ջ����ڴ�ص��ӿ�

    virtual UINT32      GetRecvSize() = 0;							// ��ûỰ���ջ����ڴ��С�ص��ӿ�

    virtual const char* GetRemoteIPStr();							// ����������ӶԷ�ip��ַ�ӿ�

    virtual UINT32      GetRemotePort();							// ����������ӶԷ��˿ڽӿ�

    virtual bool        Send(const char* pBuf,UINT32 dwLen);		// �������ӷ��ͽӿ�

    virtual void        Close(void);								// �رո��������ӻỰ�ӿ�

    virtual bool        Reconnect(void);							// ����

    virtual bool        IsConnected(void);							// �ж��Ƿ�������

    virtual void        Init(FxConnection* poConnection);

    virtual bool        SetSessionOpt(ESessionOpt eOpt, bool bSetting);	// �������Խӿ�

    virtual FxConnection*   GetConnection(void);

private:
    FxConnection*        m_poConnection;
};

// �Ự������
class IFxSessionFactory
{
public:
	virtual ~IFxSessionFactory() {}

	// �����Ự��ӿ�
    virtual FxSession*   CreateSession() = 0;
};

class IFxNet
{
public:
    virtual ~IFxNet() {}

	// ����ȫ������
    virtual bool        SetNetOpt(ENetOpt eOpt, int nValue) = 0;
    
	// ��ʼ��
	virtual bool        Init(int nThread = 1) = 0;

	// ��Ϣ������ѭ��
    virtual bool        Run(UINT32 dwCount) = 0;

	// �ͷ�
    virtual void        Release() = 0;

	// ����
    virtual SOCKET      Connect(FxSession* poSession, UINT32 dwIP, UINT16 wPort, UINT32 dwRecvSize, UINT32 dwSendSize, bool bReconnect = false, bool bHead = true, int nEventPerSocket = MAX_NETEVENT_PERSOCK) = 0;
    
	// ����
	virtual bool        Listen(IFxSessionFactory* poFactory, UINT32 dwIP, UINT16 wPort, UINT32 dwRecvSize, UINT32 dwSendSize, bool bHead = true, int nEventPerSocket = MAX_NETEVENT_PERSOCK) = 0;

private:

};

IFxNet* FxNetGetModule();

typedef IFxNet* (*PFN_FxNetGetModule)();


#endif  // __IFNET_H_2009_0901__

