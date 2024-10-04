#include<Windows.h>
#include<string>
#include"resource.h"

CONST CHAR* g_LIST_BOX_ITEMS[] = { "This", "is", "my", "First", "List", "Box"};

BOOL CALLBACK AddProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_LIST), NULL, ListProc, 0);
	return 0;
}

BOOL CALLBACK AddProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			
			HWND hParent = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer) == LB_ERR)
			{
				bool flag = false;
				for(UINT i = 0; i < strlen(sz_buffer); i++)
					if (sz_buffer[i] != '\0' and sz_buffer[i] != '\n' and sz_buffer[i] != ' ')
					{
						flag = true;
						break;
					}

				if (flag)
				{
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
					EndDialog(hwnd, 0);
				}
				else
					MessageBox(hwnd, "Невозможно ввести пустую строку", "Error", MB_OK | MB_ICONERROR);
			}
			else
				MessageBox(hwnd, "Такое вхождение уже существует", "Error", MB_OK | MB_ICONERROR);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK EditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_SETTEXT, 0, lParam);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{ 
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_NAME), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

			HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST1);
			if (SendMessage(hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer) == LB_ERR)
			{
				bool flag = false;
				for (UINT i = 0; i < strlen(sz_buffer); i++)
					if (sz_buffer[i] != '\0' and sz_buffer[i] != '\n' and sz_buffer[i] != ' ')
					{
						flag = true;
						break;
					}
				if (flag)
				{
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
					SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
					EndDialog(hwnd, 0);
				}
				else
					MessageBox(hwnd, "Невозможно ввести пустую строку", "Error", MB_OK | MB_ICONERROR);
			}
			else MessageBox(hwnd, "Такое вхождение уже существует", "Error", MB_OK | MB_ICONERROR);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK ListProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);

		for (int i = 0; i < sizeof(g_LIST_BOX_ITEMS) / sizeof(g_LIST_BOX_ITEMS[0]); i++)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEMS[i]);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_EDIT:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);

			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);

			if (index != LB_ERR)
			{
				CHAR* text = new CHAR[SendMessage(hList, LB_GETTEXTLEN, (WPARAM)index, 0)];
				SendMessage(hList, LB_GETTEXT, (WPARAM)index, (LPARAM)text);
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_EDIT), hwnd, EditProc, (LPARAM)text);
			}
			else
				MessageBox(hwnd, "Вы не выбрали значение для редактирования!", "Error", MB_OK | MB_ICONERROR);
		}
			break;
		case IDC_BUTTON_ADD:
		{
			//GetModuleHandle - возвращает hInstance запущенной программы
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, AddProc, 0);
		}
		break;
		case IDC_BUTTON_DELETE:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);

			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);

			if (index != LB_ERR)
			{
				CHAR* text = new CHAR[SendMessage(hList, LB_GETTEXTLEN, (WPARAM)index, 0)];
				SendMessage(hList, LB_GETTEXT, (WPARAM)index, (LPARAM)text);

				std::string buffer = "Вы действительно хотите удалить пункт №" + std::to_string(index);
				buffer += " со значением \'";
				buffer += text;
				buffer += "\'";

				if (MessageBox(hwnd, buffer.c_str(), "Delete", MB_YESNO | MB_ICONQUESTION) == IDYES)
					SendMessage(hList, LB_DELETESTRING, index, 0);
			}
			else
				MessageBox(hwnd, "Вы не выбрали значение для удаления!", "Error", MB_OK | MB_ICONERROR);
		}
		break;
		case IDOK: 
		{
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);

			INT index = SendMessage(hList, LB_GETCURSEL, 0, 0);
			
			if (index != LB_ERR)
			{
				CHAR* text = new CHAR[SendMessage(hList, LB_GETTEXTLEN, (WPARAM)index, 0)];
				SendMessage(hList, LB_GETTEXT, (WPARAM)index, (LPARAM)text);

				std::string buffer = "Вы выбрали пункт №" + std::to_string(index);
				buffer += " со значением \'";
				buffer += text;
				buffer += "\'";
				MessageBox(hwnd, buffer.c_str(), "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
				MessageBox(hwnd, "Вы не выбрали значение!", "Info", MB_OK | MB_ICONERROR);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}