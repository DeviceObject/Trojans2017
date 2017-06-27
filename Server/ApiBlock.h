#ifndef __API_BLOCK_H__
#define __API_BLOCK_H__

#include <ntsecapi.h>
#include <mstcpip.h>
#include <WinInet.h>
#include <WtsApi32.h>
#include <WinSock2.h>
#include <TlHelp32.h>


typedef BOOLEAN (__stdcall *GETCOMPUTERNAMEW)(LPTSTR lpBuffer,LPDWORD lpnSize);
typedef BOOLEAN (__stdcall *GETUSERNAMEW)(LPTSTR lpBuffer,LPDWORD lpnSize);
typedef UINT (__stdcall *GETSYSTEMDIRECTORYW)(LPTSTR lpBuffer,UINT uSize);
typedef UINT (__stdcall *GETWINDOWSDIRECTORYW)(LPTSTR lpBuffer,UINT uSize);
typedef HANDLE (__stdcall *CREATEFILEW)(LPCTSTR lpFileName,  \
                                        DWORD dwDesiredAccess, \
                                        DWORD dwShareMode, \
                                        LPSECURITY_ATTRIBUTES lpSecurityAttributes, \
                                        DWORD dwCreationDisposition, \
                                        DWORD dwFlagsAndAttributes, \
                                        HANDLE hTemplateFile);
typedef BOOLEAN (__stdcall *READFILE)(HANDLE hFile, \
                                      LPVOID lpBuffer, \
                                      DWORD nNumberOfBytesToRead, \
                                      LPDWORD lpNumberOfBytesRead, \
                                      LPOVERLAPPED lpOverlapped);
typedef BOOLEAN (__stdcall *WRITEFILE)(HANDLE hFile, \
                                       LPCVOID lpBuffer, \
                                       DWORD nNumberOfBytesToWrite, \
                                       LPDWORD lpNumberOfBytesWritten, \
                                       LPOVERLAPPED lpOverlapped);
typedef HRESULT (__stdcall *CLOSEHANDLE)(HANDLE hHandle);
typedef HANDLE (__stdcall *CREATETHREAD)(LPSECURITY_ATTRIBUTES lpThreadAttributes, \
                                         SIZE_T dwStackSize, \
                                         LPTHREAD_START_ROUTINE lpStartAddress, \
                                         LPVOID lpParameter, \
                                         DWORD dwCreationFlags, \
                                         LPDWORD lpThreadId);
typedef SC_HANDLE (__stdcall *CREATESERICEW)(SC_HANDLE hSCManager, \
                                             LPCTSTR lpServiceName, \
                                             LPCTSTR lpDisplayName, \
                                             DWORD dwDesiredAccess, \
                                             DWORD dwServiceType, \
                                             DWORD dwStartType, \
                                             DWORD dwErrorControl, \
                                             LPCTSTR lpBinaryPathName, \
                                             LPCTSTR lpLoadOrderGroup, \
                                             LPDWORD lpdwTagId, \
                                             LPCTSTR lpDependencies, \
                                             LPCTSTR lpServiceStartName, \
                                             LPCTSTR lpPassword);
typedef SC_HANDLE (__stdcall *OPENSCMANAGERW)(LPCTSTR lpMachineName, \
                                              LPCTSTR lpDatabaseName, \
                                              DWORD dwDesiredAccess);
typedef SC_HANDLE (__stdcall *OPENSERVICEW)(SC_HANDLE hSCManager, \
                                            LPCTSTR lpServiceName, \
                                            DWORD dwDesiredAccess);
typedef BOOLEAN (__stdcall *STARTSERVICEW)(SC_HANDLE hService, \
                                           DWORD dwNumServiceArgs, \
                                           LPCTSTR *lpServiceArgVectors);
typedef BOOLEAN (__stdcall *CONTROLSERVICE)(SC_HANDLE hService, \
                                            DWORD dwControl, \
                                            LPSERVICE_STATUS lpServiceStatus);
typedef BOOLEAN (__stdcall *QUERYSERVICESTATUSEX)(SC_HANDLE hService, \
                                                  SC_STATUS_TYPE InfoLevel, \
                                                  LPBYTE lpBuffer, \
                                                  DWORD cbBufSize, \
                                                  LPDWORD pcbBytesNeeded);
typedef BOOLEAN (__stdcall *DELETESERVICE)(SC_HANDLE hService);
typedef BOOLEAN (__stdcall *CLOSESERVICEHANDLE)(SC_HANDLE hSCObject);
typedef HANDLE (__stdcall *FINDFIRSTFILEW)(LPCTSTR lpFileName, \
                                           LPWIN32_FIND_DATA lpFindFileData);
typedef BOOLEAN (__stdcall *FINDNEXTFILEW)(HANDLE hFindFile, \
                                           LPWIN32_FIND_DATA lpFindFileData);
typedef BOOLEAN (__stdcall *FINDCLOSE)(HANDLE hFindFile);
typedef LPVOID (__stdcall *VIRTUALALLOC)(LPVOID lpAddress, \
                                         SIZE_T dwSize, \
                                         DWORD flAllocationType, \
                                         DWORD flProtect);
typedef BOOL (__stdcall *VIRTUALFREE)(LPVOID lpAddress, \
                                      SIZE_T dwSize, \
                                      DWORD dwFreeType);
typedef DWORD (__stdcall *GETFILESIZE)(HANDLE hFile,LPDWORD lpFileSizeHigh);
typedef DWORD (__stdcall *GETMODULEFILENAMEW)(HMODULE hModule,LPTSTR lpFilename,DWORD nSize);
typedef HANDLE (__stdcall *CREATEEVENTW)(LPSECURITY_ATTRIBUTES lpEventAttributes, \
                                         BOOL bManualReset, \
                                         BOOL bInitialState, \
                                         LPCTSTR lpName);
typedef DWORD (__stdcall *SETFILEPOINTER)(HANDLE hFile, \
                                          LONG lDistanceToMove, \
                                          PLONG lpDistanceToMoveHigh, \
                                          DWORD dwMoveMethod);
typedef VOID (__stdcall *SLEEP)(DWORD dwMilliseconds);
typedef LONG (__stdcall *REGOPENKEYW)(HKEY hKey,LPCTSTR lpSubKey,PHKEY phkResult);
typedef LONG (__stdcall *REGSETVALUEEXW)(HKEY hKey,LPCTSTR lpValueName,DWORD Reserved,DWORD dwType,const BYTE *lpData,DWORD cbData);
typedef BOOL (__stdcall *QUERYSERVICESTATUS)(SC_HANDLE hService,LPSERVICE_STATUS lpServiceStatus);
typedef int (__stdcall *WIDECHARTOMULTIBYTE)(UINT CodePage, \
                                             DWORD dwFlags, \
                                             LPCWSTR lpWideCharStr, \
                                             int cchWideChar, \
                                             LPSTR lpMultiByteStr, \
                                             int cbMultiByte, \
                                             LPCSTR lpDefaultChar, \
                                             LPBOOL lpUsedDefaultChar);
typedef int (__stdcall *MULTIBYTETOWIDECHAR)(UINT CodePage, \
                                             DWORD dwFlags, \
                                             LPCSTR lpMultiByteStr, \
                                             int cbMultiByte, \
                                             LPWSTR lpWideCharStr, \
                                             int cchWideChar);
