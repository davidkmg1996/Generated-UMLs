#define NEW_BUTTON  2000
#define QUIT 1000
bool bEmpty;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nProc(HWND nwnd, UINT eMsg, WPARAM eParam, LPARAM eParamL);

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

		sqlite3* db;
		int getDb;

		getDb = sqlite3_open("users.db", &db);

		string name;
		int errShow = SW_SHOWNORMAL;

		if (LOWORD(wParam) == NEW_BUTTON) {
			wchar_t tText[300];
			wchar_t tAddress[300];
			GetWindowText(textEdit, tText, 300);

			GetWindowText(getAddress, tAddress, 300);

			//Use null character
			for (int i = 0; tText[i] != '\0'; i++) {

				if (!iswalpha(tText[i])) {

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
				break;

				}
				else {
					bEmpty = false;
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

			}
		

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

			if (bEmpty == false) {
				DrawText(hdc, out.c_str(), -1, &r, DT_WORDBREAK);
			}
		

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

LRESULT CALLBACK nProc(HWND nwnd, UINT eMsg, WPARAM eParam, LPARAM eParamL) {

	PAINTSTRUCT e;

	HDC edc;

	RECT eR;

	switch (eMsg) {

	case WM_PAINT:
		edc = BeginPaint(nwnd, &e);
		SetTextColor(edc, RGB(0, 0, 0));
		SetBkMode(edc, TRANSPARENT);
		GetClientRect(nwnd, &eR);
		DrawText(edc, L"Member Name must contain only alphabetic characters", -1, &eR, DT_WORDBREAK);
		EndPaint(nwnd, &e);
		break;

	case WM_CLOSE:
		DestroyWindow(nwnd);
		break;

	}

	return DefWindowProc(nwnd, eMsg, eParam, eParamL);

}