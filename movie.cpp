#include <iomanip>
#include <sstream>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product("movie", name, price, qty) 
{
	genre_ = genre;
	rating_ = rating;
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
	std::set<std::string> temp1 = parseStringToWords(name_);
	std::set<std::string> temp2 = parseStringToWords(genre_);
	std::set<std::string> keyword = setUnion(temp1, temp2); //after parsing relevant attributes to words, combine the sets of words
	keyword.insert(rating_); //no need to parse

	return keyword;
}

std::string Movie::displayString() const {
	return (name_ + "\n Genre: " + genre_ + " Rating: "+ rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.");	
}

void Movie::dump(std::ostream& os) const{
	Product::dump(os);
	os << genre_ << "\n" << rating_ << "\n";
}