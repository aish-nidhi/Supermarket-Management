#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <list>
using namespace std;


class Category		//Category class
{
public:				//Public members of class category
	Category() {}
	string getCategoryName();
	bool viewCategories();
	void putintoFile(Category);
	void addCategory(Category);
	bool checkCategory(Category cat);
	list<Category> getCategoryList();
	Category& setListValue(Category&, string, int);
	string getCategoryId();
	void setCategoryId(string);
	void setCategoryName(string);
	friend ostream& operator<<(ostream &, Category &);
	friend ofstream& operator<<(ofstream &, Category &);
	friend ifstream& operator>>(ifstream &, Category &);

private:			//Private members of class category
	string catId;
	string catName;
};