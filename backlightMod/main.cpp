#include "script.h"
#include "ledseffects/EffectReader.h"

#include "..\..\inc\main.h"


BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, ScriptMain);
		break;
	case DLL_PROCESS_DETACH:
		EffectReader* effectReader = EffectReader::getInstance();
		effectReader->finish();
		scriptUnregister(hInstance);
		break;
	}		
	return TRUE;
}