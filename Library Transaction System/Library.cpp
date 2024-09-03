#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.Syndication.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "MS.h"
#include "Book.h"
#include "Member.h"
#include "tchar.h"
#include "Transaction.h"
#include "winAtts.h"
#include <commctrl.h>
#include <fstream>
#include <array>

#define NEW_BUTTON  2000
#define QUIT 1000
bool bEmpty = false;


using namespace std;

/*
* Based off of UML suggestion with
* screenshots provided.
*
* All relevant documentation included
* in MS header file, though none of it is
* revelant so I wouldn't bother being nosey
*/

HINSTANCE hInst;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nProc(HWND hwnd, UINT eMsg, WPARAM eParam, LPARAM eparam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	wchar_t LIB_NAME[500] = L"Library";

	WNDCLASS winD = {};
	winD.lpfnWndProc = WindowProc;
	winD.hInstance = hInstance;
	winD.lpszClassName = LIB_NAME;
	//Prevent black bars/ghosting
	winD.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	winD.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&winD);



	HWND hwnd = CreateWindowEx(
		0,
		LIB_NAME,
		L"Library Transaction System",
		WS_OVERLAPPEDWINDOW,
		100, 100, 800, 600,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	ShowWindowAsync(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	//Use CreateMenu() for menuBar
	

	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}

	return (int)nMes.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	vector<Book> bVector;
	
	static wstring out;

	BS_PUSHBUTTON();

	Library lib;

	Book b1 = Book("A Farewell to Arms", "Ernest Hemingway", "1451658168", true, "Fiction");
	Book b2 = Book("Lord of The Flies", "William Golding", "0399501487", true, "Fiction");
	lib.addBook(b1);
	lib.addBook(b2);

	Member* m2;

	m2 = new Member(L"Victoria", L"Beverly Hills", 90210, bVector);

	static HWND textEdit;
	static HWND getAddress;


	switch (uMsg) {


	case WM_CREATE:
	{
		HINSTANCE inst = ((LPCREATESTRUCT)lParam)->hInstance;

		CreateWindowEx(0, L"button", L"Register Member", WS_CHILD | WS_VISIBLE, 300, 400, 175, 50, hwnd, (HMENU)NEW_BUTTON, inst, 0);
		textEdit = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 335, 250, 20, hwnd, 0, inst, 0);
		getAddress = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 260, 370, 250, 20, hwnd, 0, inst, 0);
		wchar_t placeholder[] = L"Enter a member name";
		wchar_t pAddress[] = L"Please enter an address";
		Edit_SetCueBannerText(textEdit, placeholder);
		Edit_SetCueBannerText(getAddress, pAddress);

		HMENU menuBar = CreateMenu();
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuBar, L"File");
		AppendMenu(menuBar, MF_POPUP, (UINT_PTR)menuBar, L"About");
		AppendMenu(menuBar, MF_STRING, QUIT, L"Quit");
		SetMenu(hwnd, menuBar);


		break;

	}


	case WM_COMMAND:
	{

		string name;
		int errShow = SW_SHOWNORMAL;

		if (LOWORD(wParam) == NEW_BUTTON) {
			wchar_t tText[300];
			wchar_t tAddress[300];
			GetWindowText(textEdit, tText, 300);

			GetWindowText(getAddress, tAddress, 300);

			

			if (!iswalpha(tText[0])) {

				bEmpty = true;

				HINSTANCE nInst = GetModuleHandle(nullptr);
				wchar_t errorLib[50] = L"ERROR";

				WNDCLASS errorWindow = {};
				errorWindow.lpfnWndProc = nProc;
				errorWindow.hInstance = nInst;
				errorWindow.lpszClassName = errorLib;
				errorWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW);
				errorWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);

				RegisterClass(&errorWindow);

				HWND eMenu = CreateWindowEx(
					0,
					errorLib,
					L"Error",
					WS_OVERLAPPEDWINDOW,
					100, 100, 400, 100,
					nullptr,
					nullptr,
					nInst,
					nullptr

				);

				ShowWindow(eMenu, errShow);
				UpdateWindow(eMenu);
				
			}

			Member* m1 = new Member(tText, tAddress, 999, bVector);
			out = lib.RegisterMember(m1);

			ofstream nstream("users.txt", std::ios::app);

			wstring sName = m1->getName();
			int sId = m1->getMemberId();

			string sInfoN(sName.begin(), sName.end());

			nstream << sInfoN << endl;
			nstream << sId << endl;


			InvalidateRect(hwnd, NULL, true);
		}

		if (LOWORD(wParam) == QUIT) {
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
		break;
	}


	case WM_PAINT:
	{


		PAINTSTRUCT p;

		HDC hdc = BeginPaint(hwnd, &p);


		/*
		* TextOut(param1, param2, . . . , param5)
		* does not support carriage return
		* 
		* and neither do I
		*/

		RECT r;

	
		GetClientRect(hwnd, &r);
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);

		DrawText(hdc, out.c_str(), -1, &r, DT_WORDBREAK);
		
		EndPaint(hwnd, &p);
		break;

	}

	/*
		* If you're going to close the window,
		* just close the window.
		* kthx
		*/

	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}

	case WM_DESTROY: {

		PostQuitMessage(0);
		break;

	}
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK nProc(HWND hwnd, UINT eMsg, WPARAM eParam, LPARAM eparam) {

	switch (eMsg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	

	return DefWindowProc(hwnd, eMsg, eParam, eparam);

}