#include <windows.h>
#include "resource1.h"
#include <string.h>

void OnCreate(HWND hw) {
	char s[128];
	LoadString(0, IDS_STRING101, s, sizeof s);

	CreateWindow("BUTTON",s, WS_CHILD | WS_VISIBLE, 75, 50, 100, 30, hw, (HMENU)IDC_BUTTON1, 0, 0);

	LoadString(0, IDS_STRING102, s, sizeof s);
	CreateWindow("BUTTON", s, WS_CHILD | WS_VISIBLE, 225, 50, 100, 30, hw, (HMENU)IDC_BUTTON2, 0, 0);

	LoadString(0, IDS_STRING103, s, sizeof s);
	CreateWindow("BUTTON", s, WS_CHILD | WS_VISIBLE, 270, 225, 100, 30, hw, (HMENU)IDC_BUTTON3, 0, 0);

}

void OnCommand(HWND hw, int id, int code) {

	switch (id)
	{

	//otvori nobi prozor sa igrom
	case IDC_BUTTON1: {
	
	
	}

	//otvodio dialog sa postavkama 
	case IDC_BUTTON2: {
	
	}
	case IDC_BUTTON3:
	{
			PostQuitMessage(0);
	}
			break;
	}

}

LRESULT CALLBACK WndProc(HWND hw, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE:
		OnCreate(hw);
		return(0);
	case WM_COMMAND:
		OnCommand(hw, LOWORD(wParam), HIWORD(wParam));
		return(0);
	case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hw, message, wParam, lParam);
}


int RegisterMyClass(HINSTANCE hInstance, char* className)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof wc);

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);

	return RegisterClass(&wc);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	char clsName[] = "MazeGame";

	if(!RegisterMyClass(hInstance, clsName))
		return 0;

	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	HWND hwnd = CreateWindow(clsName, "Maze Game",  WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, hMenu, hInstance, NULL); 

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	return msg.wParam;
}

