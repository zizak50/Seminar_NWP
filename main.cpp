#include "nwpwin.h"
#include "resource1.h"
#include <windows.h>
#include <string.h>
#include <iostream>

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:

		return TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_QUIT:
			EndDialog(hwnd, IDOK);
			::PostQuitMessage(0);
			break;
		case ID_NewGame:

			EndDialog(hwnd, IDCANCEL);
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
	void OnPaint(HDC hdc);
	void OnKeyDown(int vk);
	void OnDestroy();

	POINT Curren_pos();
	void New_pos(int x,int y);
	void Relese_Tile(POINT p);

public:
	COLORREF color_wall = RGB(0, 0, 0);
	COLORREF color_path = RGB(0, 255, 0);
	COLORREF color_start = RGB(255, 0, 0);
	COLORREF color_end = RGB(255, 255, 0);

	int x = 5;
	int y = 5;

	POINT cur_position;

	int moves = 0;

	// 0-path
	// 1-wall
	// 2-start/current_postition
	// 3-end
	int game_map[5][5] = {
		{1,2,1,1,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,0,0,0,1},
		{1,1,1,3,1} 
	};
};

POINT MyWindow::Curren_pos() {
	POINT p;

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) {
			if (game_map[i][j] == 2) {
				p.x = i;
				p.y = j;
				return p;
			}
		}
	}
}

void MyWindow::New_pos(int x,int y) {
	game_map[x][y] = 2;
}

void MyWindow::Relese_Tile(POINT p) {
	game_map[p.x][p.y] = 0;

}

void MyWindow::OnPaint(HDC hdc) {

	RECT rc;
	HBRUSH brush= CreateSolidBrush(color_path);
	GetClientRect(*this, &rc);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, 0);
	SetWindowExtEx(hdc, x, y, 0);

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++)
		{
			if (game_map[j][i] == 0) {
				brush = CreateSolidBrush(color_path);
				RECT r = { i,j,i + 1,j + 1 };
				FillRect(hdc, &r, brush);
			}

			if (game_map[j][i] == 1) {
				brush= CreateSolidBrush(color_wall);
				RECT r = { i,j,i + 1,j + 1 };
				FillRect(hdc, &r, brush);
			}

			if (game_map[j][i] == 2) {
				brush = CreateSolidBrush(color_start);
				RECT r = { i,j,i + 1,j + 1 };
				FillRect(hdc, &r, brush);
			}

			if (game_map[j][i] == 3) {
				brush = CreateSolidBrush(color_end);
				RECT r = { i,j,i + 1,j + 1 };
				FillRect(hdc, &r, brush);
			}
		}
	}
	DeleteObject(brush);
}

void MyWindow::OnKeyDown(int key) {

	cur_position = Curren_pos();

	switch (key)
	{
	case VK_DOWN:
		if (game_map[cur_position.x + 1][cur_position.y] == 1)
		{
			break;
		}
		else if (game_map[cur_position.x+1][cur_position.y] == 3)
		{
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x + 1, cur_position.y);
			InvalidateRect(*this, NULL, true);

			HWND dialog=CreateDialog(NULL, MAKEINTRESOURCE (IDD_DIALOG1), *this, (DLGPROC) DlgProc);
			ShowWindow(dialog, 1);

		}
		else if (game_map[cur_position.x + 1][cur_position.y] == 0) {
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x + 1, cur_position.y);
			InvalidateRect(*this, NULL, true);
		}
		break;
	case VK_UP:
		if (game_map[cur_position.x - 1][cur_position.y] == 1)
		{
			break;
		}
		else if (game_map[cur_position.x-1][cur_position.y] == 3)
		{
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x - 1, cur_position.y);
			InvalidateRect(*this, NULL, true);
		}
		else if (game_map[cur_position.x - 1][cur_position.y] == 0) {
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x - 1, cur_position.y);
			InvalidateRect(*this, NULL, true);
		}
		break;

	case VK_RIGHT:
		if (game_map[cur_position.x][cur_position.y + 1] == 1)
		{
			break;
		}
		else if (game_map[cur_position.x][cur_position.y + 1] == 3)
		{
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x, cur_position.y+1);
			InvalidateRect(*this, NULL, true);
		}
		else if (game_map[cur_position.x][cur_position.y + 1] == 0)
		{
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x, cur_position.y+1);
			InvalidateRect(*this, NULL, true);
		}
		break;

	case VK_LEFT:
		if (game_map[cur_position.x][cur_position.y - 1] == 1) {

			break;
		}
		else if (game_map[cur_position.x][cur_position.y - 1] == 3)
		{
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x, cur_position.y-1);
			InvalidateRect(*this, NULL, true);
		}
		else if (game_map[cur_position.x][cur_position.y-1]==0)
		{
			moves + 1;
			Relese_Tile(cur_position);
			New_pos(cur_position.x, cur_position.y-1);
			InvalidateRect(*this, NULL, true);
		}
		break;
	case VK_ESCAPE:
		::PostQuitMessage(0);
	}
}

int MyWindow::OnCreate(CREATESTRUCT* psc)
{	
	return 0;
}
void MyWindow::OnCommand(int id)
{
	
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

