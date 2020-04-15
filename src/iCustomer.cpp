

#include <fstream>
#include <string>
#include "Customer.h"
#include "Error.h"
#include <string.h>
#include "FileHelp.h"

//CUSTOMER

/*function definition for Customer Class*/

Customer& Customer::setListValue(Customer& obj, string str, int  i)
{
	//Admin obj;
	int j = i % 4;
	if (i > 4 && j == 1)
	{
		str = str.substr(1, str.length() - 1);
	}
	if (j == 1)
	{
		obj.setCustPhNum(str);
	}
	else if (j == 3)
	{
		obj.setPassword(str);
	}
	else if (j == 2)
	{
		obj.setCustName(str);
	}
	else if (j == 0)
	{
		obj.setCardPoints(str);
	}
	return obj;
}

//setters

void Customer::setCustPhNum(string PhNo)
{
		CustPhNum = PhNo;
}

void Customer::setCardPoints(string points)
{
	cardPoints = points;
}

void Customer::setPassword(string inPass)
{
	password = inPass;
}

bool Customer::setCustName(string inName)
{
	for (int i = 0; i < inName.length(); i++)
	{
		if (!((inName[i] >= 'A' && inName[i] <= 'Z') || (inName[i] >= 'a' && inName[i] <= 'z') || inName[i] == ' '))
		{
			Error err( "Name can only contain alphabets and space.",-32);
			return 0;
		}
	}
	CustName = inName;
	return 1;
}

//getters

string Customer::getCustPhNum()
{
	return CustPhNum;
}

string Customer::getCustName()
{
	return CustName;
}

string Customer::getCustPass()
{
	return password;
}

string Customer::getCardPoints()
{
	return cardPoints;
}

bool Customer::operator==(const Customer &inCust) {

	return (CustPhNum == inCust.CustPhNum);

}

/*ostream& operator<<(ostream& out2, Customer &cust)
{
	out2 << "\nCustomer PhoneNumer(UserID) :" << cust.CustPhNum;
	//out2 << "\nCustomer Card Number :" << cust.getCardNumber();
	//out2 << "\nCustomer Card Points :" << cust.getCardPoints();
	return out2;
}

//File Handling for Customer

//writting to the Customer file

ofstream& operator<<(ofstream &fout, Customer &OfCust)
{
	fout << "\n" << OfCust.CustPhNum << "!" << OfCust.getCardNumber() << "!" << OfCust.getCardPoints() << "!";
	return fout;
}

//Reading from the Customer file

ifstream& operator>>(ifstream &fin, Customer &IfCust)
{
	string cardnum;
	unsigned cardpoint;
	fin >> IfCust.CustPhNum >> cardnum >> cardpoint;
	/*IfCust.setCardNumber(cardnum);
	IfCust.setCardPoints(cardpoint);
	return fin;
}*/