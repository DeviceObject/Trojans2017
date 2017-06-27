#include "Server.h"
#include "ApiBlock.h"
#include "Utils.h"
#include "RunTimeCheck.h"

BOOLEAN IsCheckSystemX64()
{
	if (sizeof(ULONG_PTR) == 0x04)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
	return FALSE;
}
BOOLEAN CheckRepeatRun(HMODULE hModuleName)
{
	HANDLE hMutex;
	WCHAR wModuleName[MAX_PATH];

	hMutex = NULL;
	CleanZero((PCHAR)wModuleName,sizeof(WCHAR) * MAX_PATH);

	g_Kernel32ApiBlock.MyGetModuleFileNameW(hModuleName,wModuleName,MAX_PATH);

	hMutex = g_Kernel32ApiBlock.MyCreateMutexW(NULL,FALSE,wModuleName);
	if (hMutex && g_Kernel32ApiBlock.MyGetLastError() == ERROR_ALREADY_EXISTS)
	{
		return FALSE;
	}
	return TRUE;
}
ULONG BkCRC32(PCHAR pMem,ULONG ulLength)
{
    ULONG uli,ulC;
    ULONG ulSeed = -1;

    while(ulLength--)
    {
        ulC = *pMem;
        pMem = pMem + 1;

        for(uli = 0;uli < 8;uli++ )
        {
            if ((ulSeed ^ ulC) & 1)
            {
                ulSeed = (ulSeed >> 1) ^ 0xEDB88320;
            }
            else
            {
                ulSeed = (ulSeed >> 1);
            }
            ulC >>= 1;
        }
    }
    return ulSeed;
}