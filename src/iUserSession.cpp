#include "UserSession.h"
#include "AdminSession.h"
#include "Error.h"
#include "EmployeeSession.h"
#include "CustomerSession.h"
#include "Error.h"


Session* SessionFactory::createSession(string userType) {

	if (userType == "Admin")
		return new AdminSession;
	else if (userType == "Customer")
		return new CustomerSession;
	else if (userType == "Employee")
		return new EmployeeSession;
	else
	{
		Error err("Invalid Transaction", 1);
		throw err;
	}

}