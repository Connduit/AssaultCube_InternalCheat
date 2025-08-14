// globals

#include <iostream>
#include "constants.h"

HMODULE hModule = GetModuleHandle(nullptr);
uintptr_t exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);

Player* localPlayerPtr = *(Player**)(exeBaseAddress + 0x0017E0A8);

uintptr_t playersAddr = exeBaseAddress + 0x18AC04; // pointer to address of array of players
EntityList* players = *(EntityList**)playersAddr; // array of players
int numPlayers = *(int*)(exeBaseAddress + 0x191FD4); // TODO: this isincorrect as well.. idk it looks corerct... it's also static so it shouldn't change

void resetPointers()
{
	localPlayerPtr = *(Player**)(exeBaseAddress + 0x0017E0A8);
	players = *(EntityList**)(playersAddr);
	numPlayers = *(int*)(exeBaseAddress + 0x191FD4);
}





_wglSwapBuffers originalSwapBuffers = (_wglSwapBuffers)GetProcAddress(GetModuleHandle(L"OPENGL32.dll"), "wglSwapBuffers");
_SDL_SetRelativeMouseMode originalSetRelativeMouseMode = (_SDL_SetRelativeMouseMode)GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode");
//_SDL_ShowCursor originalShowCursor = (_SDL_ShowCursor)GetProcAddress(GetModuleHandleA("SDL.dll"), "SDL_ShowCursor");

