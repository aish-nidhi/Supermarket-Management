#include <string>
#include <iostream>
#include <algorithm>
#include "Product.h"
#include "Employee.h"
#include "AdminSession.h"
#include "Error.h"
#include "FileHelp.h"
#include "Category.h"
#include <list>

using namespace std;

int AdminSession::convertStringToInt(string str)
{
	int stock = 0,i;
	for ( i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case '1': stock = (stock * 10) + 1;
			break;
		case '2': stock = (stock * 10) + 2;
			break;
		case '3':stock = (stock * 10) + 3;
			break;
		case '4': stock = (stock * 10) + 4;
			break;
		case '5': stock = (stock * 10) + 5;
			break;
		case '6': stock = (stock * 10) + 6;
			break;
		case '7': stock = (stock * 10) + 7;
			break;
		case '8': stock = (stock * 10) + 8;
			break;
		case '9': stock = (stock * 10) + 9;
			break;
		case '0': stock = (stock * 10) + 0;
			break;
		default:"Invalid stock entry!";
		}
	}
	return stock;
}
string AdminSession::convertIntToString(int stock)
{
	int rem;
	string avlStock;
	for (int i = stock; stock > 0; i++)
	{
		rem = stock % 10;
		switch (rem)
		{
		case 1: avlStock = "1" + avlStock;
			break;
		case 2: avlStock = "2" + avlStock;
			break;
		case 3:avlStock = "3" + avlStock;
			break;
		case 4: avlStock = "4" + avlStock;
			break;
		case 5: avlStock = "5" + avlStock;
			break;
		case 6: avlStock = "6" + avlStock;
			break;
		case 7: avlStock = "7" + avlStock;
			break;
		case 8: avlStock = "8" + avlStock;
			break;
		case 9: avlStock = "9" + avlStock;
			break;
		case 0: avlStock = "0" + avlStock;
			break;
		default:"Invalid stock entry!";
		}
		stock /= 10;
	}
	return avlStock;
}

Admin& AdminSession::setAdminValue(Admin& adm)
{
	list<Admin> li = getlist();
	list<Admin>::iterator itr;
	int flag = 0;
	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (itr->getId() == adm.getId())
		{
			adm.setAdminName(itr->getAdminName());
			adm.setPassword(itr->getPassword());
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "User ID not found.";
	}
	return adm;
}

Employee& AdminSession::setEmpValue(Employee& emp)
{
	list<Employee> li = getEmplist();
	list<Employee>::iterator itr;
	int flag = 0;
	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (itr->getId() == emp.getId())
		{
			emp.setEmployeeName(itr->getEmployeeName());
			emp.setPassword(itr->getPassword());
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "User ID not found.";
	}
	return emp;
}

Product& AdminSession::setProdValue(Product& prod)
{
	list<Product> li = getProdlist();
	list<Product>::iterator itr;
	int flag = 0;
	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (itr->getId() == prod.getId())
		{
			prod.setProductName(itr->getProductName());
			prod.setPrice(itr->getPrice());
			prod.setExp_date(itr->getExp_date());
			prod.setManufacture_date(itr->getManufacture_date());
			prod.setStock_available(itr->getStock_available());
			flag = 1;
			break;
		}
		// return prod;
	}
	if (flag == 0)
	{
		cout << "Product ID not found.";
	}
	return prod;

}

void AdminSession::putAdminInFile(Admin adm)
{
	ofstream outfile("admin.txt", ios::app);
	outfile << adm.getId() << "!" << adm.getAdminName() << "!" << adm.getPassword() << "!" << "\n";
	outfile.close();
}

void AdminSession::putEmpInFile(Employee emp)
{
	ofstream outfile("employee.txt", ios::app);
	outfile << emp.getId() << "!" << emp.getEmployeeName() << "!" << emp.getPassword() << "!"<<"\n";
	outfile.close();
}

void AdminSession::putProdInFile(Product prod)
{
	ofstream outfile("product.txt", ios::app);
	outfile << prod.getId() << "!" << prod.getProductName() << "!" << prod.getPrice() << "!" << prod.getExp_date() << "!" << prod.getManufacture_date() << "!" << prod.category.getCategoryId() << "!" << prod.getStock_available() << "!" << "\n";
	outfile.close();
}

