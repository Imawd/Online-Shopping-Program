#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {
public:
	MyDataStore();
	~MyDataStore();

	void addProduct(Product* p);
  void addUser(User* u);;

	void buyCart(std::string username);
	void addProductToCart(std::string username, int hit_no, std::vector<Product*> hits);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  void dump(std::ostream& ofile);

	bool isValid(std::string username);
	User* getUser(std::string username);

	std::vector<Product*> getCart(std::string username);

	std::vector<Product*> getProducts();


protected:
	//product storage vector
	std::vector<Product*> products;
	//user storage vector
	std::vector<User*> users;
	std::map<User*, std::vector<Product*>> cart;
	std::map<std::string, std::set<Product*>> keywordMap;

};
#endif