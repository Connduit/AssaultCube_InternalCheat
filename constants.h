#pragma once

#include <Windows.h>

#include "genCode.h"


// globals

extern HMODULE hModule;
extern uintptr_t exeBaseAddress;

extern Player* localPlayerPtr;
extern EntityList* players;

extern int numPlayers;

void resetPointers();

typedef BOOL(__stdcall* _wglSwapBuffers)(HDC hdc);
extern _wglSwapBuffers originalSwapBuffers;

typedef int(__cdecl* _SDL_SetRelativeMouseMode)(int mode);
extern _SDL_SetRelativeMouseMode originalSetRelativeMouseMode;

//typedef int(__cdecl* _SDL_ShowCursor)(int toggle);
//extern _SDL_ShowCursor originalShowCursor;

