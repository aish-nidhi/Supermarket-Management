#pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "Error.h"
//#include "CProduct.h"

using namespace std;

template<class T>
list<T> getList_FromFile(string inFileName) {
	cout<<inFileName;
	ofstream outFile(inFileName, ios::out);
	if (!outFile)
	{
		cout << "Unable to open the file\n";
	}

	list<T> li;
	T obj;
	ifstream file(inFileName);

		while (!file.eof())
		{
			file >> obj;
			cout << obj;
			//getline(file, obj, "!");
			li.push_back(obj);
		}

	file.close();
	return li;

}


//All the classes should be ifstream and ofstream overloaded with a 
//comma separated and newline ended way
/*template<class T>
void putList_InFile(const char *inFileName, list<T> li) {

	if (!inFileName) {
		Error err("File Cannot be Opened", 2);
		throw err;
	}

	list<T>::iterator itr;
	ofstream file(inFileName);
	if (file.is_open())
		file.close();
	file.open(inFileName, std::fstream::binary);

	for (itr = li.begin(); itr != li.end(); itr++)
		file << *itr << "!";


	file.close();

}

//multimap<unsigned long, Product> getCart_FromFile(const char *inFileName);

bool checkName(string x);

/*Function to check value for password*/
bool checkPass(string x);

istream& takePassword(istream &in, string s);

//oid set_stdinEcho(bool enable_echo);

const std::string getDateString();

const std::string getTimeString();