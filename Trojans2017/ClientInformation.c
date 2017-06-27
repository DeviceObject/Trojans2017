#include "Trojans2017.h"
#include "ClientInformation.h"

void InitializeClientInfo()
{
    RtlZeroMemory(&g_ClientInformation,sizeof(CLIENT_INFORMATION));
    InitializeCriticalSection(&g_ClientInformation.CriticalSection);
    InitializeListHead(&g_ClientInformation.ClientList);
}
ULONG AddTail(PCLIENT_CONTEXT pClientContext)
{
    if (NULL == pClientContext)
    {
        return g_ClientInformation.ulOnlineCnt;
    }
    InitializeListHead(&pClientContext->NextClient);

    EnterCriticalSection(&g_ClientInformation.CriticalSection);
    InsertTailList(&g_ClientInformation.ClientList,&pClientContext->NextClient);
    LeaveCriticalSection(&g_ClientInformation.CriticalSection);
    InterlockedIncrement(&g_ClientInformation.ulOnlineCnt);
    return g_ClientInformation.ulOnlineCnt;
}
PCLIENT_CONTEXT FindClient(PCLIENT_CONTEXT pClient)
{
    return NULL;
}