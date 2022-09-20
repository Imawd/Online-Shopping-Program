#include <iomanip>
#include <sstream>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn) : Product ("book", name, price, qty)
{
	author_ = author;
	isbn_ = isbn;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const {
	std::set<std::string> keyword = parseStringToWords(name_);
	std::set<std::string> temp = parseStringToWords(author_);
	keyword = setUnion(keyword, temp);
	temp = parseStringToWords(isbn_);

	keyword = setUnion(keyword, temp);
	return keyword;
}

std::string Book::displayString() const {
	return ("Name: " + name_ + "\n Author: " + author_ + "\n ISBN: "+ isbn_ + "\n Price: " + std::to_string(price_) + "\n Quantity: " + std::to_string(qty_));	
}

void Book::dump(std::ostream& os) const{
	Product::dump(os);
	os << author_ << "\n" << isbn_ << "\n";
}