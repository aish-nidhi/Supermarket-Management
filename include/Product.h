#pragma once

#include <string>
#include <fstream>
#include "Category.h"

using namespace std;

class Product {

private:
	string Id;
	string ProductName;
	string Price;
	string Exp_date;
	string Manufacture_date;
	string Stock_available;


public:
	Product() {}
	Category category;
	Product(string inId, string inName, string inPrice, string inExp_date, string inManufacture_date, string inStock_available) : Id(inId), ProductName(inName), Price(inPrice), Exp_date(inExp_date), Manufacture_date(inManufacture_date), Stock_available(inStock_available) {}
	string getId();
	string getProductName();
	string getPrice();
	string getExp_date();
	string getManufacture_date();
	string getStock_available();
	void setProductName(string inName);
	void setId(string);
	void setPrice(string);
	void setExp_date(string);
	void setManufacture_date(string);
	void setStock_available(string);
	Product& setListValue(Product&, string, int);
	friend ostream& operator<<(ostream&, Product&);
	friend ofstream& operator<<(ofstream&, Product&);
	friend ifstream& operator>>(ifstream&, Product&);
	bool operator==(const Product);
	string getType()
	{
		return "Product";
	}
};