#pragma once
#include <string>


typedef std::basic_string<TCHAR> tstring;

class Dialog
{
	int moves;
	HWND hw;
public:
	static int CALLBACK Proc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
	operator HWND() const { return hw; }
	int DoModal(HINSTANCE, HWND parent = 0);
	void SetMoves(int i) { moves = i; };
	int GetMoves() { return moves; }
protected:
	//	overridables
	virtual int IDD() = 0;
	virtual bool OnInitDialog(HWND hw) { return false; }
	virtual bool OnCommand(int id, int code) { return false; }
	virtual bool OnOK() { return true; }
	virtual void OnCancel() { }
};
