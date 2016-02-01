﻿#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <sstream>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("buy");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Покупка в магазине");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application

	//Ñîçäàåì îêíî
	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static HWND Edit111, add, hListBox1, delet, hListBox2, summa;


	switch (message)
	{
	// Parse the menu selections:
	case WM_CREATE:
	{
					  add = CreateWindow(TEXT("button"), TEXT(">"), WS_CHILD | WS_VISIBLE, 260, 95, 50, 30, hWnd, (HMENU)100, ((LPCREATESTRUCT)lParam)->hInstance, 0);
					  delet = CreateWindow(TEXT("button"), TEXT("<"), WS_CHILD | WS_VISIBLE, 260, 145, 50, 30, hWnd, (HMENU)109, ((LPCREATESTRUCT)lParam)->hInstance, 0);
					  hListBox1 = CreateWindow(TEXT("ListBox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 30, 30, 200, 250, hWnd, (HMENU)101, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
					  hListBox2 = CreateWindow(TEXT("ListBox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 350, 30, 200, 250, hWnd, (HMENU)112, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
					  summa = CreateWindow(TEXT("Edit"), TEXT("Element count: 0"), WS_CHILD | WS_VISIBLE | LBS_STANDARD, 100, 350, 400, 30, hWnd, (HMENU)112, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
					  //summa = CreateWindow(L"Static", NULL, WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE, 220, 315, 65, 20, hWnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
					  SendMessage(hListBox1, LB_ADDSTRING, (WPARAM)L"10000", (LPARAM)L"Молоко");
					  SendMessage(hListBox1, LB_ADDSTRING, (WPARAM)L"7500", (LPARAM)L"Хлеб");
					  SendMessage(hListBox1, LB_ADDSTRING, (WPARAM)L"50000", (LPARAM)L"Тортик");
					  SendMessage(hListBox1, LB_ADDSTRING, (WPARAM)L"25000", (LPARAM)L"Чай");
					  break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 101:
			if (HIWORD(wParam) == LBN_SELCHANGE)//проверка на условия выбора в listbox
			{
				int element_count = 0;
				int a = SendMessage(hListBox1, LB_GETCURSEL, 0, 0);//выбор индекса
				TCHAR ad[100];
				a = SendMessage(hListBox1, LB_GETTEXT, a, (LPARAM)ad);//по индексу выбирается имя
				SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)ad);
				TCHAR s[100];
				a = SendMessage(hListBox1, LB_GETTEXT, a, (WPARAM)s);//по индексу выбирается имя
				SendMessage(summa, LB_ADDSTRING, 0, (WPARAM)s);


				/*std::wstringstream summ;
				summ << L"Element count: " << ++element_count;
				SetWindowText(summa, summ.str().c_str());*/
			}
			break;
		case 112:
			if (HIWORD(wParam) == LBN_SELCHANGE)//проверка на условия выбора в listbox
			{
				int d = SendMessage(hListBox2, LB_GETCURSEL, 0, 0);//выбор индекса
				SendMessage(hListBox2, LB_DELETESTRING, d, 0);
			}
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 10, TEXT("Магазин"), _tcslen(TEXT("Магазин")));
		TextOut(hdc, 420, 10, TEXT("Корзина"), _tcslen(TEXT("Корзина")));
		TextOut(hdc, 255, 290, TEXT("Стоимость"), _tcslen(TEXT("Стоимость")));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}