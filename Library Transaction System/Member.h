#ifndef MEMBER_H
#define MEMBER_H
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

	const wchar_t* getMemberInfo()  {

		wstring info =  L"Member Name: " + name + L"\n" +
			L"Member Address: " + address + L"\n" +
			L"Member ID: " + to_wstring(memberId) +  L"\n";

		return info.c_str();
	}

	void setName(wstring n) {
		name = n;
	}

	const wstring getName() const {

		return name.c_str();
	}

	int getMemberId() const {

		return memberId;
	}

	const wstring getAddress() const {
		return address.c_str();
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
			wcout << borrowedBooks.at(i).getTitle();
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