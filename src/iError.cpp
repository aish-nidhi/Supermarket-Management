
#include "Error.h"
#include <iostream>

using namespace std;

//ERROR CLASS
void Error::display()
{
	cout << "\n\tError: " << errmsg << " Error Code: " << errcode << endl;
}