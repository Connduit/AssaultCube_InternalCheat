#include <iostream>
#include <windows.h>
#include "imgui.h"
#include "external/imgui/backends/imgui_impl_win32.h"
#include "external/imgui/backends/imgui_impl_opengl2.h"

#include "GL/GL.h"
#include "gl/GLU.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "menu.h"
#include "constants.h"

const ImVec2 initWindowSize = ImVec2(400, 400);
bool showMenu = false;
bool initialized = false;
bool contextCreated = false;
HWND gameWindow;
HGLRC myContext;
HGLRC gameContext;
HDC gHDC;
WNDPROC originalWndProc = nullptr;




LRESULT CALLBACK newWNDProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (showMenu)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return 0;

		switch (uMsg)
		{
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			return 0;
		}
	}
	return CallWindowProc(originalWndProc, hWnd, uMsg, wParam, lParam);
}


void Menu::toggleMenu()
{
	std::cout << "inside toggle menu" << std::endl;
	//showMenu = !showMenu;
	//ImGuiIO& io = ImGui::GetIO();
	std::cout << "got imgui io" << std::endl;
	//io.WantCaptureMouse = showMenu; // setting these values cause a core for some reason?
	//io.WantCaptureKeyboard = showMenu; // setting these values cause a core for some reason?
	//io.MouseDrawCursor = showMenu; // setting these values cause a core for some reason?
	std::cout << "set io fields" << std::endl;
	//originalSetRelativeMouseMode(!showMenu);
	//originalShowCursor(!showMenu);
	std::cout << "originalsetrelativemousemode good" << std::endl;
}

void Menu::init()
{
	std::cout << "inside init" << std::endl;
	ImGui::CreateContext();
	gameWindow = FindWindowA(NULL, "AssaultCube");
	originalWndProc = (WNDPROC)SetWindowLongPtr(gameWindow, GWLP_WNDPROC, (LONG_PTR)newWNDProc);

	ImGui_ImplWin32_Init(gameWindow);
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	io.Fonts->AddFontDefault();

	ImGui::SetCurrentContext(ImGui::GetCurrentContext());
	ImGui::SetNextWindowSize(initWindowSize);

	initialized = true;
	std::cout << "Menu initalized" << std::endl;

}

void Menu::startRender()
{
	//std::cout << "inside start render" << std::endl;
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Menu::endRender()
{
	//std::cout << "inside end render" << std::endl;
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Menu::render()
{
	//std::cout << "inside render" << std::endl;
	if (GetAsyncKeyState(VK_INSERT) & 1)
		showMenu = !showMenu;

	ImGuiIO& io = ImGui::GetIO();
	if (showMenu)
	{
		io.WantCaptureMouse = true;
		io.MouseDrawCursor = true;
		originalSetRelativeMouseMode(!showMenu);
		ImGui::Begin("Menu", &showMenu);
		ImGui::Text("Hello World");

		if (ImGui::Button("TP UP"))
		{
			localPlayerPtr->pos.z += 5;
		}
		ImGui::End();
	}
	else
	{
		io.WantCaptureMouse = false;
		io.MouseDrawCursor = false;
		originalSetRelativeMouseMode(!showMenu);
	}

}

void setupContext(HDC& hdc)
{
	std::cout << "inside setup context" << std::endl;
	myContext = wglCreateContext(hdc);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	contextCreated = true;
}



BOOL __stdcall Menu::newSwapBuffers(HDC hdc)
{
	//std::cout << "inside new swap buffers" << std::endl;
	if (!initialized)
	{
		init();
		return originalSwapBuffers(hdc);
	}

	gameContext = wglGetCurrentContext();
	if (!contextCreated)
	{
		setupContext(hdc);
	}

	wglMakeCurrent(hdc, myContext);
	Menu::startRender();
	Menu::render();
	Menu::endRender();

	wglMakeCurrent(hdc, gameContext);
	return originalSwapBuffers(hdc);
}


void Menuu::toggleMenu()
{

}

void Menuu::render()
{

}

void Menuu::init()
{

}