typedef int (__stdcall *WSPRINTDA)(LPSTR,LPCSTR,...);
typedef int (__stdcall *WSPRINTDW)(LPWSTR,LPCWSTR,...);
typedef HANDLE (__stdcall *CREATEMUTEXW)(LPSECURITY_ATTRIBUTES lpMutexAttributes,BOOL bInitialOwner,LPCTSTR lpName);
typedef BOOL (__stdcall *SHGETSPECIALFOLDERPATHW)(HWND hwndOwner,LPTSTR lpszPath,int csidl,BOOL fCreate);
typedef BOOL (__stdcall *DEFINEDOSDEVICEW)(DWORD dwFlags,LPCTSTR lpDeviceName,LPCTSTR lpTargetPath);
typedef DWORD (__stdcall *GETFILEATTRIBUTESW)(LPCTSTR lpFileName);
typedef BOOL (__stdcall *COPYFILEW)(LPCTSTR lpExistingFileName,LPCTSTR lpNewFileName,BOOL bFailIfExists);
typedef BOOL (__stdcall *MOVEFILEEXW)(LPCTSTR lpExistingFileName,LPCTSTR lpNewFileName,DWORD dwFlags);
typedef BOOL (__stdcall *SETFILEATTRIBUTESW)(LPCWSTR lpFileName,DWORD dwFileAttributes);
typedef BOOL (__stdcall *CREATEDIRECTORYW)(LPCWSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef LONG (__stdcall *REGOPENKEYEXW)(HKEY hKey,LPCTSTR lpSubKey,DWORD ulOptions,REGSAM samDesired,PHKEY phkResult);
typedef LONG (__stdcall *REGCLOSEKEY)(HKEY hKey);
typedef BOOL (__stdcall *SETSERVICESTATUS)(SERVICE_STATUS_HANDLE hServiceStatus,LPSERVICE_STATUS lpServiceStatus);
typedef SERVICE_STATUS_HANDLE (__stdcall *REGISTERSERVICECTLHANDLERW)(LPCTSTR lpServiceName,LPHANDLER_FUNCTION lpHandlerProc);
typedef BOOL (__stdcall *STARTSERVICECTLDISPATCHERW)(const SERVICE_TABLE_ENTRY *lpServiceTable);
typedef DWORD (__stdcall *GETTICKCOUNT)(void);
typedef SC_LOCK (__stdcall *LOCKSERVICEDATABASE)(SC_HANDLE hSCManager);
typedef BOOL (__stdcall *CHANGESERVICECONFIG2W)(SC_HANDLE hService,DWORD dwInfoLevel,LPVOID lpInfo);
typedef BOOL (__stdcall *UNLOCKSERVICEDATABASE)(SC_LOCK ScLock);
typedef int (__stdcall *WSASTARTUP)(WORD wVersionRequested,LPWSADATA lpWSAData);
typedef HANDLE (__stdcall *OPENEVENTW)(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCTSTR lpName);
typedef struct hostent* FAR (__stdcall *GETHOSTBYNAME)(const char *name);
typedef int (__stdcall *WSAIOCTL)(SOCKET s, \
                                  DWORD dwIoControlCode, \
                                  LPVOID lpvInBuffer, \
                                  DWORD cbInBuffer, \
                                  LPVOID lpvOutBuffer, \
                                  DWORD cbOutBuffer, \
                                  LPDWORD lpcbBytesReturned, \
                                  LPWSAOVERLAPPED lpOverlapped, \
                                  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
typedef BOOL (__stdcall *RESETEVENT)(HANDLE hEvent);
typedef SOCKET (__stdcall *DEFSOCKET)(int af,int type,int protocol);
typedef u_short (__stdcall *HTONS)(u_short hostshort);
typedef int (__stdcall *CONNECT)(SOCKET s,const struct sockaddr *name,int namelen);
typedef int (__stdcall *SETSOCKOPT)(SOCKET s,int level,int optname,const char *optval,int optlen);
typedef int (__stdcall *SELECT)(int nfds,fd_set FAR * readfds,fd_set FAR * writefds,fd_set FAR * exceptfds,const struct timeval FAR * timeout);
typedef BOOL (__stdcall *CANCELIO)(HANDLE hFile);
typedef int (__stdcall *CLOSESOCKET)(SOCKET s);
typedef BOOL (__stdcall *SETEVENT)(HANDLE hEvent);
typedef int (__stdcall *SELECT)(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,const struct timeval *timeout);
typedef int (__stdcall *RECV)(SOCKET s,char *buf,int len,int flags);
typedef HMODULE (__stdcall *LOADLIBRARYW)(LPCTSTR lpFileName);
typedef LPTSTR (__stdcall *GETCOMMANDLINEW)(void);
typedef LPWSTR* (__stdcall *COMMANDLINETOARGVW)(LPCWSTR lpCmdLine,int *pNumArgs);
typedef HINTERNET (__stdcall *INTERNETOPENW)(LPCTSTR lpszAgent,DWORD dwAccessType,LPCTSTR lpszProxyName,LPCTSTR lpszProxyBypass,DWORD dwFlags);
typedef HINTERNET (__stdcall *INTERNETOPENURLW)(HINTERNET hInternet,LPCTSTR lpszUrl,LPCTSTR lpszHeaders,DWORD dwHeadersLength,DWORD dwFlags,DWORD_PTR dwContext);
typedef BOOL (__stdcall *INTERNETREADFILE)(HINTERNET hFile,LPVOID lpBuffer,DWORD dwNumberOfBytesToRead,LPDWORD lpdwNumberOfBytesRead);
typedef BOOL (__stdcall *INTERNETCLOSEHANDLE)(HINTERNET hInternet);
typedef BOOL (__stdcall *CREATEPIPE)(PHANDLE hReadPipe,PHANDLE hWritePipe,LPSECURITY_ATTRIBUTES lpPipeAttributes,DWORD nSize);
typedef VOID (__stdcall *GETSTARTUPINFOA)(LPSTARTUPINFOA lpStartupInfoA);
typedef VOID (__stdcall *GETSTARTUPINFOW)(LPSTARTUPINFOW lpStartupInfoW);
typedef BOOL (__stdcall *CREATEPROCESSA)(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );
typedef BOOL (__stdcall *CREATEPROCESSW)(
    LPCWSTR lpApplicationName,
    LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    );
typedef BOOL (__stdcall *PEEKNAMEDPIPE)(
                                        HANDLE  hNamedPipe,
                                        LPVOID  lpBuffer,
                                        DWORD   nBufferSize,
                                        LPDWORD lpBytesRead,
                                        LPDWORD lpTotalBytesAvail,
                                        LPDWORD lpBytesLeftThisMessage);
typedef HLOCAL (__stdcall *LOCALALLOC)(
                                       UINT   uFlags,
                                       SIZE_T uBytes);
typedef HLOCAL (__stdcall *LOCALFREE)(
                                      HLOCAL hMem);
typedef DWORD (__stdcall *WAITFORMULTIPLEOBJECTS)(
    DWORD  nCount,
    const HANDLE *lpHandles,
    BOOL   bWaitAll,
    DWORD  dwMilliseconds);
typedef BOOL (__stdcall *TERMINATETHREAD)(
    HANDLE hThread,
    DWORD  dwExitCode
    );
typedef BOOL (__stdcall *TERMINATEPROCESS)(
    HANDLE hProcess,
    UINT   uExitCode
    );
typedef DWORD (__stdcall *WAITFORSINGLEOBJECT)(
    HANDLE hHandle,
    DWORD  dwMilliseconds
    );
typedef BOOL (__stdcall *DISCONNECTNAMEDPIPE)(
    HANDLE hNamedPipe
    );
typedef BOOL (__stdcall *GETVERSIONEXA)(
                                        LPOSVERSIONINFOA lpVersionInfoA
                                        );
typedef BOOL (__stdcall *GETVERSIONEXW)(
                                        LPOSVERSIONINFOW lpVersionInfoW
                                        );
typedef int (__stdcall *GETSOCKNAME)(
                                     SOCKET          s,
struct sockaddr *name,
    int             *namelen
    );
typedef void (__stdcall *GETSYSTEMINFO)(
                                        LPSYSTEM_INFO lpSystemInfo
                                        );
typedef LONG (__stdcall *REGQUERYVALUEEXW)(
    HKEY    hKey,
    LPCTSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE  lpData,
    LPDWORD lpcbData
    );
typedef void (__stdcall *GLOBALMEMORYSTATUS)(
    LPMEMORYSTATUS lpBuffer
    );
typedef int (__stdcall *GETHOSTNAME)(
                                     char *name,
                                     int  namelen
                                     );
typedef int (__stdcall *SEND)(
                              SOCKET s,
                              const char   *buf,
                              int    len,
                              int    flags
                              );
typedef DWORD (__stdcall *STARTTHREAD)(LPVOID lparam);
typedef void (__stdcall *INITIALIZECRITICALSECTION)(
    LPCRITICAL_SECTION lpCriticalSection
    );
typedef void (__stdcall *ENTERCRITICALSECTION)(
    LPCRITICAL_SECTION lpCriticalSection
    );
typedef void (__stdcall *LEAVECRITICALSECTION)(
    LPCRITICAL_SECTION lpCriticalSection
    );
typedef void (__stdcall *DELETECRITICALSECTION)(
    LPCRITICAL_SECTION lpCriticalSection
    );
typedef void (__stdcall *COPYMEMORY)(
                                     PVOID  Destination,
                                     const VOID   *Source,
                                     SIZE_T Length
                                     );
typedef void (__stdcall *MOVEMEMORY)(
                                     PVOID  Destination,
                                     const VOID   *Source,
                                     SIZE_T Length
                                     );
typedef int (__stdcall *WSACLEANUP)(void);
typedef HLOCAL (__stdcall *LOCALREALLOC)(
    HLOCAL hMem,
    SIZE_T uBytes,
    UINT   uFlags
    );
typedef UINT (__stdcall *LOCALSIZE)(
                                    HLOCAL hMem
                                    );
typedef void (__stdcall *GETLOCALTIME)(
                                       LPSYSTEMTIME lpSystemTime
                                       );
typedef HWND (__stdcall *GETFOREGROUNDWINDOW)(void);
typedef int (__stdcall *GETWINDOWTEXTW)(
                                        HWND   hWnd,
                                        LPTSTR lpString,
                                        int    nMaxCount
                                        );
//typedef LSTATUS (__stdcall *REGOPENKEYEXA)(
//	 HKEY hKey,
//	 LPCSTR lpSubKey,
//	 DWORD ulOptions,
//	 REGSAM samDesired,
//	 PHKEY phkResult
//	);
typedef LSTATUS (__stdcall *REGQUERYVALUEA)(
    HKEY hKey,
    LPCSTR lpSubKey,
    LPSTR lpData,
    PLONG lpcbData
    );
typedef DWORD (__stdcall *GETLOGICALDRIVESTRINGA)(
    DWORD nBufferLength,LPSTR lpBuffer);
typedef BOOL (__stdcall *GETVOLUMEINFORMATIONA)(
    LPCSTR lpRootPathName,
    LPSTR lpVolumeNameBuffer,
    DWORD nVolumeNameSize,
    LPDWORD lpVolumeSerialNumber,
    LPDWORD lpMaximumComponentLength,
    LPDWORD lpFileSystemFlags,
    LPSTR lpFileSystemNameBuffer,
    DWORD nFileSystemNameSize
    );
typedef DWORD_PTR (__stdcall *SHGETFILEINFOA)(LPCSTR pszPath, DWORD dwFileAttributes,SHFILEINFOA *psfi,
                                              UINT cbFileInfo, UINT uFlags);
typedef BOOL (__stdcall *GETDISKFREESPACEEXA)(
    LPCSTR lpDirectoryName,
    PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    PULARGE_INTEGER lpTotalNumberOfBytes,
    PULARGE_INTEGER lpTotalNumberOfFreeBytes
    );
typedef UINT (__stdcall *GETDRIVETYPEA)(
                                        LPCSTR lpRootPathName
                                        );
typedef HANDLE (__stdcall *FINDFIRSTFILEA)(
    LPCSTR lpFileName,
    LPWIN32_FIND_DATAA lpFindFileData
    );
typedef BOOL (__stdcall *FINDNEXTFILEA)(
                                        HANDLE hFindFile,
                                        LPWIN32_FIND_DATAA lpFindFileData
                                        );
//typedef BOOL (__fastcall *FINDCLOSE)(
//	out HANDLE hFindFile
//	);
typedef BOOL (__stdcall *DELETEFILEW)(
                                      LPCWSTR lpFileName
                                      );
typedef BOOL (__stdcall *DELETEFILEA)(
                                      LPCSTR lpFileName
                                      );
typedef BOOL (__stdcall *REMOVEDIRECTORYW)(
    LPCWSTR lpPathName
    );
typedef BOOL (__stdcall *REMOVEDIRECTORYA)(
    LPCSTR lpPathName
    );
typedef HANDLE (__stdcall *CREATEFILEA)(
                                        LPCSTR lpFileName,
                                        DWORD dwDesiredAccess,
                                        DWORD dwShareMode,
                                        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                        DWORD dwCreationDisposition,
                                        DWORD dwFlagsAndAttributes,
                                        HANDLE hTemplateFile
                                        );
typedef BOOL (__stdcall *MOVEFILEA)(
                                    LPCSTR lpExistingFileName,
                                    LPCSTR lpNewFileName
                                    );
typedef DWORD (__stdcall *GETFILEATTRIBUTESA)(
    LPCSTR lpFileName
    );
typedef UINT (__stdcall *GETWINDOWSDIRECTORYA)(
    LPSTR lpBuffer,
    UINT uSize
    );
typedef int (__stdcall *GETWINDOWTEXTA)(
                                        HWND hWnd,
                                        LPSTR lpString,
                                        int nMaxCount);
typedef SHORT (__stdcall *GETKEYSTATE)(
                                       int nVirtKey);
typedef SHORT (__stdcall *GETASYNCKEYSTATE)(
    int vKey);
typedef int (__stdcall *WSAGETLASTERROR)(void);
typedef HANDLE (__stdcall *CREATETOOLHELP32SNAPSHOT)(
    DWORD dwFlags,
    DWORD th32ProcessID
    );
typedef BOOL (__stdcall *PROCESS32FIRST)(
    HANDLE           hSnapshot,
    LPPROCESSENTRY32 lppe
    );
typedef BOOL (__stdcall *PROCESS32NEXT)(
                                        HANDLE hSnapshot,
                                        LPPROCESSENTRY32 lppe
                                        );
typedef LSTATUS (__stdcall *REGCREATEKEYEXA)(
    HKEY hKey,
    LPCSTR lpSubKey,
    __reserved DWORD Reserved,
    LPSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
    );
typedef LSTATUS (__stdcall *REGOPENKEYEXA)(
    HKEY hKey,
    LPCSTR lpSubKey,
    DWORD ulOptions,
    REGSAM samDesired,
    PHKEY phkResult
    );
typedef LSTATUS (__stdcall *REGDELETEVALUEA) (
    HKEY hKey,
    LPCSTR lpValueName
    );
typedef LONG (__stdcall *REGDELETEKEYA)(
                                        HKEY    hKey,
                                        LPCSTR lpSubKey
                                        );
typedef LSTATUS (__stdcall *REGSETVALUEEXA)(
    HKEY hKey,
    LPCSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    CONST BYTE* lpData,
    DWORD cbData
    );
typedef LSTATUS (__stdcall *REGQUERYVALUEEXA)(
    HKEY hKey,
    LPCSTR lpValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    );
typedef LSTATUS (__stdcall *REGRESTOREKEYA)(
    HKEY hKey,
    LPCSTR lpFile,
    DWORD dwFlags
    );
typedef LSTATUS (__stdcall *REGSAVEKEYA)(
    HKEY hKey,
    LPCSTR lpFile,
    CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
typedef LSTATUS (__stdcall *REGQUERYINFOKEYA)(
    HKEY hKey,
    LPSTR lpClass,
    LPDWORD lpcchClass,
    LPDWORD lpReserved,
    LPDWORD lpcSubKeys,
    LPDWORD lpcbMaxSubKeyLen,
    LPDWORD lpcbMaxClassLen,
    LPDWORD lpcValues,
    LPDWORD lpcbMaxValueNameLen,
    LPDWORD lpcbMaxValueLen,
    LPDWORD lpcbSecurityDescriptor,
    PFILETIME lpftLastWriteTime
    );
typedef LSTATUS (__stdcall *REGENUMKEYEXA)(
    HKEY hKey,
    DWORD dwIndex,
    LPSTR lpName,
    LPDWORD lpcchName,
    LPDWORD lpReserved,
    LPSTR lpClass,
    LPDWORD lpcchClass,
    PFILETIME lpftLastWriteTime
    );
typedef LSTATUS (__stdcall *REGENUMVALUEA)(
    HKEY hKey,
    DWORD dwIndex,
    LPSTR lpValueName,
    LPDWORD lpcchValueName,
    LPDWORD lpReserved,
    LPDWORD lpType,
    LPBYTE lpData,
    LPDWORD lpcbData
    );
typedef HDESK (__stdcall *OPENDESKTOPA)(
                                        LPCSTR lpszDesktop,
                                        DWORD dwFlags,
                                        BOOL fInherit,
                                        ACCESS_MASK dwDesiredAccess);
typedef HDESK (__stdcall *OPENDESKTOPW)(
                                        LPCWSTR lpszDesktop,
                                        DWORD dwFlags,
                                        BOOL fInherit,
                                        ACCESS_MASK dwDesiredAccess);
typedef HDESK (__stdcall *OPENINPUTDESKTOP)(
    DWORD dwFlags,
    BOOL fInherit,
    ACCESS_MASK dwDesiredAccess);
typedef BOOL (__stdcall *CLOSEDESKTOP)(
                                       HDESK hDesktop
                                       );
typedef HDESK (__stdcall *GETTHREADDESKTOP)(
    DWORD dwThreadId
    );
typedef BOOL (__stdcall *GETUSEROBJECTINFORMATIONA)(
    HANDLE hObj,
    int nIndex,
    PVOID pvInfo,
    DWORD nLength,
    LPDWORD lpnLengthNeeded);
typedef BOOL (__stdcall *GETUSEROBJECTINFORMATIONW)(
    HANDLE hObj,
    int nIndex,
    PVOID pvInfo,
    DWORD nLength,
    LPDWORD lpnLengthNeeded);
typedef BOOL (__stdcall *SETTHREADDESKTOP)(
    HDESK hDesktop);
typedef BOOL (__stdcall *POSTMESSAGE)(
                                      HWND   hWnd,
                                      UINT   Msg,
                                      WPARAM wParam,
                                      LPARAM lParam
                                      );
typedef BOOL (__stdcall *GETVERSIONEXA)(LPOSVERSIONINFOA lpVersionInformation);
typedef BOOL (__stdcall *GETVERSIONEXW)(LPOSVERSIONINFOW lpVersionInformation
                                        );
typedef BOOL (__stdcall *WTSQUERYSESSIONINFORMATIONW)(
    IN HANDLE hServer,
    IN DWORD SessionId,
    IN WTS_INFO_CLASS WTSInfoClass,
    LPWSTR * ppBuffer,
    DWORD * pBytesReturned
    );

typedef BOOL (__stdcall *WTSQUERYSESSIONINFORMATIONA)(
    IN HANDLE hServer,
    IN DWORD SessionId,
    IN WTS_INFO_CLASS WTSInfoClass,
    LPSTR * ppBuffer,
    DWORD * pBytesReturned
    );
typedef VOID (__stdcall *WTSFREEMEMORY)(
                                        IN PVOID pMemory
                                        );
typedef BOOL (__stdcall *BITBLT)(
                                 HDC   hdcDest,
                                 int   nXDest,
                                 int   nYDest,
                                 int   nWidth,
                                 int   nHeight,
                                 HDC   hdcSrc,
                                 int   nXSrc,
                                 int   nYSrc,
                                 DWORD dwRop
                                 );
typedef HBITMAP (__stdcall *CREATECOMPATIBLEBITMAP)(
    HDC hdc,
    int nWidth,
    int nHeight
    );
typedef HBITMAP (__stdcall *CREATEDIBSECTION)(
    HDC        hdc,
    const BITMAPINFO *pbmi,
    UINT       iUsage,
    VOID       **ppvBits,
    HANDLE     hSection,
    DWORD      dwOffset
    );
typedef HGDIOBJ (__stdcall *SELECTOBJECT)(
    HDC     hdc,
    HGDIOBJ hgdiobj
    );
typedef HWND (__stdcall *GETDESKTOPWINDOW)(void);
typedef HDC (__stdcall *CREATECOMPATIBLEDC)(  HDC hdc);
typedef int (__stdcall *RELEASEDC)(
                                   HWND hWnd,
                                   HDC hDC);
typedef BOOL (__stdcall *DELETEDC)(  HDC hdc);
typedef BOOL (__stdcall *DELETEOBJECT)(  HGDIOBJ ho);
typedef int (__stdcall *GETDIBITS)(HDC hdc,           // handle to DC
                                   HBITMAP hbmp,      // handle to bitmap
                                   UINT uStartScan,   // first scan line to set
                                   UINT cScanLines,   // number of scan lines to copy
                                   LPVOID lpvBits,    // array for bitmap bits
                                   LPBITMAPINFO lpbi, // bitmap data buffer
                                   UINT uUsage);        // RGB or palette index
typedef int (__stdcall *__WSAFDISSET)(
                                      SOCKET fd,
                                      fd_set *set
                                      );
typedef SOCKET (__stdcall *ACCEPT)(
                                   SOCKET s,
                                   struct sockaddr FAR * addr,
                                   int FAR * addrlen
                                   );
typedef int (__stdcall *BIND)(
                              SOCKET s,
                              const struct sockaddr FAR * name,
                              int namelen
                              );
typedef int (__stdcall *LISTEN)(
                                SOCKET s,
                                int backlog
                                );
typedef unsigned long (__stdcall *INET_ADDR)(
    IN const char FAR * cp
    );
typedef int (__stdcall *GETPEERNAME)(
                                     SOCKET          s,
struct sockaddr *name,
    int             *namelen
    );
typedef int (__stdcall *RECVFROM)(
                                  SOCKET          s,
                                  char            *buf,
                                  int             len,
                                  int             flags,
struct sockaddr *from,
    int             *fromlen
    );
typedef char FAR *(__stdcall *INET_NTOA)(
struct in_addr in
    );
typedef u_short (__stdcall *NTOHS)(
                                   u_short netshort
                                   );
typedef int (__stdcall *SENDTO)(
                                SOCKET                s,
                                const char                  *buf,
                                int                   len,
                                int                   flags,
                                const struct sockaddr *to,
                                int                   tolen
                                );
typedef HINTERNET (__stdcall *INTERNETOPENA)(
    LPCSTR lpszAgent,
    DWORD dwAccessType,
    LPCSTR lpszProxy,
    LPCSTR lpszProxyBypass,
    DWORD dwFlags
    );
typedef HINTERNET (__stdcall *INTERNETOPENURLA)(
    HINTERNET hInternet,
    LPCSTR lpszUrl,
    LPCSTR lpszHeaders,
    DWORD dwHeadersLength,
    DWORD dwFlags,
    DWORD_PTR dwContext
    );
typedef int (__stdcall *IOCTLSOCKET)(
                                     SOCKET s, 
                                     long cmd, 
                                     u_long *argp );
typedef HANDLE (__stdcall *CREATEMUTEXA)(
    LPSECURITY_ATTRIBUTES lpMutexAttributes,
    BOOL bInitialOwner,
    LPCSTR lpName
    );
typedef HANDLE (__stdcall *OPENEVENTA)(
                                       DWORD dwDesiredAccess,
                                       BOOL bInheritHandle,
                                       LPCSTR lpName
                                       );
typedef VOID (__stdcall *EXITPROCESS)(
                                      UINT uExitCode
                                      );
typedef UINT (__stdcall *GETSYSTEMDIRECTORYA)(LPSTR lpBuffer,UINT uSize);
//typedef UINT (__stdcall *GETSYSTEMDIRECTORYW)(LPWSTR lpBuffer,UINT uSize);
//typedef DWORD (__stdcall *GETLOGICALDRIVESTRINGSA)(DWORD nBufferLength,LPSTR lpBuffer);
typedef DWORD (__stdcall *GETLOGICALDRIVESTRINGSW)(DWORD nBufferLength,LPWSTR lpBuffer);
typedef LPSTR (__stdcall *CHARNEXTA)(LPCSTR lpsz);
typedef LPWSTR (__stdcall *CHARNEXTW)(LPCWSTR lpsz);
typedef BOOL (__stdcall *CREATEDIRECTORYA)(
    LPCSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
typedef BOOL (__stdcall *CREATEDIRECTORYW)(
    LPCWSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
typedef SC_HANDLE (__stdcall *OPENSCMANAGERA)(
    LPCSTR                lpMachineName,
    LPCSTR                lpDatabaseName,
    DWORD                   dwDesiredAccess
    );
typedef SC_HANDLE (__stdcall *OPENSERVICEA)(
    SC_HANDLE               hSCManager,
    LPCSTR                lpServiceName,
    DWORD                   dwDesiredAccess
    );
typedef DWORD (__stdcall *GETMODULEFILENAMEA)(
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    );
typedef DWORD (__stdcall *GETTEMPPATHA)(
                                        DWORD nBufferLength,
                                        LPSTR lpBuffer
                                        );
typedef BOOL (__stdcall *MOVEFILEEXA)(
                                      LPCSTR lpExistingFileName,
                                      LPCSTR lpNewFileName,
                                      DWORD    dwFlags
                                      );
typedef HANDLE (__stdcall *CREATEEVENTA)(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCSTR lpName
    );
typedef BOOL (__stdcall *ENUMWINDOWS)(
                                      WNDENUMPROC lpEnumFunc,
                                      LPARAM      lParam
                                      );
typedef HANDLE (__stdcall *OPENPROCESS)(
                                        DWORD dwDesiredAccess,
                                        BOOL bInheritHandle,
                                        DWORD dwProcessId
                                        );
typedef HANDLE (__stdcall *CREATETOOLHELP32SNAPSHOT)(
    DWORD dwFlags,
    DWORD th32ProcessID
    );
typedef BOOL (__stdcall *ENUMPROCESSMODULES)(
    HANDLE hProcess,
    HMODULE *lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded
    );
typedef DWORD (__stdcall *GETMODULEFILENAMEEXA)(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    );
typedef BOOL (__stdcall *OPENPROCESSTOKEN)(
    HANDLE ProcessHandle,
    DWORD DesiredAccess,
    PHANDLE TokenHandle
    );
typedef BOOL (__stdcall *LOOKUPPRIVILEGEVALUEA)(
    LPCSTR lpSystemName,
    LPCSTR lpName,
    PLUID   lpLuid
    );
typedef BOOL (__stdcall *ADJUSTTOKENPRIVILEGES)(
    HANDLE TokenHandle,
    BOOL DisableAllPrivileges,
    PTOKEN_PRIVILEGES NewState,
    DWORD BufferLength,
    PTOKEN_PRIVILEGES PreviousState,
    PDWORD ReturnLength
    );

typedef DWORD (__stdcall *GETLASTERROR)(
                                        VOID
                                        );
typedef HANDLE (__stdcall *GETCURRENTPROCESS)(
    VOID
    );
typedef DWORD (__stdcall *GETWINDOWTHREADPROCESSID)(
    HWND hWnd,
    LPDWORD lpdwProcessId);
typedef BOOL (__stdcall *ISWINDOWVISIBLE)(
    HWND hWnd);
typedef BOOL (__stdcall *EXITWINDOWSEX)(
                                        UINT uFlags,
                                        DWORD dwReason);
//typedef BOOL (__stdcall *ENUMWINDOWS)(
//	 WNDENUMPROC lpEnumFunc,
//	 LPARAM lParam);
typedef HINSTANCE (__stdcall *SHELLEXECUTEA)( HWND hwnd,  LPCSTR lpOperation,  LPCSTR lpFile,  LPCSTR lpParameters,
                                             LPCSTR lpDirectory,  INT nShowCmd);

typedef LSTATUS (__stdcall *REGCREATEKEYA)(
    HKEY hKey,
    LPCSTR lpSubKey,
    PHKEY phkResult
    );
typedef HANDLE (__stdcall *OPENEVENTLOGA)(
    LPCSTR lpUNCServerName,
    LPCSTR lpSourceName
    );
typedef BOOL (__stdcall *CLEAREVENTLOGA)(
    HANDLE hEventLog,
    LPCSTR lpBackupFileName
    );
typedef BOOL (__stdcall *CLEAREVENTLOGW)(
    HANDLE hEventLog,
    LPCWSTR lpBackupFileName
    );
typedef BOOL (__stdcall *CLOSEEVENTLOG)(
                                        HANDLE hEventLog
                                        );
typedef LPVOID (__stdcall *HEAPALLOC)(
                                      HANDLE hHeap,
                                      DWORD dwFlags,
                                      SIZE_T dwBytes
                                      );

typedef LPVOID (__stdcall *HEAPREALLOC)(
                                        HANDLE hHeap,
                                        DWORD dwFlags,
                                        LPVOID lpMem,
                                        SIZE_T dwBytes
                                        );

typedef BOOL (__stdcall *HEAPFREE)(
                                   HANDLE hHeap,
                                   DWORD dwFlags,
                                   LPVOID lpMem
                                   );
typedef SIZE_T (__stdcall *HEAPSIZE)(
                                     HANDLE hHeap,
                                     DWORD dwFlags,
                                     LPCVOID lpMem
                                     );
typedef HANDLE (__stdcall *GETPROCESSHEAP)(void);
typedef LONG (__stdcall *REGSETKEYSECURITY)(
    HKEY hKey,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor
    );

typedef BOOL (__stdcall *ALLOCATEANDINITIALIZESID)(
    PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
    BYTE nSubAuthorityCount,
    DWORD dwSubAuthority0,
    DWORD dwSubAuthority1,
    DWORD dwSubAuthority2,
    DWORD dwSubAuthority3,
    DWORD dwSubAuthority4,
    DWORD dwSubAuthority5,
    DWORD dwSubAuthority6,
    DWORD dwSubAuthority7,
    PSID* pSid
    );
typedef DWORD (__stdcall *GETLENGTHSID)(
                                        PSID pSid
                                        );
typedef BOOL (__stdcall *INITIALIZEACL)(
                                        PACL pAcl,
                                        DWORD nAclLength,
                                        DWORD dwAclRevision
                                        );
typedef BOOL (__stdcall *ADDACCESSALLOWEDACE)(PACL pAcl,
                                              DWORD dwAceRevision,
                                              DWORD AccessMask,
                                              PSID pSid
                                              );
typedef BOOL (__stdcall *INITIALIZESECURITYDESCRIPTOR)(
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    DWORD dwRevision
    );
typedef BOOL (__stdcall *SETSECURITYDESCRIPTORDACL)(PSECURITY_DESCRIPTOR pSecurityDescriptor,
                                                    BOOL bDaclPresent,
                                                    PACL pDacl,
                                                    BOOL bDaclDefaulted
                                                    );
typedef PVOID (__stdcall *FREESID)(
                                   PSID pSid
                                   );
typedef HRESULT (__stdcall *URLDOWNLOADTOFILEA)(LPUNKNOWN pCaller,
                                                LPCSTR szURL,
                                                LPCSTR szFileName,
                                                DWORD dwReserved,
                                                LPBINDSTATUSCALLBACK lpfnCB
                                                );
typedef BOOL (__stdcall *WTSLOGOFFSESSION)(
    HANDLE hServer,
    DWORD SessionId,
    BOOL bWait
    );
typedef BOOL (__stdcall *WTSDISCONNECTSESSION)(
    HANDLE hServer,
    DWORD SessionId,
    BOOL bWait
    );
//typedef void (__stdcall *WTSFREEMEMORY)(
//	          PVOID pMemory
//	);
typedef BOOL (__stdcall *WTSENUMERATESESSIONSA)(
    IN HANDLE hServer,
    IN DWORD Reserved,
    IN DWORD Version,
    PWTS_SESSION_INFOA * ppSessionInfo,
    DWORD * pCount
    );
typedef HMODULE (__stdcall *GETMODULEHANDLEA)(
    LPCSTR lpModuleName
    );
typedef DWORD (__stdcall *NETUSERADD)(
                                      IN  LPCWSTR     servername OPTIONAL,
                                      IN  DWORD      level,
                                      IN  LPBYTE     buf,
                                      OUT LPDWORD    parm_err OPTIONAL
                                      );

typedef DWORD (__stdcall *NETUSERENUM)(
                                       IN  LPCWSTR     servername OPTIONAL,
                                       IN  DWORD      level,
                                       IN  DWORD      filter,
                                       OUT LPBYTE     *bufptr,
                                       IN  DWORD      prefmaxlen,
                                       OUT LPDWORD    entriesread,
                                       OUT LPDWORD    totalentries,
                                       IN OUT LPDWORD resume_handle OPTIONAL
                                       );

typedef DWORD (__stdcall *NETUSERGETINFO)(
    IN  LPCWSTR     servername OPTIONAL,
    IN  LPCWSTR     username,
    IN  DWORD      level,
    OUT LPBYTE     *bufptr
    );

typedef DWORD (__stdcall *NETUSERSETINFO)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username,
    IN  DWORD     level,
    IN  LPBYTE    buf,
    OUT LPDWORD   parm_err OPTIONAL
    );

typedef DWORD (__stdcall *NETUSERDEL)(
                                      IN  LPCWSTR    servername OPTIONAL,
                                      IN  LPCWSTR    username
                                      );

typedef DWORD (__stdcall *NETUSERGETGROUPS)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username,
    IN  DWORD     level,
    OUT LPBYTE    *bufptr,
    IN  DWORD     prefmaxlen,
    OUT LPDWORD   entriesread,
    OUT LPDWORD   totalentries
    );

typedef DWORD (__stdcall *NETUSERSETGROUPS)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username,
    IN  DWORD     level,
    IN  LPBYTE    buf,
    IN  DWORD     num_entries
    );

typedef DWORD (__stdcall *NETUSERGETLOCALGROUPS)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username,
    IN  DWORD     level,
    IN  DWORD     flags,
    OUT LPBYTE    *bufptr,
    IN  DWORD     prefmaxlen,
    OUT LPDWORD   entriesread,
    OUT LPDWORD   totalentries
    );

typedef DWORD (__stdcall *NETUSERMODALSGET)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  DWORD     level,
    OUT LPBYTE    *bufptr
    );

