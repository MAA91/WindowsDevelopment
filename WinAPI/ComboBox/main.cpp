#include<Windows.h>
#include<string>
#include"resource.h"

#define _CRT_SECURE_NO_WARNINGS

CONST CHAR* g_COMBO_BOX_ITEMS[] = {"This", "is", "my", "First", "Combo", "Box"};

void Sort(char** buffer, const int size);

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

void Sort(char** buffer, const int size)
{
	char** SORT_BUFFER = new char* [size];
	for (int i = 0; i < size; i++)
	{
		SORT_BUFFER[i] = new char[256] {};
		strcpy_s(SORT_BUFFER[i], 256, buffer[i]);
		_strupr_s(SORT_BUFFER[i], 256);
	}
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			char* buf = new char[256];
			char* BUF = new char[256];
			if (strcmp(SORT_BUFFER[j], SORT_BUFFER[j + 1]) > 0)
			{
				strcpy_s(BUF, 256, SORT_BUFFER[j]);
				strcpy_s(SORT_BUFFER[j], 256, SORT_BUFFER[j + 1]);
				strcpy_s(SORT_BUFFER[j + 1], 256, BUF);

				strcpy_s(buf, 256, buffer[j]);
				strcpy_s(buffer[j], 256, buffer[j + 1]);
				strcpy_s(buffer[j + 1], 256, buf);
			}
			delete[] buf;
			delete[] BUF;
		}
	for (int i = 0; i < size; i++)
		delete[] SORT_BUFFER[i];
	delete[] SORT_BUFFER;
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
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEMS[i]);
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_CHECKBOX:
		{
			HWND hCheck = GetDlgItem(hwnd, IDC_CHECKBOX);
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT COUNT = SendMessage(hCombo, CB_GETCOUNT, 0, 0);

			if (SendMessage(hCheck, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				CHAR** buffer = new CHAR*[COUNT];

				for (int i = 0; i < COUNT; i++)
				{
					buffer[i] = new CHAR[256]{};
					SendMessage(hCombo, CB_GETLBTEXT, 0, (LPARAM)buffer[i]);
					SendMessage(hCombo, CB_DELETESTRING, 0, 0);
				}

				Sort(buffer, COUNT);

				for (int i = 0; i < COUNT; i++)
				{
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)buffer[i]);
					delete[] buffer[i];
				}
				delete[] buffer;
			}
			if (SendMessage(hCheck, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
				for (int i = 0; i < COUNT; i++)
				{
					SendMessage(hCombo, CB_DELETESTRING, 0, 0);
					SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEMS[i]);
				}
		}
			break;
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