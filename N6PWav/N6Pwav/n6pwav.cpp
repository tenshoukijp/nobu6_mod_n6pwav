// n6pwav.cpp : n6pwavのエントリポイント
//

#include <windows.h>

FARPROC p1_DllMain;
FARPROC p2_DllMain;
FARPROC p3_DllMain;
FARPROC p1_LoadWaveResource;
FARPROC p2_LoadWaveResource;
FARPROC p3_LoadWaveResource;

HINSTANCE h1_original;
HINSTANCE h2_original;
HINSTANCE h3_original;

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	switch( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		//----------1
		h1_original = LoadLibrary( "n6pwav1.dll" );
		if ( h1_original == NULL )
			return FALSE;
		p1_DllMain = GetProcAddress( h1_original, "DllMain" );
		p1_LoadWaveResource = GetProcAddress( h1_original, "LoadWaveResource" );

		//----------2
		h2_original = LoadLibrary( "n6pwav2.dll" );
		if ( h2_original == NULL )
			return FALSE;
		p2_DllMain = GetProcAddress( h2_original, "DllMain" );
		p2_LoadWaveResource = GetProcAddress( h2_original, "LoadWaveResource" );

		//----------3
		h3_original = LoadLibrary( "n6pwav3.dll" );
		if ( h3_original == NULL )
			return FALSE;
		p3_DllMain = GetProcAddress( h3_original, "DllMain" );
		p3_LoadWaveResource = GetProcAddress( h3_original, "LoadWaveResource" );
		break;

	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary( h1_original );
		FreeLibrary( h2_original );
		FreeLibrary( h3_original );
		break;
	default:
		break;
	}
	return TRUE;
}