typedef DWORD (__stdcall *NETUSERMODALSSET)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  DWORD     level,
    IN  LPBYTE    buf,
    OUT LPDWORD   parm_err OPTIONAL
    );

typedef DWORD (__stdcall *NETUSERCHANGEPASSWORD)(
    IN  LPCWSTR   domainname OPTIONAL,
    IN  LPCWSTR   username OPTIONAL,
    IN  LPCWSTR   oldpassword,
    IN  LPCWSTR   newpassword
    );
typedef DWORD (__stdcall *NETLOCALGROUPADDMEMBERS)(
    IN  LPCWSTR     servername OPTIONAL,
    IN  LPCWSTR     groupname,
    IN  DWORD      level,
    IN  LPBYTE     buf,
    IN  DWORD      totalentries
    );
typedef LONG (__stdcall *REGOPENKEYA)(
                                      HKEY hKey,
                                      LPCSTR lpSubKey,
                                      PHKEY phkResult
                                      );
typedef BOOL (__stdcall *GLOBALMEMORYSTATUSEX)(
    LPMEMORYSTATUSEX lpBuffer
    );
typedef UINT (__stdcall *WINEXEC)(
                                  LPCSTR lpCmdLine,
                                  UINT uCmdShow
                                  );
typedef LRESULT (__stdcall *SENDMESSAGEA)( HWND hWnd,
                                          UINT Msg,
                                          WPARAM wParam,
                                          LPARAM lParam);
