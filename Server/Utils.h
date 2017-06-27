#ifndef __UTILS_H__
#define __UTILS_H__

void CleanZero(PCHAR pCleanBuffer,ULONG ulLength);
PCHAR My__MEMCPY__(PCHAR pDst,PCHAR pSrc,ULONG ulLength);
ULONG CalcHashValue(char *szApiName);
int  My_memicmp(char *src,char *dest,int size);
char *My_stristr(char *src,char *dest);
int my_strlen(char *str);
int my_strcmp(char *src,char *dest);
char *My_Strcpy(char *dst,const char *src);
BOOL __ISUPPER__(__in CHAR c);
CHAR __TOLOWER__(__in CHAR c);
ULONG __STRLEN__(PCHAR pStr);
ULONG __STRLENW__(__in LPWSTR lpStr1);
LPSTR __STRSTRI__(__in LPSTR lpStr1, __in LPSTR lpStr2);
LPWSTR __STRSTRIW__(__in LPWSTR lpStr1, __in LPWSTR lpStr2);
ULONG __STRCMPI__(__in LPSTR lpStr1, __in LPSTR lpStr2);
ULONG __STRNCMPI__(__in LPSTR lpStr1, __in LPSTR lpStr2, __in DWORD dwLen);
ULONG __STRNCMPIW__(__in LPWSTR lpStr1, __in LPWSTR lpStr2, __in DWORD dwLen);
LPSTR __STRCAT__(__in LPSTR	strDest,__in LPSTR strSource);
LPWSTR __STRCATW__(__in LPWSTR	strDest, __in LPWSTR strSource);
LPVOID __MEMCPY__(__in LPVOID lpDst,__in LPVOID lpSrc,__in DWORD dwCount);
VOID __MEMSET__(__in LPVOID p, __in CHAR cValue, __in DWORD dwSize);
ULONG UnicodeToAnsi(PWCHAR pSrc,PCHAR pDst,ULONG ulSize);
ULONG AnsiToUnicode(PCHAR pSrc,PWCHAR pDst,ULONG ulSize);
int StormRand(int count);
//HANDLE GetPidFromProcessName(PWCHAR wProcName);
HANDLE GetLdrDllHandle(PWCHAR pDllName);
BOOLEAN getLoginInfo(char *lpURL, char **lppszHost, LPDWORD lppPort);
void SplitLoginInfo(char *lpDecodeString,char **lppszHost,LPDWORD lppPort);
DWORD CPUClockMhz();
char* MyDecode(char *str);
int base64_decode(const char *str, char **data);
char __fastcall upcaseA(char c);
int __fastcall strcmpiA(const char *s1, const char *s2);
BOOLEAN SelfDeleteMe();
PCHAR MyStrChr(PCHAR pDest,ULONG ulAscii);
#endif