#pragma once
#include <iostream>
#include <string>

using namespace std;


class varsH {


public:
	void setUsername(wstring user) {

		currentuser = user;
	}

	wstring getUsername() {

		return currentuser;
	}

	void setFilePath(wstring path) {

		fPath = path;
	}

	wstring getFilePath() {

		return fPath;
	}

	void setTrue(bool oCatalog) {
		oCatalog = true;
		catalog = oCatalog;

	}

	void setFalse(bool fCatalog) {
		fCatalog = false;
		catalog = fCatalog;
	}

	bool getBool() {

		return catalog;
	}

private:
	wstring currentuser;
	wstring fPath;
	bool catalog;

};