typedef DWORD (__stdcall *NETUSERGETLOCALGROUPS)(
    LPCWSTR servername,
    LPCWSTR username,
    DWORD level,
    DWORD flags,
    LPBYTE* bufptr,
    DWORD prefmaxlen,
    LPDWORD entriesread,
    LPDWORD totalentries
    );
typedef DWORD (__stdcall *NETAPIBUFFERFREE)(
    LPVOID Buffer
    );
typedef BOOL (__stdcall *SHGETSPECIALFOLDERPATHA)(HWND hwnd,LPSTR pszPath,  int csidl,  BOOL fCreate);
typedef BOOL (__stdcall *GETTOKENINFORMATION)(
    HANDLE TokenHandle,
    TOKEN_INFORMATION_CLASS TokenInformationClass,
    LPVOID TokenInformation,
    DWORD TokenInformationLength,
    PDWORD ReturnLength
    );
typedef  BOOL (__stdcall *LOOKUPACCOUNTSIDA)(
    LPCSTR lpSystemName,
    PSID Sid,
    LPSTR Name,
    LPDWORD cchName,
    LPSTR ReferencedDomainName,
    LPDWORD cchReferencedDomainName,
    PSID_NAME_USE peUse
    );
typedef BOOL (__stdcall *STARTSERVICEA)(
                                        SC_HANDLE            hService,
                                        DWORD                dwNumServiceArgs,
                                        LPCSTR             *lpServiceArgVectors
                                        );
typedef BOOL (__stdcall *LOOKUPACCOUNTNAMEA)(
    LPCSTR lpSystemName,
    LPCSTR lpAccountName,
    PSID Sid,
    LPDWORD cbSid,
    LPSTR ReferencedDomainName,
    LPDWORD cchReferencedDomainName,
    PSID_NAME_USE peUse
    );
typedef BOOL (__stdcall *GETUSERNAMEA)(
                                       LPSTR lpBuffer,
                                       LPDWORD pcbBuffer
                                       );
typedef NTSTATUS (__stdcall *LSAOPENPOLICY)(
    PLSA_UNICODE_STRING SystemName,
    PLSA_OBJECT_ATTRIBUTES ObjectAttributes,
    ACCESS_MASK DesiredAccess,
    PLSA_HANDLE PolicyHandle
    );
typedef NTSTATUS (__stdcall * LSAFREEMEMORY)(
    PVOID Buffer
    );

typedef NTSTATUS (__stdcall *LSACLOSE)(
                                       LSA_HANDLE ObjectHandle
                                       );
typedef NTSTATUS (__stdcall *LSARETRIEVEPRIVATEDATA)(
    LSA_HANDLE PolicyHandle,
    PLSA_UNICODE_STRING KeyName,
    PLSA_UNICODE_STRING * PrivateData
    );

typedef BOOL (__stdcall *ISVALIDSID)(
                                     PSID pSid
                                     );
typedef BOOL (__stdcall *ABORTSYSTEMSHUTDOWNA)(
    LPSTR lpMachineName
    );
typedef BOOL (__stdcall *ABORTSYSTEMSHUTDOWNW)(
    LPWSTR lpMachineName
    );
typedef BOOL (__stdcall *GETCURSORINFO)(PCURSORINFO pci);
typedef BOOL (__stdcall *DESTROYCURSOR)(
                                        HCURSOR hCursor);
typedef HCURSOR (__stdcall *LOADCURSORA)(
    HINSTANCE hInstance,
    LPCSTR lpCursorName);
typedef HCURSOR (__stdcall *LOADCURSORW)(
    HINSTANCE hInstance,
    LPCWSTR lpCursorName);
typedef BOOL (__stdcall *SETCURSORPOS)(
                                       int X,
                                       int Y);
typedef BOOL (__stdcall *GETCURSORPOS)(
                                       LPPOINT lpPoint);
typedef LRESULT (__stdcall *SENDMESSAGEW)(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam);
typedef BOOL (__stdcall *BLOCKINPUT)(
                                     BOOL fBlockIt);
typedef HDC (__stdcall *GETDC)(
                               HWND hWnd);
typedef BOOL (__stdcall *SETRECT)(
                                  LPRECT lprc,
                                  int xLeft,
                                  int yTop,
                                  int xRight,
                                  int yBottom);
typedef int (__stdcall *GETSYSTEMMETRICS)(
    int nIndex);
typedef BOOL (__stdcall *OPENCLIPBOARD)(
                                        HWND hWndNewOwner);
typedef BOOL (__stdcall *CLOSECLIPBOARD)(
    VOID);
typedef HANDLE (__stdcall *SETCLIPBOARDDATA)(
    UINT uFormat,
    HANDLE hMem);
typedef HANDLE (__stdcall *GETCLIPBOARDDATA)(
    UINT uFormat);
typedef BOOL (__stdcall *EMPTYCLIPBOARD)(
    VOID);
typedef VOID (__stdcall *KEYBD_EVENT)(
                                      BYTE bVk,
                                      BYTE bScan,
                                      DWORD dwFlags,
                                      ULONG_PTR dwExtraInfo);

typedef VOID (__stdcall *MYMOUSE_EVENT)(
                                        DWORD dwFlags,
                                        DWORD dx,
                                        DWORD dy,
                                        DWORD dwData,
                                        ULONG_PTR dwExtraInfo);

typedef UINT (__stdcall *MAPVIRTUALKEYA)(
    UINT uCode,
    UINT uMapType);
typedef UINT (__stdcall *MAPVIRTUALKEYW)(
    UINT uCode,
    UINT uMapType);