list<Admin> AdminSession::getlist()
{
	list<Admin> li;
	string line = "";
	Admin obj;
	int i = 1;
	ifstream file("admin.txt");
	if (file.is_open())
	{
		while (getline(file, line, '!'))
		{
			obj.setListValue(obj, line, i);
			if (i % 3 == 0)
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


list<Employee> AdminSession::getEmplist()
{
	list<Employee> li;
	string line = "";
	Employee obj;
	int i = 1;
	ifstream file("employee.txt");
	if (file.is_open())
	{
		while (getline(file, line, '!'))
		{
			obj.setListValue(obj, line, i);
			if (i % 3 == 0)
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

list<Product> AdminSession::getProdlist()
{
	list<Product> li;
	string line = "";
	Product obj;
	int i = 1;
	ifstream file("product.txt");
	if (file.is_open())
	{
		while (getline(file, line, '!'))
		{
			obj.setListValue(obj, line, i);
			if (i % 7 == 0)
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
bool AdminSession::Login() {

	try
	{
		list<Admin> li;
		li = getlist();
		if (li.empty())
		{
			cout << endl << "Admin not set. Contact helpdesk.";
			return 0;
		}
		int flag = 0;
		cout << "\n\tEnter the Id: ";
		string id, corresPass;
		cin >> id;
		admin.setId(id);
		list<Admin>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (itr->getId() == id)
			{
				admin.setAdminName(itr->getAdminName());
				corresPass = itr->getPassword();
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			cout << "Incorrect ID.";
			return 0;
		}
		cout << "\n\tEnter the password: ";
		string pass;
		cin >> pass;
		admin.setPassword(pass);

		if (pass != corresPass)
		{
			cout << endl << "Incorrect Password";
			return 0;
		}
		else
		{
			return 1;
		}
		return 0;
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}

//this function object is used to find the employee in the admin transaction.

class searchEmployeeById {

public:
	bool operator()(Employee e1, Employee e2)
	{

		return e1.getId() < e2.getId();
	}
};

bool AdminSession::checkEmployee(Employee inEmployee)
{

	list<Employee> li = getEmplist();
	try
	{
		li.sort(searchEmployeeById());
		return (binary_search(li.begin(), li.end(), inEmployee, searchEmployeeById()));
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}
//this function object is used to find the employee in the admin session.
class searchAdminById {

public:
	bool operator()(Admin a1, Admin a2)
	{
		return a1.getId() < a2.getId();
	}
};

bool AdminSession::checkAdmin(Admin inAdmin)
{

	list<Admin> li = getlist();
	try
	{

		li.sort(searchAdminById());
		return (binary_search(li.begin(), li.end(), inAdmin, searchAdminById()));
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}

class searchProductById {

public:
	bool operator()(Product p1, Product p2)
	{

		return p1.getId() < p2.getId();
	}
};

bool AdminSession::checkProduct(Product inProduct)
{

	list<Product> li = getProdlist();
	try
	{

		li.sort(searchProductById());
		return (binary_search(li.begin(), li.end(), inProduct, searchProductById()));
	}
	catch (Error inErr)
	{
		throw inErr;
	}

}

void AdminSession::addAdmin(Admin inAdmin)
{
	list<Admin> li = getlist();
	try
	{

		li.push_back(inAdmin);
		putAdminInFile(inAdmin);
		cout << "\n\tAdmin added successfully.";
	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::removeAdmin(Admin inAdmin)
{
	list<Admin> li = getlist();
	if (inAdmin.getId() == admin.getId())
	{
		cout << "Self Deletion not allowed.";
		return;
	}
	try
	{
		ifstream fin;
		fin.open("admin.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		string toDelLine = inAdmin.getId() + "!" + inAdmin.getAdminName() + "!" + inAdmin.getPassword() + "!";
		while (getline(fin, line))
		{
			cout << line << endl;
			if (line != toDelLine)
			{
				temp << line << endl;
			}
		}
		li.remove(inAdmin);
		temp.close();
		fin.close();
		remove("admin.txt");
		rename("temp.txt", "admin.txt");
		cout << endl << "Deletion Successful";
	}

	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::addEmployee(Employee inEmployee)
{
	list<Employee> li = getEmplist();
	try
	{
		li.push_back(inEmployee);
		putEmpInFile(inEmployee);
		cout << "\n\tEmployee added successfully.";
	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::removeEmployee(Employee inEmployee)
{
	list<Employee> li = getEmplist();
	try
	{
		ifstream fin;
		fin.open("employee.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		string toDelLine = inEmployee.getId() + "!" + inEmployee.getEmployeeName() + "!" + inEmployee.getPassword() + "!";
		cout << endl << toDelLine << endl;
		while (getline(fin, line))
		{
			if (line != toDelLine)
			{
				temp << line << endl;
			}
		}
		li.remove(inEmployee);
		temp.close();
		fin.close();
		remove("employee.txt");
		rename("temp.txt", "employee.txt");
		cout << endl << "Deletion Successful";
	}

	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::addProduct(Product inProduct)
{
	list<Product> li = getProdlist();
	try
	{
		li.push_back(inProduct);
		putProdInFile(inProduct);
		cout << "\n\tProduct added successfully.";
	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::removeProduct(Product inProduct)
{
	list<Product> li = getProdlist();
	try
	{
		ifstream fin;
		fin.open("product.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		string toDelLine = inProduct.getId() + "!" + inProduct.getProductName() + "!" + inProduct.getPrice() + "!" + inProduct.getExp_date() + "!" + inProduct.getManufacture_date() +"!" + inProduct.category.getCategoryId() + "!" + inProduct.getStock_available() + "!";
		while (getline(fin, line))
		{
			if (line != toDelLine)
			{
				temp << line << endl;
			}
		}
		li.remove(inProduct);
		temp.close();
		fin.close();
		remove("product.txt");
		rename("temp.txt", "product.txt");
		cout << endl << "Deletion Successful";
	}

	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::updateStock(Product inprod, int inStock) {

	try
	{
		list<Product> li = getProdlist();
		string prevStock,avlStock;
		list<Product>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (inprod.getId() == itr->getId())
			{
				inprod.category.setCategoryId(itr->category.getCategoryId());
				int stock = 0;
				prevStock = itr->getStock_available();
				avlStock = prevStock;
				stock = convertStringToInt(avlStock);
				stock += inStock;
				avlStock = convertIntToString(stock);
				inprod.setStock_available(avlStock);
			}
		}
		ifstream fin;
		fin.open("product.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line, prevLine;
		while (getline(fin, line, '!'))
		{
			if (line == prevStock && prevLine==inprod.category.getCategoryId())
			{
				line = avlStock;
			}
			if (line == "\n")
			{
				temp << line;
			}
			else
				temp << line << '!';
			prevLine = line;
		}
		temp.close();
		fin.close();
		remove("product.txt");
		rename("temp.txt", "product.txt");
	}
	catch (Error inErr)
	{
		inErr.display();
	}

}

void AdminSession::changePasswd(string inPass1) {

	try
	{
		list<Admin> li = getlist();

		list<Admin>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (admin.getId() == itr->getId() && admin.getPassword() == itr->getPassword())
			{
				itr->setPassword(inPass1);
				break;
			}
		}
		ifstream fin;
		fin.open("admin.txt");
		ofstream temp;
		temp.open("temp.txt");
		string line;
		string toUpdateLine = admin.getPassword();
		while (getline(fin, line, '!'))
		{
			if (line == toUpdateLine)
			{
				line = inPass1;
			}
			if (line == "\n")
			{
				temp << line;
			}
			else
				temp << line << '!';
		}
		temp.close();
		fin.close();
		remove("admin.txt");
		rename("temp.txt", "admin.txt");
	}
	catch (Error inErr)
	{
		inErr.display();
	}


}

void AdminSession::displayMenu()
{
	char choice;
	Admin adm;
	Employee emp;
	Product prod;
	string id;
	system("COLOR 1F");
	do {
		system("cls");
		cout << "\n\t" << __DATE__;
		cout << "\n\t\t\tWELCOME " << admin.getAdminName() << ".\n";
		cout << "\n\t\t\tEnter the choice to enter into                     \n\n";
		cout << "\t\t\tEmployee Related Options\n\n";
		cout << "\t\t\t  1.Add Employee\n";
		cout << "\t\t\t  2.Remove Employee\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tAdmin Related Options\n\n";
		cout << "\t\t\t  3.Add Admin\n";
		cout << "\t\t\t  4.Remove Admin\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tProduct Related Options\n\n";
		cout << "\t\t\t  5.Add Product\n";
		cout << "\t\t\t  6.Remove Product\n";
		cout << "\t\t\t  7.Update Stocks\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tPersonal Details Change\n\n";
		cout << "\t\t\t  8.Change your Password\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\t  9. LOGOUT\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\n\t\tEnter your choice----> ";
		cin >> choice;


		switch (choice) {

		case '1':
			try
			{
				cout << "\n\tEnter the Employee id: ";
				cin >> id;
				if (id.length() == 6)
				{
					for (int i = 0; i < id.length(); i++)
					{
						if (!(id[i] >= '0' && id[i] <= '9'))
						{
							cout << endl << "\tInvalid employee Id. No characters allowed.";
							return;
						}
					}
				}
				if (id.length() != 6)
				{
					cout << endl << "\tEmployee Id must be of 6 digits.";
					return;
				}
				emp.setEmployeeId(id);

				if (!checkEmployee(emp))
				{
					cout << "\n\tEnter the Employee Name: ";
					string name;
					cin.ignore();
					getline(cin, name);
					if(!(emp.setEmployeeName(name)))
						return;
					cout << "\n\tEnter the Employee Password: ";
					int flag=1;
					string pass;
					cin >> pass;
					for (int x = 0; x < pass.length(); x++)
					{
						if (pass[x] == '!' || pass[x] == ' ')
						{
							cout << "Invalid password.";
							flag = 0;
						}
					}
					if (flag != 0)
					{
						emp.setPassword(pass);
					}
					else
					{
						return;
					}
					addEmployee(emp);
					cout << "\n-->Registration Successful.<--";
				}
				else
				{
					cout << "\n\tEntered Id already Exists.";
				}

			}
			catch (Error inErr)
			{
				inErr.display();
			}
			break;

		case '2':
			try
			{
				cout << "\n\tEnter the Employee id: ";
				cin >> id;
				if (id.length() == 6)
				{
					for (int i = 0; i < id.length(); i++)
					{
						if (!(id[i] >= '0' && id[i] <= '9'))
						{
							cout << endl << "\tInvalid employee Id. No characters allowed.";
							return;
						}
					}
				}
				if (id.length() != 6)
				{
					cout << endl << "\tEmployee Id must be of 6 digits.";
					return;
				}
				emp.setEmployeeId(id);

				if (checkEmployee(emp))
				{
					setEmpValue(emp);
					removeEmployee(emp);
				}
				else
				{
					cout << "\n\tEntered Id does not exist. Employee cannot be removed";
				}

			}
			catch (Error inErr)
			{
				inErr.display();
			}
			break;


		case '3':
			try
			{
				cout << "\n\tEnter the Admin id: ";
				cin >> id;
				if (id.length() == 6)
				{
					for (int i = 0; i < id.length(); i++)
					{
						if (!(id[i] >= '0' && id[i] <= '9'))
						{
							cout << endl << "\tInvalid employee Id. No characters allowed.";
							return;
						}
					}
				}
				if (id.length() != 6)
				{
					cout << endl << "\tEmployee Id must be of 6 digits.";
					return;
				}
				cin.ignore();
				adm.setId(id);

				if (!checkAdmin(adm))
				{
					cout << "\n\tEnter the Admin Name: ";
					string name;
					getline(cin, name);
					adm.setAdminName(name);
					cout << "\n\tEnter the Admin Password: ";

					string pass;
					cin >> pass;
					adm.setPassword(pass);

					addAdmin(adm);
				}
				else
				{
					cout << "\n\tEntered Id already Exists.";
				}

			}
			catch (Error inErr)
			{
				inErr.display();
			}
			break;

		case '4':
			try
			{
				cout << "\n\tEnter the Admin id: ";
				cin >> id;
				adm.setId(id);
				if (id.length() == 6)
				{
					for (int i = 0; i < id.length(); i++)
					{
						if (!(id[i] >= '0' && id[i] <= '9'))
						{
							cout << endl << "\tInvalid employee Id. No characters allowed.";
							return;
						}
					}
				}
				if (id.length() != 6)
				{
					cout << endl << "\tEmployee Id must be of 6 digits.";
					return;
				}
				if (checkAdmin(adm))
				{
					setAdminValue(adm);
					removeAdmin(adm);
				}
				else
				{
					cout << "\n\tEntered Id does not exist. Admin cannot be removed";
				}

			}
			catch (Error inErr)
			{
				inErr.display();
			}
			break;

		case '5':
			try
			{

				cout << "\n\tEnter the Product id: ";
				cin >> id;
				prod.setId(id);

				if (!checkProduct(prod))
				{
					cout << "\n\tEnter the Product Name: ";
					string name;
					cin.ignore();
					getline(cin, name);
					prod.setProductName(name);

					cout << "\n\tEnter the Product Cost : ";
					string price;
					cin >> price;
					prod.setPrice(price);

					cout << "\n\tEnter the Product Expiry Date(dd/mm/yyyy): ";
					string expdate;
					cin >> expdate;
					prod.setExp_date(expdate);

					cout << "\n\tEnter the Product Manufacturing Date(dd/mm/yyyy) : ";
					string mfgdate;
					cin >> mfgdate;
					prod.setManufacture_date(mfgdate);

					cout << "\n\tEnter the Product Available Stock : ";
					string stock;
					cin >> stock;
					prod.setStock_available(stock);

					cout << "\n\tEnter the Product Category Id : ";
					string catId;
					cin >> catId;
					prod.category.setCategoryId(catId);
					if (prod.category.checkCategory(prod.category))
					{
						addProduct(prod);
					}
					else
					{
						char cont;
						cout << "\n\tCategory not found. Do you want to add new category?(Press 1-->Yes or 0->No) :";
						cin >> cont;
						if (cont == '1')
						{
							cout << "\n\tEnter Category Name : ";
							string name;
							cin >> name;
							prod.category.setCategoryName(name);
							prod.category.addCategory(prod.category);
							addProduct(prod);
						}
						else
							cout << "\n\tProduct addition aborted.";
					}
				}
				else
				{
					cout << "\n\tProduct Already Exists. Enter Unique Id";
					break;
				}
			}
			catch (Error inErr)
			{
				inErr.display();
			}
			break;

			//this takes the product id and checks if it is there in file or not.
			//if it is not there is shows error msg and if its there the product will be removed.
		case '6':
			try {

				cout << "\n\tEnter the Product id: ";
				cin >> id;
				prod.setId(id);

				if (checkProduct(prod))
				{
					setProdValue(prod);
					removeProduct(prod);
				}
				else
				{
					cout << "\n\tProduct Does not Exist. Cannot Remove.";
					break;
				}
			}
			catch (Error inErr) {
				inErr.display();
			}
			break;

		case '7':
			try
			{

				cout << "\n\tEnter the Product id: ";
				string id;
				cin >> id;
				prod.setId(id);
				if (checkProduct(prod))
				{
					cout << "\n\tEnter the number of items to increase: ";
					int stockcount;
					cin >> stockcount;
					if (stockcount > 0)
						updateStock(prod, stockcount);
					else
					{
						cout << "\n\tStock should be greater than ZERO.";
						break;
					}
				}
				else
				{
					cout << "\n\tProduct Does not Exists. Cannot Remove.";
					break;
				}

			}
			catch (Error inErr) {
				inErr.display();
			}
			break;

			//TO change the password of the admin.
			//Admin enters the the password to be changed to two times and the password
			//should be alphanumeric.
		case '8':
			try
			{
				cout << "\nEnter current password: ";
				string pswd;
				cin >> pswd;
				if (pswd != admin.getPassword())
				{
					cout << endl << "Incorrect current password, try again.";
					return;
				}
				cout << "\n\tEnter the new Password: ";
				string pass1;
				cin >> pass1;
				cout << "\n\tConfirm Password: ";
				string pass2;
				cin >> pass2;
				if (pass1 == pass2)
				{
					changePasswd(pass1);
					cout << endl << "\tPassword successfully changed.";
				}
				else
					cout << "\n\t-!!Passwords Entered Do not match each other.!!-\n";
			}
			catch (Error inErr) 
			{
				inErr.display();
			}

			break;
		case '9': return;

		default:
			cout << "\n\tInvalid Choice";
			break;
		}

		cout << "\n\n\tDo you want to continue as Admin?\n\tPress 1 to continue. 0. Exit----> ";
		cin >> choice;
		cout << "\n\n";
	
	} while (choice != '0');
	system("cls");
	system("COLOR F0");
}