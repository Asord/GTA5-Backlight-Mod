#include "script.h"

#ifdef _DEBUG
int main(int argc, char* argv[])
{
	ScriptMain();

	return 0;
}
#else
#include "..\..\inc\main.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, ScriptMain);
		break;
	case DLL_PROCESS_DETACH:
		EffectHandler* handler = EffectHandler::getInstance();
		handler->unlock();
		scriptUnregister(hInstance);
		break;
	}
	return TRUE;
}
#endif
