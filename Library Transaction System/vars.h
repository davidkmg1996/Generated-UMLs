#pragma once
#include <iostream>
#include <string>

using namespace std;


class varsH {

public:
	wstring currentuser;

	void setUsername(wstring user) {

		currentuser = user;
	}

	wstring getUsername() {

		return currentuser;
	}
};