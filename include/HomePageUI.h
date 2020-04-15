#pragma once

#include "UserSession.h"

class UserInterface {

private:

	Session *sessn;

public:

	UserInterface() {}
	void displayUI();
	~UserInterface() {}

};