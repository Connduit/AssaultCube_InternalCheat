// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <Windows.h>

#include "detours/detours.h"

#include "constants.h"
#include "genCode.h"
#include "esp.h"
#include "menu.h"


void hook()
{
    Sleep(1000);
    DisableThreadLibraryCalls(hModule);
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)originalSwapBuffers, Menu::newSwapBuffers);
    DetourTransactionCommit();
}

void aimbot()
{
    std::cout << "aimbot created" << std::endl;
    hook();
    while (true)
    {
        resetPointers();
        ESP::aimbot();
        Sleep(50);

        if (GetAsyncKeyState(VK_DELETE))
        {
            std::cout << "delete key detected" << std::endl;
            Menu::toggleMenu();
        }
    }
}



void console(LPVOID lpParam)
{
    HMODULE hModule = (HMODULE)lpParam;

    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
    std::cout << "Console Created" << std::endl;

    while (true)
    {
        std::string input;
        std::cin >> input;
        if (input == "exit")
        {
            break;
        }
        if (input == "fov")
        {
            std::cout << "isInFov == " << ESP::isInFov(localPlayerPtr, ESP::getNearestPlayer()->o) << std::endl;
        }
        if (input == "up")
        {
            localPlayerPtr->pos.z += 5; // TODO: for some reasoning pos.z is chaning the yaw value
        }
        if (input == "down")
        {
            localPlayerPtr->pos.z -= 5; // TODO: for some reasoning pos.z is chaning the yaw value
        }
        if (input == "local player ptr" || input == "lpp")
        {
            std::cout << "Local Player Ptr = " << localPlayerPtr << std::endl;
        }
        if (input == "np")
        {
            std::cout << "Number of Players = " << numPlayers << std::endl;
        }
        if (input == "aimbot")
        {
            aimbot();
        }
        if (input == "hook")
        {
            hook();
        }
        if (input == "ent")
        {
            for (int i = 1; i < numPlayers + 1; ++i)
            {
                std::cout << "Entity = " << i << ", Pos = " << players->players[i]->pos.x << ", " << players->players[i]->pos.y << ", " << players->players[i]->pos.z << std::endl;
            }
        }

    }
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    std::cout << "freeing dll" << std::endl;
    //return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
        // this case is hit when the dll is injected
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)console, hModule, 0, nullptr);
        //CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)hook, nullptr, 0, nullptr);
        //CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)aimbot, nullptr, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;

}

