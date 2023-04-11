#pragma once
#include "AccoutManagment.h"

class LogIn
{
public:
	static bool Login(std::ostream&, std::istream&, std::vector <User*>&, User**);
};