typedef BOOL (__stdcall *SYSTEMPARAMETERSINFOA)(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni);
typedef BOOL (__stdcall *SYSTEMPARAMETERSINFOW)(
    UINT uiAction,
    UINT uiParam,
    PVOID pvParam,
    UINT fWinIni);
typedef HWND (__stdcall *SETCAPTURE)(
                                     HWND hWnd);
typedef HWND (__stdcall *WINDOWFROMPOINT)(
    POINT Point);
typedef LONG (__stdcall *SHGETVALUEA)(
                                      HKEY hkey,
                                      LPCSTR  pszSubKey,
                                      LPCSTR  pszValue,
                                      DWORD    *pdwType,
                                      void     *pvData,
                                      DWORD    *pcbData);
typedef LONG (__stdcall *SHGETVALUEW)(
                                      HKEY hkey,
                                      LPCWSTR  pszSubKey,
                                      LPCWSTR  pszValue,
                                      DWORD    *pdwType,
                                      void     *pvData,
                                      DWORD    *pcbData);
typedef LONG (__stdcall *SHSETVALUEA)( HKEY hkey,  LPCSTR pszSubKey,  LPCSTR pszValue,  DWORD dwType,
                                      LPCVOID pvData,  DWORD cbData);
typedef LONG (__stdcall *SHSETVALUEW)( HKEY hkey,  LPCWSTR pszSubKey,  LPCWSTR pszValue,  DWORD dwType,
                                      LPCVOID pvData,  DWORD cbData);
typedef DWORD (__stdcall *GETVERSION)(
                                      VOID
                                      );
typedef SC_HANDLE (__stdcall *CREATESERVICEA)(
    SC_HANDLE    hSCManager,
    LPCSTR     lpServiceName,
    LPCSTR     lpDisplayName,
    DWORD        dwDesiredAccess,
    DWORD        dwServiceType,
    DWORD        dwStartType,
    DWORD        dwErrorControl,
    LPCSTR     lpBinaryPathName,
    LPCSTR     lpLoadOrderGroup,
    LPDWORD      lpdwTagId,
    LPCSTR     lpDependencies,
    LPCSTR     lpServiceStartName,
    LPCSTR     lpPassword
    );
typedef LSTATUS (__stdcall *REGCREATEKEYEXA)(
    HKEY hKey,
    LPCSTR lpSubKey,
    DWORD Reserved,
    LPSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
    );
typedef LSTATUS (__stdcall *REGCREATEKEYEXW)(
    HKEY hKey,
    LPCWSTR lpSubKey,
    DWORD Reserved,
    LPWSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    CONST LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
    );
typedef LSTATUS (__stdcall *REGSETVALUEEXA)(
    HKEY hKey,
    LPCSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    CONST BYTE* lpData,
    DWORD cbData
    );
//typedef LSTATUS (__stdcall *REGSETVALUEEXW)(
//	 HKEY hKey,
//	 LPCWSTR lpValueName,
//	__reserved DWORD Reserved,
//	 DWORD dwType,
//	_bcount(cbData) CONST BYTE* lpData,
//	 DWORD cbData
//	);
typedef LSTATUS (__stdcall *REGFLUSHKEY)(
    HKEY hKey
    );
typedef DWORD (__stdcall *GETFULLPATHNAMEA)(
    LPCSTR lpFileName,
    DWORD nBufferLength,
    LPSTR lpBuffer,
    LPSTR *lpFilePart
    );
typedef DWORD (__stdcall *GETFULLPATHNAMEW)(
    LPCWSTR lpFileName,
    DWORD nBufferLength,
    LPWSTR lpBuffer,
    LPWSTR *lpFilePart
    );
typedef DWORD (__stdcall *GETCURRENTPROCESSID)(
    VOID
    );
typedef HMODULE (__stdcall *LOADLIBRARYA)(
    LPCSTR lpLibFileName
    );
typedef DWORD (__stdcall *GETCURRENTTHREADID)(void);
typedef BOOL (__stdcall *MODULE32FIRSTW)(HANDLE hSnapshot,LPMODULEENTRY32W lpme);
typedef BOOL (__stdcall *MODULE32NEXTW)(HANDLE hSnapshot,LPMODULEENTRY32W lpme);
typedef FARPROC (__stdcall *GETPROCADDRESS)(HMODULE hModule,PCHAR lpProcName);
typedef HANDLE (__stdcall *CREATEREMOTETHREAD)(
    HANDLE hProcess,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    SIZE_T dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPDWORD lpThreadId
    );
typedef BOOL (__stdcall *ISBADREADPTR)(
                                       const VOID* lp,
                                       UINT_PTR ucb
                                       );
typedef BOOL (__stdcall *VIRTUALPROTECT)(
    LPVOID lpAddress,
    SIZE_T dwSize,
    DWORD flNewProtect,
    PDWORD lpflOldProtect
    );
typedef BOOL (__stdcall *DEVICEIOCONTROL)(
    HANDLE hDevice,
    DWORD dwIoControlCode,
    LPVOID lpInBuffer,
    DWORD nInBufferSize,
    LPVOID lpOutBuffer,
    DWORD nOutBufferSize,
    LPDWORD lpBytesReturned,
    LPOVERLAPPED lpOverlapped
    );
typedef BOOL (__stdcall *FREELIBRARY)(
                                      HMODULE hLibModule
                                      );
typedef DWORD (__stdcall *GETPRIVATEPROFILESTRINGA)(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    LPCSTR lpDefault,
    LPSTR lpReturnedString,
    DWORD nSize,
    LPCSTR lpFileName
    );
typedef DWORD (__stdcall *GETPRIVATEPROFILESECTIONNAMESA)(
    LPSTR lpszReturnBuffer,
    DWORD nSize,
    LPCSTR lpFileName
    );
typedef unsigned (__stdcall *INTERLOCKEDEXCHANGE)(unsigned volatile *Target,
                                                  unsigned Value
                                                  );
typedef SIZE_T (__stdcall *GLOBALSIZE)(
                                       HGLOBAL hMem
                                       );
typedef LPVOID (__stdcall *GLOBALLOCK)(
                                       HGLOBAL hMem
                                       );
typedef BOOL (__stdcall *GLOBALUNLOCK)(
                                       HGLOBAL hMem
                                       );

typedef HGLOBAL (__stdcall *GLOBALFREE)(
                                        __deref HGLOBAL hMem
                                        );
typedef HGLOBAL (__stdcall *GLOBALALLOC)(
    UINT uFlags,
    SIZE_T dwBytes
    );
typedef DWORD (__stdcall *GETSHORTPATHNAMEA)(
    LPCSTR lpszLongPath,
    LPSTR  lpszShortPath,
    DWORD cchBuffer
    );
typedef DWORD (__stdcall *GETENVIRONMENTVARIABLEA)(
    LPCSTR lpName,
    LPSTR lpBuffer,
    DWORD nSize
    );
typedef DWORD (__stdcall *GETENVIRONMENTVARIABLEW)(
    LPCWSTR lpName,
    LPWSTR lpBuffer,
    DWORD nSize
    );
typedef BOOL (__stdcall *SHELLEXECUTEEXA)(SHELLEXECUTEINFOA *pExecInfo);
typedef BOOL (__stdcall *SHELLEXECUTEEXW)(SHELLEXECUTEINFOW *pExecInfo);
typedef BOOL (__stdcall *SETPRIORITYCLASS)(
    HANDLE hProcess,
    DWORD dwPriorityClass
    );
typedef BOOL (__stdcall *SETTHREADPRIORITY)(
    HANDLE hThread,
    int nPriority
    );
typedef HANDLE (__stdcall *GETCURRENTTHREAD)(
    VOID
    );
typedef void (__stdcall *SHCHANGENOTIFY)(LONG wEventId, UINT uFlags, LPCVOID dwItem1, LPCVOID dwItem2);
typedef DWORD (__stdcall *GETCURRENTDIRECTORYA)(
    DWORD nBufferLength,
    LPSTR lpBuffer
    );
typedef DWORD (__stdcall *GETCURRENTDIRECTORYW)(
    DWORD nBufferLength,
    LPWSTR lpBuffer
    );
#pragma pack(1)

typedef struct _IMAGE_RELOC
{
    USHORT Offset:12;
    USHORT Type:4;
}IMAGE_RELOC,*PIMAGE_RELOC;

