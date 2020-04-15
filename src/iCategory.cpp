

#include <fstream>
#include <string>
#include <iomanip>
#include "Category.h"
#include "Error.h"
#include <algorithm>

using namespace std;

/********************************************************************************************/
/*Getters & Setters for Category class*/
void Category::setCategoryId(string cId)
{
	catId = cId;
}
void Category::setCategoryName(string cName)
{
	catName = cName;
}
string Category::getCategoryName()
{
	return catName;
}

string Category::getCategoryId()
{
	return catId;
}

void Category::putintoFile(Category catgry)
{
	ofstream outfile("category.txt", ios::app);
	outfile << catgry.getCategoryId() << "!" << catgry.getCategoryName() << "!" << endl;
	outfile.close();
}

void Category::addCategory(Category inCategory)
{
	list<Category> li = getCategoryList();
	try
	{
		li.push_back(inCategory);
		putintoFile(inCategory);
		cout << "\n\tCategory added successfully.";
	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

ostream& operator<<(ostream &out, Category &inCat) {

	out << "Category Id: " << inCat.catId << " Name: " << inCat.catName;
	return out;
}

class searchCategoryById {

public:
	bool operator()(Category c1, Category c2)
	{

		return c1.getCategoryId() < c2.getCategoryId();
	}
};

bool Category::checkCategory(Category inCat)
{
	list<Category> li = getCategoryList();
	try
	{

		li.sort(searchCategoryById());
		return (binary_search(li.begin(), li.end(), inCat, searchCategoryById()));
	}
	catch (Error inErr)
	{
		throw inErr;
	}
}

Category& Category::setListValue(Category& obj, string str, int  i)
{
	//Category obj;
	int j = i % 2;
	if (i > 2 && j == 1)
	{
		str = str.substr(1, str.length() - 1);
	}

	if (j == 1)
	{
		obj.setCategoryId(str);
	}
	else if (j == 0)
	{
		obj.setCategoryName(str);

	}
	return obj;
}

list<Category> Category::getCategoryList()
{
	list<Category> li;
	string line = "";
	Category obj;
	int i = 1;
	ifstream file("category.txt");
	if (file.is_open())
	{
		while (getline(file, line, '!'))
		{
			obj.setListValue(obj, line, i);
			if (i % 2 == 0)
			{
				li.push_back(obj);
			}

			i++;
		}
	}
	else
		cout << "Unable to open the file\n";
	file.close();

	return li;
}

bool Category::viewCategories()
{
	list<Category> li = getCategoryList();
	if (li.empty())
	{
		cout << "\nNo Products available. We regret the inconvinience.\n";
		return 0;
	}
	list<Category>::iterator itr;
	int i = 1;
	cout << "\n\t    Category ID"<<setw(20)<<"Category Name";
	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (itr == li.begin())
			itr++;
		cout << "\n\t" << i << "-->" << itr->getCategoryId() << setw(itr->getCategoryId().length()) << itr->getCategoryName();
		i++;
	}
}

ofstream& operator<<(ofstream &fout, Category &inCat) {

	fout << "\n" << inCat.catId << " " << inCat.catName;
	return fout;

}
ifstream& operator>>(ifstream &fin, Category &inCat) {

	fin >> inCat.catId >> inCat.catName;
	return fin;

}