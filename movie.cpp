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
	std::set<std::string> keyword = parseStringToWords(name_);
	std::set<std::string> temp = parseStringToWords(genre_);
	keyword = setUnion(keyword, temp);

	return keyword;
}

std::string Movie::displayString() const {
	return ("Name: " + name_ + "\n Genre: " + genre_ + "\n Rating: "+ rating_ + "\n Price: " + std::to_string(price_) + "\n Quantity: " + std::to_string(qty_));	
}

void Movie::dump(std::ostream& os) const{
	Product::dump(os);
	os << genre_ << "\n" << rating_ << "\n";
}