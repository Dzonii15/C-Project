#include "Administrator.h"

Administrator::Administrator(std::string userName, std::string password, std::string name, std::string surname, std::string jmbg) :User(userName, password, name, surname, jmbg)
{

}
std::string Administrator::GetType()const
{
	return "Administrator";
}
std::vector<std::string> Administrator::GetCourses()const
{
	std::vector<std::string> EmptyVek;
	return EmptyVek;
}
Administrator* Administrator::clone()const
{
	return new Administrator(*this);
}