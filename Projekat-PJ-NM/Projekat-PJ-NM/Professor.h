#pragma once
#include "User.h"
#include <functional>

class Professor :public User
{
private:
	//Kursevi koje vodi
	std::vector<std::string> coursesWhichHeLeads;
public:
	Professor(std::string, std::string, std::string, std::string, std::string);
	virtual std::string GetType()const override;
	std::vector<std::string> GetCourses()const;
	Professor* clone()const;
};