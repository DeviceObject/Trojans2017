#pragma warning(disable : 4311 4312 )

#include "Server.h"
#include "MemoryLoader.h"
#include "ApiBlock.h"
#include "Utils.h"



PVOID MyReAlloc(PVOID p,ULONG ulSize)
{
	if (p)
	{
		return g_Kernel32ApiBlock.MyHeapReAlloc(g_Kernel32ApiBlock.MyGetProcessHeap(),0,p,ulSize);
	}
	else
	{
		return g_Kernel32ApiBlock.MyHeapAlloc(g_Kernel32ApiBlock.MyGetProcessHeap(),0,ulSize);
	}
}
void MyCopySections(PVOID pLdrDat,PIMAGE_NT_HEADERS pOldNtHeader,PMEMORY_LOADER pMemLdrInfo)
{
	PIMAGE_SECTION_HEADER pSectionHeader;
	PCHAR pCodeBase;
	PCHAR pDestDat;
	ULONG ulSize;
    ULONG uli;

	pCodeBase = NULL;
	pDestDat = NULL;

	pSectionHeader = IMAGE_FIRST_SECTION(pMemLdrInfo->pNtHeader);
	pCodeBase = pMemLdrInfo->pCode;

	for (uli = 0;uli < pMemLdrInfo->pNtHeader->FileHeader.NumberOfSections;uli++)
	{
		if (pSectionHeader->SizeOfRawData == 0)
		{
			ulSize = pOldNtHeader->OptionalHeader.SectionAlignment;
			if (ulSize > 0)
			{
				pDestDat = (PCHAR)g_Kernel32ApiBlock.MyVirtualAlloc(pCodeBase + pSectionHeader->VirtualAddress, \
					ulSize, \
					MEM_COMMIT, \
					PAGE_EXECUTE_READWRITE);
				pSectionHeader->Misc.PhysicalAddress = (ULONG)pDestDat;
				RtlZeroMemory(pDestDat,ulSize);
			}
			continue;
		}
		pDestDat = (PCHAR)g_Kernel32ApiBlock.MyVirtualAlloc(pCodeBase + pSectionHeader->VirtualAddress, \
			pSectionHeader->SizeOfRawData, \
			MEM_COMMIT, \
			PAGE_EXECUTE_READWRITE);
		memcpy(pDestDat,(PCHAR)((ULONG)pLdrDat + pSectionHeader->PointerToRawData),pSectionHeader->SizeOfRawData);
		pSectionHeader->Misc.PhysicalAddress = (ULONG)pDestDat;
		pSectionHeader = (PIMAGE_SECTION_HEADER)((ULONG)pSectionHeader + sizeof(IMAGE_SECTION_HEADER));
	}
}
void MyFixedBaseRelocation(PMEMORY_LOADER pMemoryLdr,ULONG ulOffset)
{
	PCHAR pCodeBase;
	PIMAGE_DATA_DIRECTORY pDirectory;
	PIMAGE_BASE_RELOCATION pRelocation;
	PCHAR pDest;
	PSHORT pRelocDat;
	ULONG ulType;
	ULONG ulCurOffset;
	ULONG *ulPatchAddr;
    ULONG uli;

	pCodeBase = NULL;
	pDirectory = NULL;
	pRelocation = NULL;
	pDest = NULL;
	pRelocDat = NULL;

	pDirectory = &pMemoryLdr->pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
	if (pDirectory->Size > 0)
	{
		pCodeBase = pMemoryLdr->pCode;
		pRelocation = (PIMAGE_BASE_RELOCATION)((ULONG)pCodeBase + pDirectory->VirtualAddress);
		while (pRelocation->VirtualAddress > 0)
		{
			pDest = (PCHAR)((ULONG)pCodeBase + pRelocation->VirtualAddress);
			pRelocDat = (PSHORT)((ULONG)pRelocation + sizeof(IMAGE_BASE_RELOCATION));
			for (uli = 0;uli < ((pRelocation->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2);uli++,pRelocDat++)
			{
				ulType = *pRelocDat >> 12;
				ulCurOffset = *pRelocDat & 0xFFF;
				switch (ulType)
				{
				case IMAGE_REL_BASED_ABSOLUTE:
					break;
				case IMAGE_REL_BASED_HIGHLOW:
					ulPatchAddr = (ULONG*)(pDest + ulCurOffset);
					*ulPatchAddr += ulOffset;
					break;
				default:
					break;
				}
			}
			pRelocation = (PIMAGE_BASE_RELOCATION)((ULONG)pRelocation + pRelocation->SizeOfBlock);
		}
	}
}
BOOLEAN MyBuildImportTable(PMEMORY_LOADER pMemoryLdr)
{
	PCHAR pCodeBase;
	PIMAGE_DATA_DIRECTORY pDataDirectory;
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
	PIMAGE_IMPORT_BY_NAME pImportThunk;
	HMODULE hModule;
	BOOLEAN bRet;
	PULONG pThunkRef;
	PULONG pFuncRef;

	pCodeBase = NULL;
	pDataDirectory = NULL;
	pImportDesc = NULL;
	pImportThunk = NULL;
	bRet = TRUE;
	pThunkRef = NULL;
	pFuncRef = NULL;

	pCodeBase = pMemoryLdr->pCode;
	pDataDirectory = &pMemoryLdr->pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	if (pDataDirectory->Size > 0)
	{
		pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((ULONG)pCodeBase + pDataDirectory->VirtualAddress);
		while (!g_Kernel32ApiBlock.MyIsBadReadPtr(pImportDesc,sizeof(IMAGE_IMPORT_DESCRIPTOR)) && pImportDesc->Name)
		{
			hModule = g_Kernel32ApiBlock.MyLoadLibraryA((PCHAR)((ULONG)pCodeBase + pImportDesc->Name));
			if (INVALID_HANDLE_VALUE == hModule)
			{
				bRet = FALSE;
				break;
			}
			pMemoryLdr->hModule = (HMODULE *)MyReAlloc(pMemoryLdr->hModule,(pMemoryLdr->ulModuleCount + 1) * sizeof(HMODULE));
			if (NULL == pMemoryLdr->hModule)
			{
				bRet = FALSE;
				break;
			}
			pMemoryLdr->hModule[pMemoryLdr->ulModuleCount++] = hModule;
			if (pImportDesc->OriginalFirstThunk)
			{
				pThunkRef = (PULONG)((ULONG)pCodeBase + pImportDesc->OriginalFirstThunk);
				pFuncRef = (PULONG)((ULONG)pCodeBase + pImportDesc->FirstThunk);
			}
			else
			{
				pThunkRef = (PULONG)((ULONG)pCodeBase + pImportDesc->FirstThunk);
				pFuncRef = (PULONG)((ULONG)pCodeBase + pImportDesc->FirstThunk);
			}
			while(*pThunkRef)
			{
				if (IMAGE_SNAP_BY_ORDINAL(*pThunkRef))
				{
					*pFuncRef = (ULONG)g_Kernel32ApiBlock.MyGetProcAddress(hModule,(PCHAR)IMAGE_ORDINAL(*pThunkRef));
				}
				else
				{
					pImportThunk = (PIMAGE_IMPORT_BY_NAME)(pCodeBase + *pThunkRef);
					*pFuncRef = (ULONG)g_Kernel32ApiBlock.MyGetProcAddress(hModule,(PCHAR)&pImportThunk->Name);
				}
				//if (*pFuncRef == 0)
				//{
				//	break;
				//}
				pThunkRef++;
				pFuncRef++;
			}
			pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((ULONG)pImportDesc + sizeof(IMAGE_IMPORT_DESCRIPTOR));
		}
	}
	return bRet;
}
static int ProtectionFlags[2][2][2] = 
{
	{
		// not executable
		{PAGE_NOACCESS, PAGE_WRITECOPY},
		{PAGE_READONLY, PAGE_READWRITE},
	}, {
		// executable
		{PAGE_EXECUTE, PAGE_EXECUTE_WRITECOPY},
		{PAGE_EXECUTE_READ, PAGE_EXECUTE_READWRITE},
	},
};
void MyFinalizeSections(PMEMORY_LOADER pMemoryLdr)
{
	ULONG ulProtect,ulOldProtect,ulSize;
	ULONG ulExecutAble,ulReadAble,ulWriteAble;
	PIMAGE_SECTION_HEADER pSectionHeader;
    ULONG uli;

	pSectionHeader = IMAGE_FIRST_SECTION(pMemoryLdr->pNtHeader);

	for (uli = 0;uli < pMemoryLdr->pNtHeader->FileHeader.NumberOfSections;uli++)
	{
		ulExecutAble = (pSectionHeader->Characteristics & IMAGE_SCN_MEM_EXECUTE) != 0;
		ulReadAble =   (pSectionHeader->Characteristics & IMAGE_SCN_MEM_READ) != 0;
		ulWriteAble =  (pSectionHeader->Characteristics & IMAGE_SCN_MEM_WRITE) != 0;

		if (pSectionHeader->Characteristics & IMAGE_SCN_MEM_DISCARDABLE)
		{
			g_Kernel32ApiBlock.MyVirtualFree((LPVOID)pSectionHeader->Misc.PhysicalAddress,pSectionHeader->SizeOfRawData,MEM_DECOMMIT);
			continue;
		}
		ulProtect = ProtectionFlags[ulExecutAble][ulReadAble][ulWriteAble];
		if (pSectionHeader->Characteristics & IMAGE_SCN_MEM_NOT_CACHED)
		{
			ulProtect |= PAGE_NOCACHE;
		}
		ulSize = pSectionHeader->SizeOfRawData;
		if (ulSize == 0)
		{
			if (pSectionHeader->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA)
			{
				ulSize = pMemoryLdr->pNtHeader->OptionalHeader.SizeOfInitializedData;
			}
			else if (pSectionHeader->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
			{
				ulSize = pMemoryLdr->pNtHeader->OptionalHeader.SizeOfUninitializedData;
			}
		}
		if (g_Kernel32ApiBlock.MyVirtualProtect((LPVOID)pSectionHeader->Misc.PhysicalAddress, \
			pSectionHeader->SizeOfRawData, \
			ulProtect, \
			&ulOldProtect) == 0)
		{
		}
	}
}
PMEMORY_LOADER MyMemoryLoader(PVOID pLdrDat)
{
	PIMAGE_DOS_HEADER pOldDosHeader;
	PIMAGE_NT_HEADERS pOldNtHeader;
	PCHAR pCode,pHeader;
	PMEMORY_LOADER pMemoryLoaderInfo;
	ULONG ulBaseOffset;
	DLLENTRY DllEntryMain;
	SHOWINFO ShowInfo;
	BOOLEAN bSuccessFull;

	pCode = NULL;
	pHeader = NULL;
	ulBaseOffset = 0;
	DllEntryMain = NULL;
	bSuccessFull = FALSE;

    do 
    {
        pMemoryLoaderInfo = VirtualAlloc(NULL,sizeof(MEMORY_LOADER),MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);
    } while (NULL == pMemoryLoaderInfo);
	RtlZeroMemory(pMemoryLoaderInfo,sizeof(MEMORY_LOADER));
	pOldDosHeader = (PIMAGE_DOS_HEADER)pLdrDat;
	if (pOldDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return NULL;
	}
	pOldNtHeader = (PIMAGE_NT_HEADERS)((ULONG)pOldDosHeader + pOldDosHeader->e_lfanew);
	if (pOldNtHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		return NULL;
	}
	pCode = (PCHAR)g_Kernel32ApiBlock.MyVirtualAlloc((PVOID)pOldNtHeader->OptionalHeader.ImageBase, \
		pOldNtHeader->OptionalHeader.SizeOfImage, \
		MEM_RESERVE | MEM_COMMIT, \
		PAGE_EXECUTE_READWRITE);
	if (NULL == pCode)
	{
		pCode = (PCHAR)g_Kernel32ApiBlock.MyVirtualAlloc(NULL, \
			pOldNtHeader->OptionalHeader.SizeOfImage, \
			MEM_RESERVE | MEM_COMMIT, \
			PAGE_EXECUTE_READWRITE);
		if (NULL == pCode)
		{
			return NULL;
		}
	}
	pMemoryLoaderInfo->pCode = pCode;

	//g_pUseApiList->VirtualAlloc(pCode, \
	//	pOldNtHeader->OptionalHeader.SizeOfImage, \
	//	MEM_RESERVE | MEM_COMMIT, \
	//	PAGE_EXECUTE_READWRITE);
	pHeader = (PCHAR)g_Kernel32ApiBlock.MyVirtualAlloc(NULL, \
		pOldNtHeader->OptionalHeader.SizeOfHeaders, \
		MEM_RESERVE | MEM_COMMIT, \
		PAGE_EXECUTE_READWRITE);
	if (NULL == pHeader)
	{
		return NULL;
	}
	RtlZeroMemory(pHeader,pOldNtHeader->OptionalHeader.SizeOfHeaders);
	memcpy(pHeader,pOldDosHeader,pOldNtHeader->OptionalHeader.SizeOfHeaders);
	memcpy(pCode,pOldDosHeader,pOldNtHeader->OptionalHeader.SizeOfHeaders);
	pMemoryLoaderInfo->pDosHeader = (PIMAGE_DOS_HEADER)pHeader;
	pMemoryLoaderInfo->pNtHeader = (PIMAGE_NT_HEADERS)((ULONG)pHeader + ((PIMAGE_DOS_HEADER)pHeader)->e_lfanew);
	pMemoryLoaderInfo->pNtHeader->OptionalHeader.ImageBase = (ULONG)pCode;

	MyCopySections(pLdrDat,pOldNtHeader,pMemoryLoaderInfo);

	ulBaseOffset = ((ULONG)pCode - pOldNtHeader->OptionalHeader.ImageBase);
	if (ulBaseOffset != 0)
	{
		MyFixedBaseRelocation(pMemoryLoaderInfo,ulBaseOffset);
	}
	if (FALSE == MyBuildImportTable(pMemoryLoaderInfo))
	{
		MyMemoryFreeLoader(pMemoryLoaderInfo);
	}
	//FinalizeSections(&MemoryLoaderInfo);

	if (pMemoryLoaderInfo->pNtHeader->OptionalHeader.AddressOfEntryPoint != 0)
	{
		DllEntryMain = (DLLENTRY)((ULONG)pCode + pMemoryLoaderInfo->pNtHeader->OptionalHeader.AddressOfEntryPoint);
		if (NULL == DllEntryMain)
		{
			MyMemoryFreeLoader(pMemoryLoaderInfo);
		}
		bSuccessFull = (*DllEntryMain)((HINSTANCE)pCode,DLL_PROCESS_ATTACH,0);
		//bSuccessFull = DllEntryMain((HINSTANCE)pCode,DLL_PROCESS_ATTACH,0);
		if (FALSE == bSuccessFull)
		{
			MyMemoryFreeLoader(pMemoryLoaderInfo);
		}
		ShowInfo = (SHOWINFO)MyMemoryGetProcAddress(pMemoryLoaderInfo,"ShowInfo");
		ShowInfo();
		pMemoryLoaderInfo->bInitialized = TRUE;
	}
	return pMemoryLoaderInfo;
}
void MyFree(PVOID p)
{
	g_Kernel32ApiBlock.MyHeapFree(g_Kernel32ApiBlock.MyGetProcessHeap(),0,p);
}
void MyMemoryFreeLoader(PMEMORY_LOADER pMemoryLdr)
{
	DLLENTRY DllEntryMain;
    ULONG uli;

	if (NULL != pMemoryLdr)
	{
		if (pMemoryLdr->bInitialized != FALSE)
		{
			DllEntryMain = (DLLENTRY)((ULONG)pMemoryLdr->pCode + pMemoryLdr->pNtHeader->OptionalHeader.AddressOfEntryPoint);
			(*DllEntryMain)((HINSTANCE)pMemoryLdr->pCode,DLL_PROCESS_DETACH,0);
			pMemoryLdr->bInitialized = FALSE;
		}
		if (pMemoryLdr->hModule)
		{
			for (uli = 0;uli < pMemoryLdr->ulModuleCount;uli++)
			{
				if (pMemoryLdr->hModule[uli] != INVALID_HANDLE_VALUE)
				{
					g_Kernel32ApiBlock.MyFreeLibrary(pMemoryLdr->hModule[uli]);
				}
			}
			MyFree(pMemoryLdr->hModule);
		}
		if (pMemoryLdr->pCode)
		{
			g_Kernel32ApiBlock.MyVirtualFree(pMemoryLdr->pCode,0,MEM_RELEASE);
		}
		g_Kernel32ApiBlock.MyHeapFree(g_Kernel32ApiBlock.MyGetProcessHeap(),0,pMemoryLdr);
	}
}
FARPROC MyMemoryGetProcAddress(PMEMORY_LOADER pMemoryLdr,PCHAR pFnName)
{
	PCHAR pCodeBase;
	PIMAGE_EXPORT_DIRECTORY pExportDirectory;
	PIMAGE_DATA_DIRECTORY pDatDirectory;
	PULONG pNameAddress;
	PSHORT pOrdinal;
	ULONG ulIndex;
    ULONG uli;

	ulIndex = -1;
	pDatDirectory = &pMemoryLdr->pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	if (pDatDirectory->Size == 0)
	{
		return NULL;
	}
	pCodeBase = pMemoryLdr->pCode;
	pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((ULONG)pCodeBase + pDatDirectory->VirtualAddress);
	if (pExportDirectory->NumberOfFunctions  == 0 || pExportDirectory->NumberOfNames == 0)
	{
		return NULL;
	}
	pNameAddress = (PULONG)((ULONG)pCodeBase + pExportDirectory->AddressOfNames);
	pOrdinal = (PSHORT)((ULONG)pCodeBase + pExportDirectory->AddressOfNameOrdinals);
	for (uli = 0;uli < pExportDirectory->NumberOfNames;uli++,pNameAddress++,pOrdinal++)
	{
		if (strcmpiA(pFnName,(PCHAR)((ULONG)pCodeBase + *pNameAddress)) == 0)
		{
			ulIndex = *pOrdinal;
			break;
		}
	}
	if (ulIndex == -1)
	{
		return NULL;
	}
	if (ulIndex > pExportDirectory->NumberOfFunctions)
	{
		return NULL;
	}
	return (FARPROC)((ULONG)pCodeBase + pExportDirectory->AddressOfFunctions + ulIndex * 4);
}
BOOLEAN MyMemoryLoaderCall(PCHAR pLdrDat,ULONG ulLdrSize,PCHAR pCallFnName)
{
	BOOLEAN bRet;
	PMEMORY_LOADER pMemLdr;
	PFN_CALL pFn;

	pMemLdr = NULL;
	bRet = TRUE;
	pFn = NULL;

	pMemLdr = MyMemoryLoader(pLdrDat);
	if (pMemLdr == NULL)
	{
		bRet = FALSE;
		return bRet;
	}
	pFn = (PFN_CALL)MyMemoryGetProcAddress(pMemLdr,pCallFnName);
	if (NULL == pFn)
	{
		MyMemoryFreeLoader(pMemLdr);
		bRet = FALSE;
		return bRet;
	}
	pFn();
	if (pMemLdr)
	{
		MyMemoryFreeLoader(pMemLdr);
		pMemLdr = NULL;
	}
	return bRet;
}