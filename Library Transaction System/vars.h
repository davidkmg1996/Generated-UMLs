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


private:
	wstring currentuser;

};