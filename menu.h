#pragma once

#include <windows.h>
#include "imgui.h"
#include "external/imgui/backends/imgui_impl_win32.h"
#include "external/imgui/backends/imgui_impl_opengl2.h"


namespace Menu
{

}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // TODO: shouldn't be extern in cpp file? move to .h file

class Menuu
{
public:
	Menuu() {};
	void toggleMenu();
	void render();
	void init();
	void startRender(); // TODO: move into render
	void render();
	void endRender(); // TODO: move into render
	BOOL __stdcall newSwapBuffers(HDC hdc); 
private:

};
