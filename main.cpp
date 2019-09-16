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

BOOL CALLBACK SettingModlaProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		for (int i = 0; i < 3; i++)
		{
			char s[24]; sprintf(s, "%d", i);
			SendDlgItemMessage(hwnd, IDC_LIST1, CB_ADDSTRING, 0, (LPARAM)s);
		}
		SendDlgItemMessage(hwnd,IDC_LIST1,LB_SETCURSEL,2,0);
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
	int life = 25;

	POINT current_pos,end_pos;

	//broj 0: oznacava polja za kretanje
	//broj 1: oznacava zid
	//broj 2: oznacava pocetak
	//broj 3: oznacava kraj
	//broj 4: polje na kojemu se nalazimo
	int map[8][8] = {
		{1,3,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,0,0,0,1,1,0,1},
		{1,1,1,1,1,1,2,1},
	};

protected:

	int Get(int x, int y) {
		return map[x][y];
	}

	void Set(int x, int y, int value) {
		map[x][y] = value;
	}

	void SetCurrentPosToStart() {
	
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) {
				if (map[i][j] == 2) {
					current_pos.x = i;
					current_pos.y = j;
				}
			}
		}
	}

	POINT GetCurrentPos() {
		return current_pos;
	}

	void SetCurrentPos(int x,int y) {
	
		map[x][y] = 4;
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
		SetCurrentPosToStart();

		return 0;
	}

	void OnCommand(int id) {
		/*switch (id)
		{
		case VK_LEFT:
			// Process the LEFT ARROW key.
			POINT p = GetCurrentPos();
			if (p.x - 1 == 1)
			{
				life - 1;
			}
			else {
				SetCurrentPos(p.x-1, p.y);
			}
			break;
		case VK_RIGHT:
			// Process the RIGHT ARROW key.
			POINT p = GetCurrentPos();
			if (p.x + 1 == 1)
			{
				life - 1;
			}
			else {
				SetCurrentPos(p.x+1, p.y);
			}
			break;
		case VK_UP:
			// Process the UP ARROW key.
			POINT p = GetCurrentPos();
			if (p.y+1==1)
			{
				life - 1;
			}
			else {
				SetCurrentPos(p.x, p.y + 1);
			}
		}*/

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
		if (IDOK == DialogBox(0, MAKEINTRESOURCE(IDD_DIALOG2), *this, SettingModlaProc));
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

