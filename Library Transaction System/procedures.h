#define NEW_BUTTON  2000
#define QUIT 1000
#define LOGIN 2000
#define	REGISTER 2000
bool bEmpty;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK nProc(HWND nwnd, UINT eMsg, WPARAM eParam, LPARAM eParamL);
LRESULT CALLBACK login(HWND lwnd, UINT lMsg, WPARAM lParam, LPARAM lParamL);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	vector<Book> bVector;

	static wstring out;

	BS_PUSHBUTTON();

	Library lib;

	Book b1 = Book(L"A Farewell to Arms", L"Ernest Hemingway", L"1451658168", true, L"Fiction");
	Book b2 = Book(L"Lord of The Flies", L"William Golding", L"0399501487", true, L"Fiction");
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

		getDb = sqlite3_open("users", &db);

		string name;
		string address;
		int sId;
		sqlite3_stmt* n;
		int errShow = SW_SHOWNORMAL;

		if (LOWORD(wParam) == NEW_BUTTON) {
			wchar_t tText[300];
			wchar_t tAddress[300];

			if (GetWindowText(textEdit, tText, 300) != NULL) {
				GetWindowText(textEdit, tText, 300);
			}
			else {
				return 0;
			}
			if (GetWindowText(getAddress, tAddress, 300) != NULL) {
				GetWindowText(getAddress, tAddress, 300);
			}
			else {
				return 0;
			}
			

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
					string name2(sName.begin(), sName.end());
					name = name2;

					wstring sAddress = m1->getAddress();
					string address2(sAddress.begin(), sAddress.end());
					address = address2;


					sId = m1->getMemberId();
					
					string sInfoN(sName.begin(), sName.end());

					nstream << sInfoN << endl;
					nstream << sId << endl;


					InvalidateRect(hwnd, NULL, true);

				}

			}

			


			const char* createTable = "CREATE TABLE users(userName varchar(255), address varchar(255), memberId int, type varchar(255));";
			getDb = sqlite3_exec(db, createTable, 0, 0, 0);

			const char* sqlStatement = "INSERT INTO users(userName, address, memberId, type) VALUES (?, ?, ?, ?); ";

			getDb = sqlite3_prepare_v2(db, sqlStatement, -1, &n, 0);

			sqlite3_bind_text(n, 1, name.c_str(), name.length(), SQLITE_STATIC);
			sqlite3_bind_text(n, 2, address.c_str(), address.length(), SQLITE_STATIC);
			sqlite3_bind_int(n, 3, sId);
			sqlite3_bind_text(n, 4, "member", 10, SQLITE_STATIC);

			getDb = sqlite3_step(n);

			sqlite3_finalize(n);

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

void showMainScreen() {

	wchar_t LIB_NAME[500] = L"Library";
	HINSTANCE hInstance = GetModuleHandle(nullptr);
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

	ShowWindowAsync(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg = {};

	/*
	* NEVER FORGET TO TRANSLATE AND
	* DISPATCH MESSAGE
	*/
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



}

LRESULT CALLBACK login(HWND lwnd, UINT lMsg, WPARAM lParam, LPARAM lParamL) {

	
	

	switch (lMsg) {

		PAINTSTRUCT w;
		HDC loginMessage;
		RECT lm;



	case WM_CREATE: {
		static HWND userName;
		static HWND password;
		HINSTANCE inst2 = ((LPCREATESTRUCT)lParamL)->hInstance;
	
		userName = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 40, 200, 20, lwnd, 0, inst2, 0);
		password = CreateWindow(L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 88, 70, 200, 20, lwnd, 0, inst2, 0);
		CreateWindowEx(0, L"button", L"Login", WS_CHILD | WS_VISIBLE, 88, 100, 100, 40, lwnd, (HMENU)LOGIN, inst2, 0);
		CreateWindowEx(0, L"button", L"Register", WS_CHILD | WS_VISIBLE, 190, 100, 100, 40, lwnd, (HMENU)REGISTER, inst2, 0);
		wchar_t user[] = L"Username";
		wchar_t pass[] = L"Password";
		Edit_SetCueBannerText(userName, user);
		Edit_SetCueBannerText(password, pass);
		break;
	}

	case WM_COMMAND: {
		if (LOWORD(lParam) == LOGIN) {
			DestroyWindow(lwnd);
			showMainScreen();
			break;
		}
	}


	case WM_PAINT:
		loginMessage = BeginPaint(lwnd, &w);
		SetTextColor(loginMessage, RGB(0, 0, 0));
		SetBkMode(loginMessage, TRANSPARENT);
		GetClientRect(lwnd, &lm);
		DrawText(loginMessage, L"Please Enter Your Username and Password", -1, &lm, DT_CENTER | DT_WORDBREAK);
		EndPaint(lwnd, &w);
		break;

	case WM_CLOSE:
		DestroyWindow(lwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(lwnd, lMsg, lParam, lParamL);
}

