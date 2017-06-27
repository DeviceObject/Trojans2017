#include "Trojans2017.h"
#include "NetIoCompletionPort.h"

int __cdecl main(int nArgc,PCHAR pArgv)
{
    do 
    {
        if (FALSE == InitializeGlobalDat())
        {
            break;
        }
        if (FALSE == InitializeIoCompletionPort())
        {
            break;
        }
    } while (0);
    WaitForSingleObject(g_IoCompletionPortInformation.hStopEvent,INFINITE);
	return 0;
}

