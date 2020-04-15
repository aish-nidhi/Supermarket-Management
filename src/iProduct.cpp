#include <string>
#include <fstream>
#include "Error.h"
#include "Product.h"
#include "FileHelp.h"

//PRODUCT CLASS

string Product::getId()
{
	return Id;
}

string Product::getProductName()
{
	return ProductName;
}

string Product::getPrice()
{
	return Price;
}

string Product::getExp_date()
{
	return Exp_date;
}

string Product::getManufacture_date()
{
	return Manufacture_date;
}

string Product::getStock_available()
{
	return Stock_available;
}
//setters
void Product::setProductName(string inName)
{
	ProductName = inName;
}

void Product::setPrice(string inPrice)
{
	Price = inPrice;
}

void Product::setId(string inId)
{
	Id = inId;
}

void Product::setExp_date(string inExp_date)
{
	Exp_date = inExp_date;
}

void Product::setManufacture_date(string inManufacture_date)
{
	Manufacture_date = inManufacture_date;
}

void Product::setStock_available(string inStock_available)
{
	Stock_available = inStock_available;
}

ostream& operator<<(ostream &out, Product &inProduct) {

	out << "Id: " << inProduct.Id << " Name: " << inProduct.ProductName << endl;
	return out;

}

Product& Product::setListValue(Product& obj, string str, int  i)
{
	//Product obj;
	int j = i % 7;
	if (i > 7 && j == 1)
	{
		str = str.substr(1, str.length() - 1);
	}
	
	if (j == 1)
	{
		obj.setId(str);
	}
	else if (j == 6)
	{
		obj.category.setCategoryId(str);
	}
	else if (j == 0)
	{
		obj.setStock_available(str);
		
	}
	else if (j == 2)
	{
		obj.setProductName(str);
	}
	else if (j == 3)
	{
		obj.setPrice(str);
	}
	else if (j == 4)
	{
		obj.setExp_date(str);
	}
	else if (j == 5)
	{
		obj.setManufacture_date(str);
	}
	return obj;
}


bool Product::operator==(const Product inProduct)
{
	return Id == inProduct.Id;
}