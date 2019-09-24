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
	void OnCancel();
	void SetStringInStatic(int id) {
		char s[128];
		switch (id)
		{
		case IDS_STRING107:
			LoadString(0, IDS_STRING107, s, sizeof s);
			break;
		case IDS_STRING106:
			LoadString(0, IDS_STRING106, s, sizeof s);
			break;
		case IDS_STRING105:
			LoadString(0, IDS_STRING105, s, sizeof s);
			break;
		default:
			break;
		}
		SetDlgItemText(*this, IDC_STATIC_RESULT, s);
	}

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

	std::string moves_s = std::to_string(i);
	SetDlgItemText(*this, IDC_STATIC_MOVES, moves_s.c_str());

	if (i <= 7)
		SetStringInStatic(IDS_STRING107);
	if (i >= 8)
		SetStringInStatic(IDS_STRING106);
	if (i >= 11)
		SetStringInStatic(IDS_STRING105);
	return true;
}

 void End_Dialog::OnCancel() {
	 PostQuitMessage(0);
 }

class MyWindow : public Window {

protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnPaint(HDC hdc);
	void OnKeyDown(int vk);
	void OnDestroy();

	POINT Curren_pos();

	void New_pos(int x, int y);
	void Relese_Tile(POINT p);

	void PaintSquare(HDC hdc ,HBRUSH brush, int color, int i, int j) {

		RECT r = { i,j,i + 1,j + 1 };

		switch (color)
		{
		case 0:
			brush = CreateSolidBrush(color_path);
			break;
		case 1:
			brush = CreateSolidBrush(color_wall);
			break;
		case 2:
			brush = CreateSolidBrush(color_start);
			break;
		case 3:
			brush = CreateSolidBrush(color_end);
			break;

		default:
			break;
		}
		FillRect(hdc, &r, brush);
		DeleteObject(brush);
	}

	void Move(int key ,POINT cur_position) {

		SetMoves(1);
		Relese_Tile(cur_position);

		switch (key)
		{
		case VK_DOWN:
			New_pos(cur_position.x + 1, cur_position.y);
			break;
		case VK_UP:
			New_pos(cur_position.x -1, cur_position.y);
			break;
		case VK_RIGHT:
			New_pos(cur_position.x, cur_position.y+1);
			break;
		case VK_LEFT:
			New_pos(cur_position.x, cur_position.y-1);
			break;
		default:
			break;
		}
		InvalidateRect(*this, NULL, true);
	}

	void OnEndPosition() {
		End_Dialog endDia;
		endDia.SetMoves(GetMovesMyWindow());
		endDia.DoModal(0, *this);
	}

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
			if (game_map[j][i] == 0)
				PaintSquare(hdc, brush, game_map[j][i], i, j);
			if (game_map[j][i] == 1)
				PaintSquare(hdc, brush, game_map[j][i], i, j);
			if (game_map[j][i] == 2) 
				PaintSquare(hdc, brush, game_map[j][i], i, j);
			if (game_map[j][i] == 3) 
				PaintSquare(hdc, brush, game_map[j][i], i, j);
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
			break;
		else if (game_map[cur_position.x+1][cur_position.y] == 3)
		{
			Move(key, cur_position);
			OnEndPosition();
		}
		else if (game_map[cur_position.x + 1][cur_position.y] == 0)
			Move(key, cur_position);
		break;
	case VK_UP:
		if (game_map[cur_position.x - 1][cur_position.y] == 1)
			break;
		else if (game_map[cur_position.x-1][cur_position.y] == 3)
		{
			Move(key, cur_position);
			OnEndPosition();
		}
		else if (game_map[cur_position.x - 1][cur_position.y] == 0)
			Move(key, cur_position);
		break;

	case VK_RIGHT:
		if (game_map[cur_position.x][cur_position.y + 1] == 1)
			break;
		else if (game_map[cur_position.x][cur_position.y + 1] == 3)
		{
			Move(key, cur_position);
			OnEndPosition();
		}
		else if (game_map[cur_position.x][cur_position.y + 1] == 0)
			Move(key, cur_position);
		break;

	case VK_LEFT:
		if (game_map[cur_position.x][cur_position.y - 1] == 1)
			break;
		else if (game_map[cur_position.x][cur_position.y - 1] == 3)
		{
			Move(key, cur_position);
			OnEndPosition();
		}
		else if (game_map[cur_position.x][cur_position.y-1]==0)
			Move(key, cur_position);
		break;
	case VK_ESCAPE:
		::PostQuitMessage(0);
	}
}

int MyWindow::OnCreate(CREATESTRUCT* psc)
{	
	return 0;
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

