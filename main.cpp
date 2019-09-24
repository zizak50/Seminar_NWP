#include "nwpwin.h"
#include "Dlgdef.h"
#include "resource1.h"
#include <windows.h>
#include <string>
#include <iostream>

class End_Dialog : public Dialog {
	int moves = 0;
protected:
	int IDD();
	bool OnInitDialog(HWND hw);
public:
	int GetMoves() {
		return moves;
	}
	void SetMoves(int i) {
		moves = i;
	}
};

int End_Dialog::IDD() {
	return IDD_DIALOG1;
}

bool End_Dialog::OnInitDialog(HWND hw) {

	int i = GetMoves();
	char s[128];
	std::string moves_s = std::to_string(i);
	SetDlgItemText(*this, IDC_STATIC_MOVES, moves_s.c_str());

	if (i <= 7)
	{
		LoadString(0, IDS_STRING107, s, sizeof s);
		SetDlgItemText(*this, IDC_STATIC_RESULT, s);

	}
	if (i >= 8)
	{
		LoadString(0, IDS_STRING106, s, sizeof s);
		SetDlgItemText(*this, IDC_STATIC_RESULT, s);
	}
	if (i >= 11)
	{
		LoadString(0, IDS_STRING105, s, sizeof s);
		SetDlgItemText(*this, IDC_STATIC_RESULT, s);
	}
	return true;
}

class MyWindow : public Window {

protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnPaint(HDC hdc);
	void OnKeyDown(int vk);
	void OnDestroy();

	POINT Curren_pos();
	void New_pos(int x, int y);
	void Relese_Tile(POINT p);

public:
	int GetMovesMyWindow() {
		return moves;
	};
	void SetMoves(int i) {
		moves = moves+i;
	}
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
		{1,0,1,0,0},
		{1,0,1,0,1},
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
			SetMoves(1);
			Relese_Tile(cur_position);
			New_pos(cur_position.x + 1, cur_position.y);
			InvalidateRect(*this, NULL, true);

			End_Dialog endDia;
			endDia.SetMoves(GetMovesMyWindow());
			endDia.DoModal(0, *this);
		}
		else if (game_map[cur_position.x + 1][cur_position.y] == 0) {
			SetMoves(1);
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
			SetMoves(1);
			Relese_Tile(cur_position);
			New_pos(cur_position.x - 1, cur_position.y);
			InvalidateRect(*this, NULL, true);

			End_Dialog endDia;
			endDia.DoModal(0, *this);
		}
		else if (game_map[cur_position.x - 1][cur_position.y] == 0) {
			SetMoves(1);
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
			SetMoves(1);
			Relese_Tile(cur_position);
			New_pos(cur_position.x, cur_position.y+1);
			InvalidateRect(*this, NULL, true);

			End_Dialog endDia;
			endDia.DoModal(0, *this);
		}
		else if (game_map[cur_position.x][cur_position.y + 1] == 0)
		{
			SetMoves(1);
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
			SetMoves(1);
			Relese_Tile(cur_position);
			New_pos(cur_position.x, cur_position.y-1);
			InvalidateRect(*this, NULL, true);

			End_Dialog endDia;
			endDia.DoModal(0, *this);
		}
		else if (game_map[cur_position.x][cur_position.y-1]==0)
		{
			SetMoves(1);
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

