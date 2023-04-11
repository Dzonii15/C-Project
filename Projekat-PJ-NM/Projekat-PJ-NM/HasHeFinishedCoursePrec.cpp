#include "HasHeFinishedCoursePrec.h"
std::string HasHeFinishedCoursePrec::GetType()const
{
	return "2";
}
bool HasHeFinishedCoursePrec::CoursePrecondition(Student* student)const
{
	std::string finishedC = this->FCourse;
	FinishedCoursesManagment scanner(student->GetUserName());
	std::vector<std::pair<std::string, int>> finishedCourses = scanner.ReadAllFinishedCourses();
	auto it = find_if(finishedCourses.begin(), finishedCourses.end(), [finishedC](const std::pair<std::string, int>& el) {return el.first == finishedC; });
	return it != finishedCourses.end();
}
HasHeFinishedCoursePrec::HasHeFinishedCoursePrec(std::string course) :FCourse(course)
{

}
std::string HasHeFinishedCoursePrec::GetCourse()const
{
	return this->FCourse;
}
void HasHeFinishedCoursePrec::SetCourse(std::string course)
{
	this->FCourse = course;
}
std::string HasHeFinishedCoursePrec::getDescription()const
{
	return "Student se moze prijaviti na kurs samo ako je polozio prethodno definisan kurs \n";
}