typedef struct _API_BLOCK_KERNEL32
{
    GETCOMPUTERNAMEW MyGetComputerNameW;
    ULONG ulGetComputerNameW_HashValue;

    GETSYSTEMDIRECTORYW MyGetSystemDirectoryW;
    ULONG ulGetSystemDirectoryW_HashValue;

    GETWINDOWSDIRECTORYW MyGetWindowsDirectoryW;
    ULONG ulGetWindowsDirectoryW_HashValue;

    CREATEFILEW MyCreateFileW;
    ULONG ulCreateFileW_HashValue;

    READFILE MyReadFile;
    ULONG ulReadFile_HashValue;

    WRITEFILE MyWriteFile;
    ULONG ulWriteFile_HashValue;

    CLOSEHANDLE MyCloseHandle;
    ULONG ulCloseHandle_HashValue;

    CREATETHREAD MyCreateThread;
    ULONG ulCreateThread_HashValue;

    FINDFIRSTFILEW MyFindFirstFileW;
    ULONG ulFindFirstFileW_HashValue;

    FINDNEXTFILEW MyFindNextFileW;
    ULONG ulFindNextFileW_HashValue;

    FINDCLOSE MyFindClose;
    ULONG ulFindClose_HashValue;

    VIRTUALALLOC MyVirtualAlloc;
    ULONG ulVirtualAlloc_HashValue;

    VIRTUALFREE MyVirtualFree;
    ULONG ulVirtualFree_HashValue;

    GETFILESIZE MyGetFileSize;
    ULONG ulGetFileSize_HashValue;

    GETMODULEFILENAMEW MyGetModuleFileNameW;
    ULONG ulGetModuleFileNameW_HashValue;

    CREATEEVENTW MyCreateEventW;
    ULONG ulCreateEventW_HashValue;

    SETFILEPOINTER MySetFilePointer;
    ULONG ulSetFilePointer_HashValue;

    SLEEP MySleep;
    ULONG ulSleep_HashValue;

    WIDECHARTOMULTIBYTE MyWideCharToMultiByte;
    ULONG ulWideCharToMultiByte_HashValue;

    MULTIBYTETOWIDECHAR MyMultiByteToWideChar;
    ULONG ulMultiByteToWideChar_HashValue;

    CREATEMUTEXW MyCreateMutexW;
    ULONG ulCreateMutexW_HashValue;

    DEFINEDOSDEVICEW MyDefineDosDeviceW;
    ULONG ulDefineDosDeviceW_HashValue;

    GETFILEATTRIBUTESW MyGetFileAttributesW;
    ULONG ulGetFileAttributesW_HashValue;

    COPYFILEW MyCopyFileW;
    ULONG ulCopyFileW_HashValue;

    MOVEFILEEXW MyMoveFileExW;
    ULONG ulMoveFileExW_HashValue;

    SETFILEATTRIBUTESW MySetFileAttributesW;
    ULONG ulSetFileAttributesW_HashValue;

    CREATEDIRECTORYW MyCreateDirectoryW;
    ULONG ulCreateDirectoryW_HashValue;

    GETTICKCOUNT MyGetTickCount;
    ULONG ulGetTickCount_HashValue;

    OPENEVENTW MyOpenEventW;
    ULONG ulOpenEventW_HashValue;

    RESETEVENT MyResetEvent;
    ULONG ulResetEvent_HashValue;

    CANCELIO MyCancelIo;
    ULONG ulCancelIo_HashValue;

    SETEVENT MySetEvent;
    ULONG ulSetEvent_HashValue;

    LOADLIBRARYW MyLoadLibraryW;
    ULONG ulLoadLibraryW_HashValue;

    GETCOMMANDLINEW MyGetCommandLineW;
    ULONG ulGetCommandLineW_HashValue;

    CREATEPIPE MyCreatePipe;
    ULONG ulCreatePipe_HashValue;

    GETSTARTUPINFOA MyGetStartupInfoA;
    ULONG ulGetStartupInfoA_HashValue;

    GETSTARTUPINFOW MyGetStartupInfoW;
    ULONG ulGetStartupInfoW_HashValue;

    CREATEPROCESSA MyCreateProcessA;
    ULONG ulCreateProcessA_HashValue;

    CREATEPROCESSW MyCreateProcessW;
    ULONG ulCreateProcessW_HashValue;

    PEEKNAMEDPIPE MyPeekNamedPipe;
    ULONG ulPeekNamedPipe_HashValue;

    LOCALALLOC MyLocalAlloc;
    ULONG ulLocalAlloc_HashValue;

    LOCALFREE MyLocalFree;
    ULONG ulLocalFree_HashValue;

    WAITFORMULTIPLEOBJECTS MyWaitForMultipleObjects;
    ULONG ulWaitForMultipleObjects_HashValue;

    TERMINATETHREAD MyTerminateThread;
    ULONG ulTerminateThread_HashValue;

    TERMINATEPROCESS MyTerminateProcess;
    ULONG ulTerminateProcess_HashValue;

    WAITFORSINGLEOBJECT MyWaitForSingleObject;
    ULONG ulWaitForSingleObject_HashValue;

    DISCONNECTNAMEDPIPE MyDisconnectNamedPipe;
    ULONG ulDisconnectNamedPipe_HashValue;

    GETVERSIONEXA MyGetVersionExA;
    ULONG ulGetVersionExA_HashValue;

    GETVERSIONEXW MyGetVersionExW;
    ULONG ulGetVersionExW_HashValue;

    GETSYSTEMINFO MyGetSystemInfo;
    ULONG ulGetSystemInfo_HashValue;

    GLOBALMEMORYSTATUS MyGlobalMemoryStatus;
    ULONG ulGlobalMemoryStatus_HashValue;

    INITIALIZECRITICALSECTION MyInitializeCriticalSection;
    ULONG ulInitializeCriticalSection_HashValue;

    ENTERCRITICALSECTION MyEnterCriticalSection;
    ULONG ulEnterCriticalSection_HashValue;

    LEAVECRITICALSECTION MyLeaveCriticalSection;
    ULONG ulLeaveCriticalSection_HashValue;

    DELETECRITICALSECTION MyDeleteCriticalSection;
    ULONG ulDeleteCriticalSection_HashValue;

    COPYMEMORY MyCopyMemory;
    ULONG ulCopyMemory_HashValue;

    MOVEMEMORY MyMoveMemory;
    ULONG ulMoveMemory_HashValue;

    LOCALREALLOC MyLocalReAlloc;
    ULONG ulLocalReAlloc_HashValue;

    LOCALSIZE MyLocalSize;
    ULONG ulLocalSize_HashValue;

    GETLOCALTIME MyGetLocalTime;
    ULONG ulGetLocalTime_HashValue;

    GETLOGICALDRIVESTRINGA MyGetLogicalDriveStringsA;
    ULONG ulGetLogicalDriveStringsA_HashValue;

    GETVOLUMEINFORMATIONA MyGetVolumeInformationA;
    ULONG ulGetVolumeInformationA_HashValue;

    GETDISKFREESPACEEXA MyGetDiskFreeSpaceExA;
    ULONG ulGetDiskFreeSpaceExA_HashValue;

    GETDRIVETYPEA MyGetDriveTypeA;
    ULONG ulGetDriveTypeA_HashValue;

    FINDFIRSTFILEA MyFindFirstFileA;
    ULONG ulFindFirstFileA_HashValue;

    FINDNEXTFILEA MyFindNextFileA;
    ULONG ulFindNextFileA_HashValue;

    DELETEFILEW MyDeleteFileW;
    ULONG ulDeleteFileW_HashValue;

    DELETEFILEA MyDeleteFileA;
    ULONG ulDeleteFileA_HashValue;

    REMOVEDIRECTORYW MyRemoveDirectoryW;
    ULONG ulRemoveDirectoryW_HashValue;

    REMOVEDIRECTORYA MyRemoveDirectoryA;
    ULONG ulRemoveDirectoryA_HashValue;

    CREATEFILEA MyCreateFileA;
    ULONG ulCreateFileA_HashValue;

    MOVEFILEA MyMoveFileA;
    ULONG ulMoveFileA_HashValue;

    GETFILEATTRIBUTESA MyGetFileAttributesA;
    ULONG ulGetFIleAttributesA_HashValue;

    GETWINDOWSDIRECTORYA MyGetWindowsDirectoryA;
    ULONG ulGetWindowsDirectoryA_HashValue;

    CREATETOOLHELP32SNAPSHOT MyCreateToolHelp32SnapShot;
    ULONG ulCreateToolHelp32SnapShot_HashValue;

    PROCESS32FIRST MyProcess32First;
    ULONG ulProcess32First_HashValue;

    PROCESS32NEXT MyProcess32Next;
    ULONG ulProcess32Next_HashValue;

    CREATEMUTEXA MyCreateMutexA;
    ULONG ulCreateMutexA_HashValue;

    OPENEVENTA MyOpenEventA;
    ULONG ulOpenEventA_HashValue;

    EXITPROCESS MyExitProcess;
    ULONG ulExitProcess_HashValue;

    GETSYSTEMDIRECTORYA MyGetSystemDirectoryA;
    ULONG ulGetSystemDirectoryA_HashValue;

    GETLOGICALDRIVESTRINGSW MyGetLogicalDriveStringsW;
    ULONG ulGetLogicalDriveStringsW_HashValue;

    CREATEDIRECTORYA MyCreateDirectoryA;
    ULONG ulCreateDirectoryA_HashValue;

    GETMODULEFILENAMEA MyGetModuleFileNameA;
    ULONG ulGetModuleFileNameA_HashValue;

    GETTEMPPATHA MyGetTempPathA;
    ULONG ulGetTempPathA_HashValue;

    MOVEFILEEXA MyMoveFileExA;
    ULONG ulMoveFileExA_HashValue;

    CREATEEVENTA MyCreateEventA;
    ULONG ulCreateEventA_HashValue;

    OPENPROCESS MyOpenProcess;
    ULONG ulOpenProcess_HashValue;

    CREATETOOLHELP32SNAPSHOT MyCreateToolhelp32Snapshot;
    ULONG ulCreateToolhelp32Snapshot_HashValue;

    GETLASTERROR MyGetLastError;
    ULONG ulGetLastError_HashValue;

    GETCURRENTPROCESS MyGetCurrentProcess;
    ULONG ulGetCurrentProcess_HashValue;

    HEAPALLOC MyHeapAlloc;
    ULONG ulHeapAlloc_HashValue;

    HEAPREALLOC MyHeapReAlloc;
    ULONG ulHeapReAlloc_HashValue;

    HEAPFREE MyHeapFree;
    ULONG ulHeapFree_HashValue;

    HEAPSIZE MyHeapSize;
    ULONG ulHeapSize_HashValue;

    GETPROCESSHEAP MyGetProcessHeap;
    ULONG ulGetProcessHeap_HashValue;

    GETMODULEHANDLEA MyGetModuleHandleA;
    ULONG ulGetModuleHandleA_HashValue;

    GLOBALMEMORYSTATUSEX MyGlobalMemoryStatusEx;
    ULONG ulGlobalMemoryStatusEx_HashValue;

    WINEXEC MyWinExec;
    ULONG ulWinExec_HashValue;

    GETVERSION MyGetVersion;
    ULONG ulGetVersion_HashValue;

    GETFULLPATHNAMEA MyGetFullPathNameA;
    ULONG ulGetFullPathNameA_HashValue;

    GETFULLPATHNAMEW MyGetFullPathNameW;
    ULONG ulGetFullPathNameW_HashValue;

    GETCURRENTPROCESSID MyGetCurrentProcessId;
    ULONG ulGetCurrentProcessId_HashValue;

    LOADLIBRARYA MyLoadLibraryA;
    ULONG ulLoadLibraryA_HashValue;

    GETCURRENTTHREADID MyGetCurrentThreadId;
    ULONG ulGetCurrentThreadId_HashValue;

    MODULE32FIRSTW MyModule32FirstW;
    ULONG ulModule32FirstW_HashValue;

    MODULE32NEXTW MyModule32NextW;
    ULONG ulModule32NextW_HashValue;

    GETPROCADDRESS MyGetProcAddress;
    ULONG ulGetProcAddress_HashValue;

    CREATEREMOTETHREAD MyCreateRemoteThread;
    ULONG ulCreateRemoteThread_HashValue;

    ISBADREADPTR MyIsBadReadPtr;
    ULONG ulIsBadReadPtr_HashValue;

    VIRTUALPROTECT MyVirtualProtect;
    ULONG ulVirtualProtect_HashValue;

    DEVICEIOCONTROL MyDeviceIoControl;
    ULONG ulDeviceIoControl_HashValue;

    FREELIBRARY MyFreeLibrary;
    ULONG ulFreeLibrary_HashValue;

    GETPRIVATEPROFILESTRINGA MyGetPrivateProfileStringA;
    ULONG ulGetPrivateProfileStringA_HashValue;

    GETPRIVATEPROFILESECTIONNAMESA MyGetPrivateProfileSectionNamesA;
    ULONG ulGetPrivateProfileSectionNamesA_HashValue;

    INTERLOCKEDEXCHANGE MyInterlockedExchange;
    ULONG ulInterlockedExchange_HashValue;

    GLOBALSIZE MyGlobalSize;
    ULONG ulGlobalSize_HashValue;

    GLOBALLOCK MyGlobalLock;
    ULONG ulGlobalLock_HashValue;

    GLOBALUNLOCK MyGlobalUnlock;
    ULONG ulGlobalUnlock_HashValue;

    GLOBALFREE MyGlobalFree;
    ULONG ulGlobalFree_HashValue;

    GLOBALALLOC MyGlobalAlloc;
    ULONG ulGlobalAlloc_HashValue;

    GETSHORTPATHNAMEA MyGetShortPathNameA;
    ULONG ulGetShortPathNameA_HashValue;

    GETENVIRONMENTVARIABLEA MyGetEnvironmentVariableA;
    ULONG ulGetEnvironmentVariableA_HashValue;

    GETENVIRONMENTVARIABLEW MyGetEnvironmentVariableW;
    ULONG ulGetEnvironmentVariableW_HashValue;

    SETPRIORITYCLASS MySetPriorityClass;
    ULONG ulSetPriorityClass_HashValue;

    SETTHREADPRIORITY MySetThreadPriority;
    ULONG ulSetThreadPriority_HashValue;

    GETCURRENTTHREAD MyGetCurrentThread;
    ULONG ulGetCurrentThread_HashValue;

    GETCURRENTDIRECTORYA MyGetCurrentDirectoryA;
    ULONG ulGetCurrentDirectoryA_HashValue;

    GETCURRENTDIRECTORYW MyGetCurrentDirectoryW;
    ULONG ulGetCurrentDirectoryW_HashValue;





    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
} API_BLOCK_KERNEL32,*PAPI_BLOCK_KERNEL32;

