#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() : DataStore() {

}

MyDataStore::~MyDataStore() {
	cart.clear();
	products.clear();
	users.clear();
	keywordMap.clear();

}

void MyDataStore::addProduct(Product* p) {
	if (std::find(products.begin(), products.end(), p) == products.end()) {
		products.push_back(p); //add product to datastore vector
		std::set<std::string> keywords = p->keywords();
		for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
				keywordMap[*it].insert(p); //map products to keyword to make search easier
		}
	}
}

void MyDataStore::addUser(User* u) {
	users.push_back(u);
	cart[u];
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	
	std::set<Product*> results; //make a set to hold results
	std::set<Product*> termSet; //make a set to find the set of products that share terms
	std::vector<Product*> end_results; //output variable in vector form


	if (type == 1)
	{
		for (unsigned int i = 0; i < terms.size(); i++) {
				termSet = keywordMap[terms[i]]; //products with a certain keyword
				results = setUnion(results, termSet); //returns set if either of the terms match keywords
		}
		for (std::set<Product*>::iterator it = results.begin(); it != results.end(); ++it) {
    			end_results.push_back(*it);
  		}	 
	}

	else if (type == 0)
	{
		if (keywordMap.find(terms[0]) != keywordMap.end()) { //fill results for the first term to check against the next term
			results = keywordMap.find(terms[0])->second;
		}
		for (unsigned int i = 1; i < terms.size(); i++) {
				termSet = keywordMap[terms[i]]; //products with a certain keyword
				results = setIntersection(results, termSet); //returns the set of products that matches both sets
		}
		for (std::set<Product*>::iterator it = results.begin(); it != results.end(); ++it) {
			end_results.push_back(*it);
		}	 
		 
	}

	return end_results;
}

void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << std::endl; //formatting for db file
	for (unsigned int i = 0; i < products.size(); i++) {
    products[i]->dump(ofile); //calls previous function that we wrote to dump to the database
  }
	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;
  for (unsigned int i = 0; i < users.size(); i++) {
    users[i]->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}

void MyDataStore::addProductToCart(std::string username, int hit_no, std::vector<Product*> hits) {
	//find user with given username first

	User* current_user = getUser(username);

	if (!isValid(username)) {
		std::cout << "Invalid Request" << std::endl;
		return;
	}

	else if (hit_no-1 >= (signed)hits.size()) {
		std::cout << "Invalid Request" << std::endl;
		return;
	}

	else {
		cart[current_user].push_back(hits[hit_no-1]);
		std::cout << "Product added: " << hits[hit_no-1]->getName() << " to " << current_user->getName() << "'s cart\n";
	}

}

//checks if user exists
bool MyDataStore::isValid(std::string username) {
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if (convToLower((*it)->getName()) == convToLower(username)) {
			return true;
		}
	}
	return false;
}

//gets users cart in the form of a vector
std::vector<Product*> MyDataStore::getCart(std::string username) {
	std::vector<Product*> results;
	User* current_user = getUser(username);

	return cart[current_user];
}

//gets user from username
User* MyDataStore::getUser(std::string username) {

	//check each user for matching username
	for (std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if (convToLower((*it)->getName()) == convToLower(username)) {
			return (*it);
		}
	}

	return NULL;
}
//iterate through cart and deduct price of each product from user's balance
void MyDataStore::buyCart(std::string username) {
	if (!isValid(username)){
		std::cout << "Invalid username" << std::endl;
		return;
	}
	User* current_user = getUser(username);
	std::vector<Product*> cart_ = getCart(username);
	std::cout << "Buying cart, user balance: " << current_user->getBalance() << std::endl;
	for (std::vector<Product*>::iterator it = cart_.begin(); it != cart_.end(); ++it) {
		Product* current_product = (*it); //for readability
		double product_price = current_product->getPrice();
		double user_bal = current_user->getBalance();
		double product_qty = current_product->getQty();

		if (product_qty > 0 && (user_bal >= product_price)) { //check if item quantity is sufficient and that user has enough balance
			current_user->deductAmount(product_price);
			current_product->subtractQty(1);
			cart[current_user].erase(cart[current_user].begin());
		}

		else {
			std::cout << "Could not afford OR item is out of stock: " << current_product->getName() << "  skipping." << std::endl;
			cart[current_user].push_back(current_product);
			cart[current_user].erase(cart[current_user].begin());
		}
	}
	std::cout << "Bought cart, new user balance: " << current_user->getBalance() << std::endl;
}

