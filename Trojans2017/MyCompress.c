#include "Trojans2017.h"
#include "zlib/zlib.h"
#include "MyCompress.h"

BOOLEAN UnionCompress(PCHAR pDestDat,PULONG pulDestSize,PCHAR pSourceDat,ULONG ulSourceSize,COMPRESS_TYPE CompressType)
{
    BOOLEAN bRet;

    bRet = FALSE;

    switch (CompressType)
    {
    case ZlibCompress:
        *pulDestSize = (ULONG)(ulSourceSize * 1.001)  + 12;
        do 
        {
            pDestDat = VirtualAlloc(NULL,*pulDestSize,MEM_COMMIT | MEM_RESERVE,PAGE_READWRITE);
        } while (NULL == pDestDat);
        RtlZeroMemory(pDestDat,*pulDestSize);
        if (Z_OK != compress(pDestDat,pulDestSize,pSourceDat,ulSourceSize))
        {
            VirtualFree(pDestDat,*pulDestSize,MEM_RESERVE | MEM_DECOMMIT);
            break;
        }
        bRet = TRUE;
        break;
    default:
        break;
    }
    return bRet;
}