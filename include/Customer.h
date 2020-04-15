#pragma once

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <string.h>

//#include "CCard.h"
//#include "CBillHistory.h"

using namespace std;


class Customer							//Customer Class
{
public:
	Customer() { }//Custcard = new Card(); }
	Customer(const string);//to do
	Customer& setListValue(Customer&, string, int);
	//setters
	void setCustPhNum(string);
	bool setCustName(string);
	void setCardPoints(string);
	void setPassword(string);
	//getters
	string getCustPhNum();
	string getCardPoints();
	string getCustName();
	string getCustPass();
	friend ostream& operator<<(ostream&, Customer&);
	friend ofstream& operator<<(ofstream&, Customer&);
	friend ifstream& operator>>(ifstream&, Customer&);
	bool operator==(const Customer&);
	~Customer() {
		//if (Custcard) { delete Custcard; Custcard = NULL; }
	}
private:
	string CustPhNum;
	string CustName;
	string password;
	string cardPoints;
	//Card *Custcard;
	//Card Custcard;
	//BillHistory Custbillhistory;
};