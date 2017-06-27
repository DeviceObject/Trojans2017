#ifndef __MEMORY_LOADER_H__
#define __MEMORY_LOADER_H__

typedef struct _MEMORY_LOADER
{
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeader;
	PCHAR pCode;
	HMODULE *hModule;
	ULONG ulModuleCount;
	BOOLEAN bInitialized;
}MEMORY_LOADER,*PMEMORY_LOADER;

PVOID MyReAlloc(PVOID p,ULONG ulSize);
void MyCopySections(PVOID pLdrDat,PIMAGE_NT_HEADERS pOldNtHeader,PMEMORY_LOADER pMemLdrInfo);
void MyFixedBaseRelocation(PMEMORY_LOADER pMemoryLdr,ULONG ulOffset);
BOOLEAN MyBuildImportTable(PMEMORY_LOADER pMemoryLdr);
void MyFinalizeSections(PMEMORY_LOADER pMemoryLdr);
PMEMORY_LOADER MyMemoryLoader(PVOID pLdrDat);
void MyFree(PVOID p);
void MyMemoryFreeLoader(PMEMORY_LOADER pMemoryLdr);
int __fastcall strcmpiA(const char *s1, const char *s2);
BOOLEAN MyMemoryLoaderCall(PCHAR pLdrDat,ULONG ulLdrSize,PCHAR pCallFnName);
FARPROC MyMemoryGetProcAddress(PMEMORY_LOADER pMemoryLdr,PCHAR pFnName);

typedef void (WINAPI *PFN_CALL)(void);
typedef BOOL (WINAPI *DLLENTRY)(HINSTANCE hInstance,DWORD fdwReason,LPVOID lpReserved);
typedef void (__stdcall *SHOWINFO)();
#endif