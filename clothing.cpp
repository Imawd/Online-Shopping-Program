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
	std::set<std::string> keyword = parseStringToWords(name_);
	std::set<std::string> temp = parseStringToWords(brand_);
	keyword = setUnion(keyword, temp);

	return keyword;
}

std::string Clothing::displayString() const {
	return ("Name: " + name_ + "\n Brand: " + brand_ + "\n Size: "+ size_ + "\n Price: " + std::to_string(price_) + "\n Quantity: " + std::to_string(qty_));	
}

void Clothing::dump(std::ostream& os) const{
	Product::dump(os);
	os << brand_ << "\n" << size_ << "\n";
}
