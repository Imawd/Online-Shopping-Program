#include <iomanip>
#include <sstream>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product("clothing", name, price, qty)
{
	brand_ = brand;
	size_ = size;
}

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const {
	std::set<std::string> temp1 = parseStringToWords(name_);
	std::set<std::string> temp2 = parseStringToWords(brand_);
	std::set<std::string> keyword = setUnion(temp1, temp2); //after parsing relevant attributes to words, combine the sets of words

	return keyword;
}

std::string Clothing::displayString() const {
	return (name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.");	
}

void Clothing::dump(std::ostream& os) const{
	Product::dump(os);
	os << size_ << "\n" << brand_ << "\n";
}
