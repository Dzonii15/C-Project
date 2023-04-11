#pragma once
#include "User.h"
class Student :public User
{
private:
	//Kursevi koje studnet pohadja
	std::vector<std::string> courses;
public:
	//Konstruktori
	Student(std::string, std::string, std::string, std::string, std::string);

	//Vraca "Student" kao tip
	virtual std::string GetType()const override;
	std::vector<std::string> GetCourses()const;
	virtual Student* clone()const;
	//Ispis kurseva koje student pohadja
	void PrintCourses(std::ostream&)const;
};
