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

	void setError(bool oError) {
		oError = true;
		error = oError;

	}

	bool getError() {

		return error;
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

	void setFilePathInfo(bool fPathInfo) {
		fPathInfo = true;
		filePathInfo = fPathInfo;

	}

	bool getFilePathInfo() {

		return filePathInfo;
	}

private:
	wstring currentuser;
	wstring fPath;
	bool catalog;
	bool error;
	bool filePathInfo;

};