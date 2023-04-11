#pragma once
#include "User.h"

class Administrator :public User
{

public:
	Administrator(std::string, std::string, std::string, std::string, std::string);
	virtual std::string GetType()const override;
	virtual std::vector<std::string> GetCourses()const;
	virtual Administrator* clone()const;
};