#include "nwpwin.h"
#include "resource1.h"
#include <windows.h>
#include <String.h>
#include <iostream>

class Button:public Window
{
public:
	std::string ClassName() { return "BUTTON"; }
};

INT_PTR CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_Apply:
			EndDialog(hwnd, IDOK);
			break;
		case IDC_BUTTON1:
			EndDialog(hwnd, IDC_CANCLE);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

//class u kojemu če se vrtiti igra
class GameWindow : public Window {
	int x = 0;
	int y = 0;


	//broj 0: oznacava polja za kretanje
	//broj 1: oznacava zid
	//broj 2: oznacava pocetak
	//broj 3: oznacava kraj
	int map[8][8] = {
		{1,2,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,1,1,1,1,1,3,1},
	};

protected:

	int Get(int x, int y) {
		return map[x][y];
	}

	void Set(int x, int y, int value) {
		map[x][y] = value;
	}

	void printMap() {
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++) {
				std::cout << map[i][j] << " ";
			}
			std::cout << std::endl;
		}
		
	}
	// TODO: na prozoru izcrtati mapu;
	int OnCreate(CREATESTRUCT* pcs) {

		return 0;
	}
	void OnCommand(int id) {
			

	}

	/*void OnPaint(HDC hdc) {
	
	
	}*/

	void OnDestroy() {
		::PostQuitMessage(0);
	}
};

class MyWindow : public Window {

protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MyWindow::OnCreate(CREATESTRUCT* psc)
{
	Button start, setting, quit;
	char s[128];

	LoadString(0, IDS_STRING101, s, sizeof s);
	start.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_START, 150, 150, 200, 100);

	LoadString(0, IDS_STRING102, s, sizeof s);
	setting.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_SETTING, 400, 150, 200, 100);

	LoadString(0, IDS_STRING103, s, sizeof s);
	quit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, s, IDC_QUIT, 575, 500, 200, 50);

	return 0;
}
void MyWindow::OnCommand(int id)
{
	HWND SettingDlg;
	GameWindow gameWnd;

	switch (id)
	{
	case IDC_START:
		gameWnd.Create(*this,WS_CHILD | WS_VISIBLE | WS_BORDER, "Game", 10000, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600);
		
			break;
	case IDC_SETTING:
		SettingDlg= CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG2),NULL,AboutDlgProc);
		ShowWindow(SettingDlg, SW_SHOW);
		break;
	case IDC_QUIT:
		PostQuitMessage(0);
		break;
	}
}

void MyWindow::OnDestroy()
{
	::PostQuitMessage(0);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MyWindow wnd;
	
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	char s[128];
	LoadString(0, IDS_STRING104, s, sizeof s);
	wnd.Create(NULL, WS_OVERLAPPED | WS_VISIBLE,s, (int)hMenu, CW_USEDEFAULT, CW_USEDEFAULT,800,600);

	return app.Run();
}

