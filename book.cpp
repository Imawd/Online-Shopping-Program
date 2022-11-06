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
	std::set<std::string> temp1 = parseStringToWords(name_);
	std::set<std::string> temp2 = parseStringToWords(author_);
	std::set<std::string> keyword = setUnion(temp1, temp2); //after parsing relevant attributes to words, combine the sets of words
	keyword.insert(isbn_); //no need to parse

	return keyword;
}

std::string Book::displayString() const {
	return (name_ + "\nAuthor: " + author_ + " ISBN: "+ isbn_ + "\n"+ std::to_string(price_) + " " + std::to_string(qty_) + " left.");	
}

void Book::dump(std::ostream& os) const{
	Product::dump(os);
	os << isbn_ << "\n" << author_ << "\n";
}