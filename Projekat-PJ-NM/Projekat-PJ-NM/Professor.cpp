#include "Professor.h"

Professor::Professor(std::string UserName, std::string Password, std::string Name, std::string Surname, std::string jmbg) :User(UserName, Password, Name, Surname, jmbg)
{
	CourseUserManagment scanner;
	scanner.SetUser(this->GetUserName());
	this->coursesWhichHeLeads = scanner.ReadAllCourses();
}
std::string Professor::GetType()const
{
	return "Professor";
}
std::vector<std::string> Professor::GetCourses()const
{
	return this->coursesWhichHeLeads;
}
Professor* Professor::clone()const
{
	return new Professor(*this);
}