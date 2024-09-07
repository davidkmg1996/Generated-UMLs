#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.Syndication.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <commctrl.h>
#include <fstream>
#include <array>
#include "sqlite3.h"
#include "MS.h"
#include "Book.h"
#include "Member.h"
#include "tchar.h"
#include "Transaction.h"
#include "procedures.h"

using namespace std;

/*
* Based off of UML suggestion with
* screenshots provided.
*
* All relevant documentation included
* in MS header file, though none of it is
* revelant so I wouldn't bother being nosey
*/


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	showLoginWindow();

	return 0;
}