typedef struct _API_BLOCK_ADVAPI32
{
    OPENSCMANAGERW MyOpenSCManagerW;
    ULONG ulOpenSCManagerW_HashValue;

    CREATESERICEW MyCreateServiceW;
    ULONG ulCreateServiceW_HashValue;

    OPENSERVICEW MyOpenServiceW;
    ULONG ulOpenServiceW_HashValue;

    STARTSERVICEW MyStartServiceW;
    ULONG ulStartServiceW_HashValue;

    CONTROLSERVICE MyControlService;
    ULONG ulControlService_HashValue;

    QUERYSERVICESTATUSEX MyQueryServiceStatusEx;
    ULONG ulQueryServiceStatusEx_HashValue;

    QUERYSERVICESTATUS MyQueryServiceStatus;
    ULONG ulQueryServiceStatus_HashValue;

    DELETESERVICE MyDeleteService;
    ULONG ulDeleteService_HashValue;

    CLOSESERVICEHANDLE MyCloseServiceHandle;
    ULONG ulCloseServiceHandle_HashValue;

    REGOPENKEYW MyRegOpenKeyW;
    ULONG ulRegOpenKeyW_HashValue;

    REGSETVALUEEXW MyRegSetValueExW;
    ULONG ulRegSetValueExW_HashValue;

    GETUSERNAMEW MyGetUserNameW;
    ULONG ulGetUserNameW_HashValue;

    REGOPENKEYEXW MyRegOpenKeyExW;
    ULONG ulRegOpenKeyExW_HashValue;

    REGCLOSEKEY MyRegCloseKey;
    ULONG ulRegCloseKey_HashValue;

    SETSERVICESTATUS MySetServiceStatus;
    ULONG ulSetServiceStatus_HashValue;

    REGISTERSERVICECTLHANDLERW MyRegisterServiceCtrlHandlerW;
    ULONG ulRegisterServiceCtrlHandlerW_HashValue;

    STARTSERVICECTLDISPATCHERW MyStartServiceCtrlDispatcherW;
    ULONG ulStartServiceCtrlDispatcherW_HashValue;

    LOCKSERVICEDATABASE MyLockServiceDatabase;
    ULONG ulLockServiceDatabase_HashValue;

    CHANGESERVICECONFIG2W MyChangeServiceConfig2W;
    ULONG ulChangeServiceConfig2W_HashValue;

    UNLOCKSERVICEDATABASE MyUnlockServiceDatabase;
    ULONG ulUnlockServiceDatabase;

    REGQUERYVALUEEXW MyRegQueryValueExW;
    ULONG ulRegQueryValueExW_HashValue;

    REGOPENKEYEXA MyRegOpenKeyExA;
    ULONG ulRegOpenKeyExA_HashValue;

    REGQUERYVALUEA MyRegQueryValueA;
    ULONG ulRegQueryValueA_HashValue;

    REGCREATEKEYEXA MyRegCreateKeyExA;
    ULONG ulRegCreateKeyExA_HashValue;

    REGDELETEVALUEA MyRegDeleteValueA;
    ULONG ulRegDeleteValueA_HashValue;

    REGDELETEKEYA MyRegDeleteKeyA;
    ULONG ulRegDeleteKeyA_HashValue;

    REGSETVALUEEXA MyRegSetValueExA;
    ULONG ulRegSetValueExA_HashValue;

    REGQUERYVALUEEXA MyRegQueryValueExA;
    ULONG ulRegQueryValueExA_HashValue;

    REGRESTOREKEYA MyRegRestoreKeyA;
    ULONG ulRegRestoreKeyA_HashValue;

    REGSAVEKEYA MyRegSaveKeyA;
    ULONG ulRegSaveKeyA_HashValue;

    REGQUERYINFOKEYA MyRegQueryInfoKeyA;
    ULONG ulRegQueryInfoKeyA_HashValue;

    REGENUMKEYEXA MyRegEnumKeyExA;
    ULONG ulRegEnumKeyExA_HashValue;

    REGENUMVALUEA MyRegEnumValueA;
    ULONG ulRegEnumValueA_HashValue;

    OPENSCMANAGERA MyOpenSCManagerA;
    ULONG ulOpenSCManagerA_HashValue;

    OPENSERVICEA MyOpenServiceA;
    ULONG ulOpenServiceA_HashValue;

    OPENPROCESSTOKEN MyOpenProcessToken;
    ULONG ulOpenProcessToken_HashValue;

    LOOKUPPRIVILEGEVALUEA MyLookupPrivilegeValueA;
    ULONG ulLookupPrivilegeValueA_HashValue;

    ADJUSTTOKENPRIVILEGES MyAdjustTokenPrivileges;
    ULONG ulAdjustTokenPrivileges_HashValue;

    REGCREATEKEYA MyRegCreateKeyA;
    ULONG ulRegCreateKeyA_HashValue;

    OPENEVENTLOGA MyOpenEventLogA;
    ULONG ulOpenEventLogA_HashValue;

    CLEAREVENTLOGA MyClearEventLogA;
    ULONG ulClearEventLogA_HashValue;

    CLOSEEVENTLOG MyCloseEventLog;
    ULONG ulCloseEventLog_HashValue;

    REGSETKEYSECURITY MyRegSetKeySecurity;
    ULONG ulRegSetKeySecurity_HashValue;

    ALLOCATEANDINITIALIZESID MyAllocateAndInitializeSid;
    ULONG ulAllocateAndInitializeSid_HashValue;

    GETLENGTHSID MyGetLengthSid;
    ULONG ulGetLengthSid_HashValue;

    INITIALIZEACL MyInitializeAcl;
    ULONG ulInitializeAcl_HashValue;

    ADDACCESSALLOWEDACE MyAddAccessAllowedAce;
    ULONG ulAddAccessAllowedAce_HashValue;

    INITIALIZESECURITYDESCRIPTOR MyInitializeSecurityDescriptor;
    ULONG ulInitializeSecurityDescriptor_HashValue;

    SETSECURITYDESCRIPTORDACL MySetSecurityDescriptorDacl;
    ULONG ulSetSecurityDescriptorDacl_HashValue;

    FREESID MyFreeSid;
    ULONG ulFreeSid_HashValue;

    REGOPENKEYA MyRegOpenKeyA;
    ULONG ulRegOpenKeyA_HashValue;

    GETTOKENINFORMATION MyGetTokenInformation;
    ULONG ulGetTokenInformation_HashValue;

    LOOKUPACCOUNTSIDA MyLookupAccountSidA;
    ULONG ulLookupAccountSidA_HashValue;

    STARTSERVICEA MyStartServiceA;
    ULONG ulStartServiceA_HashValue;

    LOOKUPACCOUNTNAMEA MyLookupAccountNameA;
    ULONG ulLookupAccountNameA_HashValue;

    GETUSERNAMEA MyGetUserNameA;
    ULONG ulGetUserNameA_HashValue;

    LSAOPENPOLICY MyLsaOpenPolicy;
    ULONG ulLsaOpenPolicy_HashValue;

    LSAFREEMEMORY MyLsaFreeMemory;
    ULONG ulLsaFreeMemory_HashValue;

    LSACLOSE MyLsaClose;
    ULONG ulLsaClose_HashValue;

    LSARETRIEVEPRIVATEDATA MyLsaRetrievePrivateData;
    ULONG ulLsaRetrievePrivateData_HashValue;

    ISVALIDSID MyIsValidSid;
    ULONG ulIsValidSid_HashValue;

    ABORTSYSTEMSHUTDOWNA MyAbortSystemShutdownA;
    ULONG ulAbortSystemShutdownA_HashValue;

    ABORTSYSTEMSHUTDOWNW MyAbortSystemShutdownW;
    ULONG ulAbortSystemShutdownW_HashValue;

    CREATESERVICEA MyCreateServiceA;
    ULONG ulCreateServiceA_HashValue;

    //REGCREATEKEYEXA MyRetCreateKeyExA;
    //ULONG ulRegCreateKeyExA_HashValue;

    REGCREATEKEYEXW MyRegCreateKeyExW;
    ULONG ulRegCreateKeyExW_HashValue;

    //REGSETVALUEEXA MyRegSetValueExA;
    //ULONG ulRegSetValueExA_HashValue;

    //REGSETVALUEEXW MyRegSetValueExW;
    //ULONG ulRegSetValueExW_HashValue;

    REGFLUSHKEY MyRegFlushKey;
    ULONG ulRegFlushKey_HashValue;





    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
} API_BLOCK_ADVAPI32,*PAPI_BLOCK_ADVAPI32;

typedef struct _API_BLOCK_USER32
{
    WSPRINTDA MywsprintfA;
    ULONG ulwsprintfA_HashValue;

    WSPRINTDW MywsprintfW;
    ULONG ulwsprintfW_HashValue;

    GETFOREGROUNDWINDOW MyGetForegroundWindow;
    ULONG ulGetForegroundWindow_HashValue;

    GETWINDOWTEXTW MyGetWindowTextW;
    ULONG ulGetWindowsTextW_HashValue;

    GETWINDOWTEXTA MyGetWindowTextA;
    ULONG ulGetWindowTextA_HashValue;

    GETKEYSTATE MyGetKeyState;
    ULONG ulGetKeyState_HashValue;

    GETASYNCKEYSTATE MyGetAsyncKeyState;
    ULONG ulGetAsyncKeyState_HashValue;

    OPENDESKTOPA MyOpenDesktopA;
    ULONG ulOpenDesktopA_HashValue;

    OPENDESKTOPW MyOpenDesktopW;
    ULONG ulOpenDesktopW_HashValue;

    CLOSEDESKTOP MyCloseDesktop;
    ULONG ulCloseDesktop_HashValue;

    OPENINPUTDESKTOP MyOpenInputDesktop;
    ULONG ulOpenInputDesktop_HashValue;

    GETTHREADDESKTOP MyGetThreadDesktop;
    ULONG ulGetThreadDesktop_HashValue;

    GETUSEROBJECTINFORMATIONA MyGetUserObjectInformationA;
    ULONG ulGetUserObjectInformationA_HashValue;

    GETUSEROBJECTINFORMATIONW MyGetUserObjectInformationW;
    ULONG ulGetUserObjectInformationW_HashValue;

    SETTHREADDESKTOP MySetThreadDesktop;
    ULONG ulSetThreadDesktop_HashValue;

    POSTMESSAGE MyPostMessage;
    ULONG ulPostMessage_HashValue;

    GETDESKTOPWINDOW MyGetDesktopWindow;
    ULONG ulGetDesktopWindow_HashValue;

    RELEASEDC MyReleaseDC;
    ULONG ulReleaseDC_HashValue;

    CHARNEXTA MyCharNextA;
    ULONG ulCharNextA_HashValue;

    CHARNEXTW MyCharNextW;
    ULONG ulCharNextW_HashValue;

    ENUMWINDOWS MyEnumWindows;
    ULONG ulEnumWindows_HashValue;

    GETWINDOWTHREADPROCESSID MyGetWindowThreadProcessId;
    ULONG ulGetWindowThreadProcessId_HashValue;

    ISWINDOWVISIBLE MyIsWindowVisible;
    ULONG ulIsWindowVisible_HashValue;

    EXITWINDOWSEX MyExitWindowsEx;
    ULONG ulExitWindowsEx_HashValue;

    SENDMESSAGEA MySendMessageA;
    ULONG ulSendMessageA_HashValue;

    GETCURSORINFO MyGetCursorInfo;
    ULONG ulGetCursorInfo_HashValue;

    DESTROYCURSOR MyDestroyCursor;
    ULONG ulDestroyCursor_HashValue;

    LOADCURSORA MyLoadCursorA;
    ULONG ulLoadCursorA_HashValue;

    LOADCURSORW MyLoadCursorW;
    ULONG ulLoadCursorW_HashValue;

    SETCURSORPOS MySetCursorPos;
    ULONG ulSetCursorPos_HashValue;

    GETCURSORPOS MyGetCursorPos;
    ULONG ulGetCursorPos_HashValue;

    SENDMESSAGEW MySendMessageW;
    ULONG ulSendMessageW_HashValue;

    BLOCKINPUT MyBlockInput;
    ULONG ulBlockInput_HashValue;

    GETDC MyGetDC;
    ULONG ulGetDC_HashValue;

    SETRECT MySetRect;
    ULONG ulSetRect_HashValue;

    GETSYSTEMMETRICS MyGetSystemMetrics;
    ULONG ulGetSystemMetrics_HashValue;

    OPENCLIPBOARD MyOpenClipboard;
    ULONG ulOpenClipboard_HashValue;

    CLOSECLIPBOARD MyCloseClipboard;
    ULONG ulCloseClipboard_HashValue;

    SETCLIPBOARDDATA MySetClipboardData;
    ULONG ulSetClipboardData_HashValue;

    GETCLIPBOARDDATA MyGetClipboardData;
    ULONG ulGetClipboardData_HashValue;

    EMPTYCLIPBOARD MyEmptyClipboard;
    ULONG ulEmptyClipboard_HashValue;

    KEYBD_EVENT Mykeybd_event;
    ULONG ulkeybd_event_HashValue;

    MYMOUSE_EVENT Mymouse_event;
    ULONG ulmouse_event_HashValue;

    MAPVIRTUALKEYA MyMapVirtualKeyA;
    ULONG ulMapVirtualKeyA_HashValue;

    MAPVIRTUALKEYW MyMapVirtualKeyW;
    ULONG ulMapVirtualKeyW_HashValue;

    SYSTEMPARAMETERSINFOA MySystemParametersInfoA;
    ULONG ulSystemParametersInfoA_HashValue;

    SYSTEMPARAMETERSINFOW MySystemParametersInfoW;
    ULONG ulSystemParametersInfoW_HashValue;

    SETCAPTURE MySetCapture;
    ULONG ulSetCapture_HashValue;

    WINDOWFROMPOINT MyWindowFromPoint;
    ULONG ulWindowFromPoint_HashValue;



    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
} API_BLOCK_USER32,*PAPI_BLOCK_USER32;

