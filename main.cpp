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
	HWND hDlg;

	switch (id)
	{
	case IDC_START:
		MessageBox(NULL, "start", NULL, MB_OK);
			break;
	case IDC_SETTING:
		hDlg = CreateDialog(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_DIALOG2),NULL,AboutDlgProc);
		ShowWindow(hDlg, SW_SHOW);
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

