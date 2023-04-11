#include "Student.h"


Student::Student(std::string UserName, std::string Password, std::string Name, std::string Surname, std::string jmbg) :User(UserName, Password, Name, Surname, jmbg)
{
	CourseUserManagment scanner;
	scanner.SetUser(this->GetUserName());
	this->courses = scanner.ReadAllCourses();
}
std::string Student::GetType()const
{
	return "Student";
}
std::vector<std::string> Student::GetCourses()const
{
	return this->courses;
}
void Student::PrintCourses(std::ostream& os)const
{
	os << "Trenutno pohadjate kurseve" << std::endl;
	for (auto element : this->courses)
		os << element << " ";
}
Student* Student::clone()const
{
	return new Student(*this);
}
