#ifndef __TROJANS_2017_H__
#define __TROJANS_2017_H__
#include <stdio.h>
#include <process.h>

#include <winsock2.h>
#include <mstcpip.h>

#include <Windows.h>
#include <ListSup.h>

#pragma comment(lib,"ws2_32.lib")

#define PACKET_NAME             "Trojans2017"
#define PACKET_NAME_LENGTH      0x0B
#define DEFAULT_PORT            4040
#define DEFAULT_BAK_PORT        5050

//typedef struct _SERVICES_INFORMATION
//{
//    // info
//}SERVICES_INFORMATION,*PSERVICES_INFORMATION;
//
//typedef struct _SERVICE_LIST
//{
//    ULONG ulServiceCnt;
//    SERVICES_INFORMATION ServiceInfoList[1];
//}SERVICE_LIST,*PSERVICE_LIST;

typedef struct _CLIENT_CONTEXT
{
    LIST_ENTRY NextClient;
    SOCKET Socket;
    PCHAR pBuffer;
    PCHAR pCompressionBuffer;
    PCHAR pDeCompressionBuffer;
    PCHAR pResendBuffer;
    WSABUF WsaInBuffer;
    CHAR InBufferA[8192];
    WSABUF WsaOutBuffer;
    HANDLE hWriteComplete;

    BOOLEAN bIsMainSocket;
    CHAR Group[50];

} CLIENT_CONTEXT,*PCLIENT_CONTEXT;

typedef struct _CLIENT_INFORMATION
{
    ULONG ulOnlineCnt;
    ULONG ulWindows2000;
    ULONG ulWindows2003;
    ULONG ulWindowsXp;
    ULONG ulWindowsVista;
    ULONG ulWindows7;
    ULONG ulWindows8;
    ULONG ulWindows2008;
    ULONG ulWindows10;
    CRITICAL_SECTION CriticalSection;
    LIST_ENTRY ClientList;
} CLIENT_INFORMATION,*PCLIENT_INFORMATION;

typedef enum _COMPRESS_TYPE
{
    ZlibCompress,
    LzmaCompress,
    RdmCompress
}COMPRESS_TYPE,*PCOMPRESS_TYPE;

extern CLIENT_INFORMATION g_ClientInformation;

typedef BOOLEAN (__stdcall *COMPRESSROUTINE)(PCHAR pDestDat,PULONG pulDestSize,PCHAR pSourceDat,ULONG ulSourceSize,COMPRESS_TYPE CompressType);

#endif