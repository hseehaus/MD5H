BOOL WINAPI DllMain(HINSTANCE hinstdll, DWORD fdwReason, LPVOID lpvReserved) 
{ 
  switch(fdwReason) 
  { 
    case DLL_PROCESS_ATTACH: 
 			  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)asf, NULL, 0, NULL); 
 		  	break; 
 	} 
return TRUE;
}
