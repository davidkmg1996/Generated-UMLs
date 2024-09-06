#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>


using namespace std;


class Book {

public:

	friend class Transaction;

	Book(wstring title, wstring author, wstring isbn, bool available, wstring type) : title{ title }, author{ author }, isbn{ isbn }, available{ available }, type{ type } {
	
	}

	const wstring getTitle() const {
		return title.c_str();
	}

	const wstring getType() const {
		return type.c_str();
	}

	const wstring getAuthor() const {
		return author.c_str();
	}

	const wstring getISBN() const {
		return isbn.c_str();
	}

	bool isAvailable() const {


		return available;
	}

	bool setAvailability(bool tF) {

	
		available = false;
		return false;

	}

	
	/*
	* Overloaded equality operator needed to prevent compile - time
	  binary equality error
	*/
		
	bool operator==(const Book& other) const {
		return (title == other.title) && (author == other.author) && (isbn == other.isbn);
	}

private:
	wstring title;
	wstring author;
	wstring isbn;
	wstring type;
	bool available;

};

#endif