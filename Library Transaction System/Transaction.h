#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Book.h"
#include "Member.h"
#include <ctime>

using namespace std;


/*
* This class is dedicated to all of my ex girlfriends
*/
class Transaction {

	friend class Member;

public:
	

	Transaction(string type, Book book) : type{ type }, book{ book }, transactionId{ transactionId } {
}
	
	/*
	* . . . the getBook() function, however,
	* is not
	*/
	Book getBook() const {
		return book;
	}

	string getType() const {
		/*
		* Not to be confused with the return type of
		* this function, which is, of course, std::string,
  		* included in the user-defined class Transaction
    		* accessed via the type member variable 
      		* std::string type returned by the member function
		* getType() const using the statement this->type
		*
  		*obviously
		*/
		return this->type;
	}

	/*
	* I could probably keep going but I'm tired
	* and it's not funny anymore
	*/
	int getTransactionId() {

		transactionId = (rand() % 9999) + 1;

		return transactionId;
	}


	void transactionReceipt(Book aBook) {

		char buffer[30];
		time_t n = time(0);
		ctime_s(buffer, sizeof buffer, &n);
	
		cout << "\n\nTransaction Complete!" << endl;
		cout << "Tranaction ID: " << getTransactionId() << endl;
		cout << "Book title: " << aBook.getTitle() << endl;
		cout << "Author " << aBook.getAuthor() << endl;
		cout << "Book genre: " << aBook.getType() << endl;
		cout << "Transaction Date: " << buffer << endl;


	}

private:
	int transactionId;
	Book book;
	string type;

};
#endif
