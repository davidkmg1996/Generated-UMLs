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
#define NEW_BUTTON  2000


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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	wchar_t LIB_NAME[500] = L"Library";

	WNDCLASS winD = {};
	winD.lpfnWndProc = WindowProc;
	winD.hInstance = hInstance;
	winD.lpszClassName = LIB_NAME;
	//Prevent black bars/ghosting
	winD.hbrBackground = (HBRUSH)(COLOR_WINDOW)	;
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

	
	PAINTSTRUCT q;
	


	

	ShowWindowAsync(hwnd, nCmdShow);
	UpdateWindow(hwnd); 

	MSG nMes;

	while (GetMessage(&nMes, nullptr, 0, 0)) {
		TranslateMessage(&nMes);
		DispatchMessage(&nMes);
	}

	return (int)nMes.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	vector<Book> bVector;

	BS_PUSHBUTTON();

	Library lib;

	Book b1 = Book("A Farewell to Arms", "Ernest Hemingway", "1451658168", true, "Fiction");
	Book b2 = Book("Lord of The Flies", "William Golding", "0399501487", true, "Fiction");
	lib.addBook(b1);
	lib.addBook(b2);

	Member* m1;
	Member* m2;


	m1 = new Member(L"David", L"Sesame Street", 999, bVector);
	m2 = new Member(L"Victoria", L"Beverly Hills", 90210, bVector);

	lib.returnBook(*m1, b1);

		PAINTSTRUCT paint;
		HDC begin = BeginPaint(hwnd, &paint);


		

		m1->borrowBook(b1);
		cout << b1.isAvailable();
		m1->borrowBook(b2);
		m1->returnBook(b1);

		switch (uMsg) {
		
		/*
		* If you're going to close the window,
		* just close the window.
		* kthx
		*/
		

		case WM_CREATE:
		{
			HINSTANCE inst = ((LPCREATESTRUCT)lParam)->hInstance;
			
			CreateWindowEx(0, L"button", L"Register Member", WS_CHILD | WS_VISIBLE, 300, 400, 175, 50, hwnd, (HMENU)NEW_BUTTON, inst, 0);
			HWND textEdit = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 175, 200, 400, 150, hwnd, 0, inst, 0);

			

			
			break;

		}

	


		case WM_COMMAND:
		{
			if (LOWORD(wParam) == NEW_BUTTON) {
				lib.RegisterMember(m1);
				InvalidateRect(hwnd, NULL, TRUE);
			}
		}
			

		case WM_PAINT:	
		{
			PAINTSTRUCT p;
		
			HDC hdc = BeginPaint(hwnd, &paint);

			
			

			
		
			/*
			* TextOut(param1, param2, . . . , param5)  
			* does not support carriage return
			*/

			RECT r;
			
		


			
			
			PAINTSTRUCT newPaint;
			GetClientRect(hwnd, &r);

			RECT r1 = r;
			RECT r2 = r;
			GetClientRect(hwnd, &r2);
			int y = r.bottom - r.top - 450;
			r2.top += y;
			SetTextColor(hdc, RGB(0, 0, 0));
			SetBkMode(hdc, TRANSPARENT);
			DrawText(hdc, lib.RegisterMember(m1).c_str(), -1, &r1, DT_WORDBREAK);
			DrawText(hdc, lib.RegisterMember(m2).c_str(), -1, &r2, DT_WORDBREAK);
		
			EndPaint(hwnd, &paint);
			break;
			

			
		}
		
		
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

