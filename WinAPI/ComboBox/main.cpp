#include<Windows.h>
#include<string>
#include"resource.h"

#define _CRT_SECURE_NO_WARNINGS


CONST CHAR* g_COMBO_BOX_ITEMS[] = { "This", "is", "my", "First", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//ICON
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_COMBO_BOX_ITEMS) / sizeof(g_COMBO_BOX_ITEMS[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEMS[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);

			INT index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR* text = new CHAR[SendMessage(hCombo, CB_GETLBTEXTLEN, (WPARAM)index, 0)];
			SendMessage(hCombo, CB_GETLBTEXT, (WPARAM)index, (LPARAM)text);

			std::string buffer = "Вы выбрали пункт №" + std::to_string(index);
			buffer += " со значением ";
			buffer += text;

			MessageBox(NULL, buffer.c_str(), "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}