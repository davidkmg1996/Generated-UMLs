#ifndef MEMBER_H
#define MEMBER_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "Book.h"
#include "Transaction.h"

using namespace std;

class Member {

	friend class Library;

public:


	Member(wstring name, wstring address, int memberId, vector<Book> borrowedBooks) : name{ name }, 
		address{ address }, borrowedBooks{ borrowedBooks } {

		this->memberId = generateId();
		memberId = this->memberId;
	
	}

	Member() {

	}

	const wstring getMemberInfo()  {

		return L"Member Name: " + name + L"\n" +
			L"Member Address: " + address + L"\n" +
			L"Member ID: " + std::to_wstring(memberId) + L"\n";
	}

	wstring getName() const {

		return name;
	}

	int getMemberId() const {
		return memberId;
	}

	wstring getAddress() const {
		return address;
	}

	void borrowBook(Book aBook) {
		borrowedBooks.push_back(aBook);
		aBook.setAvailability(false);
		Transaction nTrans(aBook.getType(), aBook);
		nTrans.transactionReceipt(aBook);
	}


	void returnBook(Book rBook) {
		borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), rBook));
		rBook.setAvailability(true);
	}

	void getBorrowedBooks() {

		for (int i = 0; i < borrowedBooks.size(); i++) {
			cout << borrowedBooks.at(i).getTitle();
		}
	}

	int generateId(){

		srand(time(NULL));
		int id = rand();
		return id;

	}

	/*
	* Overloaded equality operator needed to prevent compile-time
	* binary equality error
	*/
	bool operator==(const Member& other) const {
		return (name == other.name) && (memberId == other.memberId) && (borrowedBooks == other.borrowedBooks);
	}

private:
	/*
	* Cannot use unary address of operator and const explicitly
	* deletes function, causes compile-time error
	*/
	wstring name;
	wstring address;
	int memberId;
	vector<Book> borrowedBooks;

};

#endif