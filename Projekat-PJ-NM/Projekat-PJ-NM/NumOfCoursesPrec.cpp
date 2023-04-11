#include "NumOfCoursesPrec.h"

std::string NumOfCoursesPrec::GetType()const
{
	return "1";
}
NumOfCoursesPrec::NumOfCoursesPrec() :numOfCourses(0)
{

}
bool NumOfCoursesPrec::CoursePrecondition(Student* student)const
{
	std::vector<std::string> courses = student->GetCourses();
	if (courses.size() >= this->numOfCourses)
		return true;
	return false;
}
NumOfCoursesPrec::NumOfCoursesPrec(int numofc) :numOfCourses(numofc)
{
}
int NumOfCoursesPrec::getNumOfCourse()const
{
	return this->numOfCourses;
}
void NumOfCoursesPrec::setNumOfCourses(int numofc)
{
	this->numOfCourses = numofc;
}
std::string NumOfCoursesPrec::getDescription()const
{
	return "Uslov je definisan tako da se student moze prijaviti na kurs ako je prijavljen na definisan broj kurseva \n";
}