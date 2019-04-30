#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")
#include "md5file.h"

char *DllFiles[] =
{
	"type md5 here",
	"type another md5 here"
};

#pragma region main

char ccbuf[1024];
HMODULE hMods[1024];
TCHAR szModName[MAX_PATH];
MD5 md5;

void DisplayDetect(){
	strcpy(ccbuf, "INVALID_SIGNATURE:\n");
	strcat(ccbuf, szModName);
	MessageBox(NULL, ccbuf, "DETECTED", MB_OK);	
}

void CheckDlls(){
    DWORD cbNeeded;
    unsigned int i;
	EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &cbNeeded);
	for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
        {

            if ( GetModuleFileNameEx( GetCurrentProcess(), hMods[i], szModName,
                                      sizeof(szModName) / sizeof(TCHAR)))
            {

				char* md5code = md5.MD5File(szModName);

				for (int j = 0; j < (sizeof(DllFiles) / sizeof(LPTSTR)); j++)
				{
					if(strcmp(md5code, DllFiles[j]) == 0){
						CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DisplayDetect, NULL, 0, NULL);
						Sleep(5000);
						TerminateProcess(GetCurrentProcess(), 1);
					}
				} 
            }
        }
}

void LoopCheckDlls(){
    while (1)
    {
		try{
		CheckDlls();
		}
		catch(...){ }
		Sleep(5000);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstdll, DWORD fdwReason, LPVOID lpvReserved)
{
	switch(fdwReason)

	{
		case DLL_PROCESS_ATTACH:
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoopCheckDlls, NULL, 0, NULL);
			break;
	}
return TRUE;
}

#pragma endregion