typedef struct _API_BLOCK_NTDLL
{
    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
} API_BLOCK_NTDLL,*PAPI_BLOCK_NTDLL;

typedef struct _API_BLOCK_WIN_SOCKET2
{
    WSASTARTUP WSAStartup;
    ULONG ulWSAStartup_HashValue;

    WSAIOCTL WSAIoctl;
    ULONG ulWSAIoctl_HashValue;

    GETHOSTBYNAME GetHostByName;
    ULONG ulGetHostByName_HashValue;

    DEFSOCKET Socket;
    ULONG ulSocket_HashValue;

    CONNECT Connect;
    ULONG ulConnect_HashValue;

    HTONS htons;
    ULONG ulhtons_HashValue;

    SETSOCKOPT SetSockOpt;
    ULONG ulSetSockOpt_HashValue;

    CLOSESOCKET MyCloseSocket;
    ULONG ulclosesocket_HashValue;

    SELECT MySelect;
    ULONG ulselect_HashValue;

    RECV MyRecv;
    ULONG ulrecv_HashValue;

    GETSOCKNAME MyGetSockName;
    ULONG ulgetsockname_HashValue;

    GETHOSTNAME MyGetHostName;
    ULONG ulgethostname_HashValue;

    SEND MySend;
    ULONG ulsend_HashValue;

    WSACLEANUP WSACleanup;
    ULONG ulWSACleanup_HashValue;

    WSAGETLASTERROR WSAGetLastError;
    ULONG ulWSAGetLastError_HashValue;

    __WSAFDISSET My__WSAFDIsSet;
    ULONG ul__WSAFDIsSet_HashValue;

    ACCEPT Myaccept;
    ULONG ulaccept_HashValue;

    BIND Mybind;
    ULONG ulbind_HashValue;

    LISTEN Mylisten;
    ULONG ullisten_HashValue;

    INET_ADDR inet_addr;
    ULONG ulinet_addr_HashValue;

    GETPEERNAME getpeername;
    ULONG ulgetpeername_HashValue;

    RECVFROM recvfrom;
    ULONG ulrecvfrom_HashValue;

    INET_NTOA inet_ntoa;
    ULONG ulinet_ntoa_HashValue;

    NTOHS ntohs;
    ULONG ulntohs_HashValue;

    SENDTO sendto;
    ULONG ulsendto_HashValue;

    IOCTLSOCKET ioctlsocket;
    ULONG ulioctlsocket_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
}API_BLOCK_WIN_SOCKET2,*PAPI_BLOCK_WIN_SOCKET2;

typedef struct _API_BLOCK_SHELL32
{
    SHGETSPECIALFOLDERPATHW MySHGetSpecialFolderPathW;
    ULONG ulSHGetSpecialFolderPathW_HashValue;

    COMMANDLINETOARGVW MyCommandLineToArgvW;
    ULONG ulCommandLineToArgvW_HashValue;

    SHGETFILEINFOA MySHGetFileInfoA;
    ULONG ulSHGetFileInfoA_HashValue;

    SHELLEXECUTEA MyShellExecuteA;
    ULONG ulShellExecuteA_HashValue;

    SHGETSPECIALFOLDERPATHA MySHGetSpecialFolderPathA;
    ULONG ulSHGetSpecialFolderPathA_HashValue;

    SHELLEXECUTEEXA MyShellExecuteExA;
    ULONG ulShellExecuteExA_HashValue;

    SHELLEXECUTEEXW MyShellExecuteExW;
    ULONG ulShellExecuteExW_HashValue;

    SHCHANGENOTIFY MySHChangeNotify;
    ULONG ulSHChangeNotify_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;

}API_BLOCK_SHELL32,*PAPI_BLOCK_SHELL32;

typedef struct _API_BLOCK_WININET
{
    INTERNETOPENW InternetOpenW;
    ULONG ulInternetOpenW_HashValue;

    INTERNETOPENURLW InternetOpenUrlW;
    ULONG ulInternetOpenUrlW_HashValue;

    INTERNETREADFILE InternetReadFile;
    ULONG ulInternetReadFile_HashValue;

    INTERNETCLOSEHANDLE InternetCloseHandle;
    ULONG ulInternetCloseHandle_HashValue;

    INTERNETOPENA InternetOpenA;
    ULONG ulInternetOpenA_HashValue;

    INTERNETOPENURLA InternetOpenUrlA;
    ULONG ulInternetOpenUrlA_HashValue;



    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
}API_BLOCK_WININET,*PAPI_BLOCK_WININET;

typedef struct _API_BLOCK_WTSAPI32
{
    WTSQUERYSESSIONINFORMATIONW MyWTSQuerySessionInformationW;
    ULONG ulWTSQuerySessionInformationW_HashValue;

    WTSQUERYSESSIONINFORMATIONA MyWTSQuerySessionInformationA;
    ULONG ulWTSQuerySessionInformationA_HashValue;

    WTSLOGOFFSESSION MyWTSLogoffSession;
    ULONG ulWTSLogoffSession_HashValue;

    WTSDISCONNECTSESSION MyWTSDisconnectSession;
    ULONG ulWTSDisconnectSession_HashValue;

    WTSFREEMEMORY MyWTSFreeMemory;
    ULONG ulWTSFreeMemory_HashValue;

    WTSENUMERATESESSIONSA MyWTSEnumerateSessionsA;
    ULONG ulWTSEnumerateSessionsA_HashValue;



    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;

}API_BLOCK_WTSAPI32,*PAPI_BLOCK_WTSAPI32;

typedef struct _API_BLOCK_GDI32
{
    CREATEDIBSECTION CreateDIBSection;
    ULONG ulCreateDIBSection_HashValue;

    CREATECOMPATIBLEBITMAP CreateCompatibleBitmap;
    ULONG CreateCompatibleBitmap_HashValue;

    BITBLT BitBlt;
    ULONG ulBitBlt_HashValue;

    SELECTOBJECT SelectObject;
    ULONG ulSelectObject_HashValue;

    CREATECOMPATIBLEDC CreateCompatibleDC;
    ULONG ulCreateCompatibleDC_HashValue;

    DELETEDC DeleteDC;
    ULONG ulDeleteDC_HashValue;

    DELETEOBJECT DeleteObject;
    ULONG ulDeleteObject_HashValue;

    GETDIBITS GetDIBits;
    ULONG ulGetDIBits_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
}API_BLOCK_GDI32,*PAPI_BLOCK_GDI32;

typedef struct _API_BLOCK_PSAPI
{
    ENUMPROCESSMODULES MyEnumProcessModules;
    ULONG ulEnumProcessModules_HashValue;

    GETMODULEFILENAMEEXA MyGetModuleFileNameExA;
    ULONG ulGetModuleFileNameExA_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
}API_BLOCK_PSAPI,*PAPI_BLOCK_PSAPI;

typedef struct _API_BLOCK_URLMON
{
    URLDOWNLOADTOFILEA MyURLDownloadToFileA;
    ULONG ulURLDownloadToFileA_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
}API_BLOCK_URLMON,*PAPI_BLOCK_URLMON;

typedef struct _API_BLOCK_NETAPI32
{
    NETUSERADD MyNetUserAdd;
    ULONG ulNetUserAdd_HashValue;

    NETUSERENUM MyNetUserEnum;
    ULONG ulNetUserEnum_HashValue;

    NETUSERGETINFO MyNetUserGetInfo;
    ULONG ulNetUserGetInfo_HashValue;

    NETUSERSETINFO MyNetUserSetInfo;
    ULONG ulNetUserSetInfo_HashValue;

    NETUSERDEL MyNetUserDel;
    ULONG ulNetUserDel_HashValue;

    NETUSERGETGROUPS MyNetUserGetGroups;
    ULONG ulNetUserGetGroups_HashValue;

    NETUSERSETGROUPS MyNetUserSetGroups;
    ULONG ulNetUserSetGroups_HashValue;

    NETUSERMODALSGET MyNetUserModalsGet;
    ULONG ulNetUserModalsGet_HashValue;

    NETUSERMODALSSET MyNetUserModalsSet;
    ULONG ulNetUserModalsSet_HashValue;

    NETUSERCHANGEPASSWORD MyNetUserChangePassword;
    ULONG ulNetUserChangePassword_HashValue;

    NETLOCALGROUPADDMEMBERS MyNetLocalGroupAddMembers;
    ULONG ulNetLocalGroupAddMembers_HashValue;

    NETUSERGETLOCALGROUPS MyNetUserGetLocalGroups;
    ULONG ulNetUserGetLocalGroups_HashValue;

    NETAPIBUFFERFREE MyNetApiBufferFree;
    ULONG ulNetApiBufferFree_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;
} API_BLOCK_NETAPI32,*PAPI_BLOCK_NETAPI32;
typedef struct _API_BLOCK_SHLWAPI
{
    SHGETVALUEA MySHGetValueA;
    ULONG ulSHGetValueA_HashValue;

    SHGETVALUEW MySHGetValueW;
    ULONG ulSHGetValueW_HashValue;

    SHSETVALUEA MySHSetValueA;
    ULONG ulSHSetValueA_HashValue;

    SHSETVALUEW MySHSetValueW;
    ULONG ulSHSetValueW_HashValue;

    ULONG_PTR ulEndApiSaveAddress;
    ULONG ulEndApiHashValue;

}API_BLOCK_SHLWAPI,*PAPI_BLOCK_SHLWAPI;

#pragma pack()
extern API_BLOCK_KERNEL32 g_Kernel32ApiBlock;
extern API_BLOCK_USER32 g_User32ApiBlock;
extern API_BLOCK_NTDLL g_NtdllApiBlock;
extern API_BLOCK_ADVAPI32 g_AdvApi32ApiBlock;
extern API_BLOCK_WIN_SOCKET2 g_WinSocket2ApiBlock;
extern API_BLOCK_SHELL32 g_Shell32ApiBlock;
extern API_BLOCK_WININET g_WinINetApiBlock;
extern API_BLOCK_GDI32 g_Gdi32ApiBlock;
extern API_BLOCK_WTSAPI32 g_WtsApi32Block;
extern API_BLOCK_PSAPI g_PsApiBlock;
extern API_BLOCK_URLMON g_UrlMonApiBlock;
extern API_BLOCK_NETAPI32 g_NetApi32Block;
extern API_BLOCK_SHLWAPI g_ShlwApiBlock;
extern HANDLE hKernel32;

BOOLEAN InitializeApiBlock();
void Get_Kernel_Api_From_HashValue(PVOID pImageBase,PVOID pFirstAddress,PVOID pFirstHashValue);
PVOID LoadMemory(PVOID pMemory,VIRTUALALLOC pVirtualAlloc);
ULONG GetLoadDat(PWCHAR pLoadName, \
                 PCHAR *pLoadDat, \
                 VIRTUALALLOC pVirtualAlloc, \
                 CREATEFILEW pCreateFileW, \
                 GETFILESIZE pGetFileSize, \
                 READFILE pReadFile, \
                 VIRTUALFREE pVirtualFree, \
                 CLOSEHANDLE pCloseHandle);

#pragma pack(1)
typedef struct _PEB_LDR_DATA {
    BYTE Reserved1[8];
    PVOID Reserved2[3];
    LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY {
    PVOID Reserved1[2];
    LIST_ENTRY InMemoryOrderLinks;
    PVOID Reserved2[2];
    PVOID DllBase;
    PVOID Reserved3[2];
    UNICODE_STRING FullDllName;
    BYTE Reserved4[8];
    PVOID Reserved5[3];
    union {
        ULONG CheckSum;
        PVOID Reserved6;
    } DUMMYUNIONNAME;
    ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    BYTE Reserved1[16];
    PVOID Reserved2[10];
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef
VOID
(NTAPI *PPS_POST_PROCESS_INIT_ROUTINE) (
                                        VOID
                                        );

typedef struct _PEB {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    BYTE Reserved4[104];
    PVOID Reserved5[52];
    PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
    BYTE Reserved6[128];
    PVOID Reserved7[1];
    ULONG SessionId;
} PEB, *PPEB;

#pragma pack()

#endif