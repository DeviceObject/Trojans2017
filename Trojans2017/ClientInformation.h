#ifndef __CLIENT_INFORMATION_H__
#define __CLIENT_INFORMATION_H__

void InitializeClientInfo();
ULONG AddTail(PCLIENT_CONTEXT pClientContext);
PCLIENT_CONTEXT FindClient(PCLIENT_CONTEXT pClient);

#endif