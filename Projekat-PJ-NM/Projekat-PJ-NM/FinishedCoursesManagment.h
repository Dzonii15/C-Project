#pragma once
#include <fstream>
#include "UserDirectoryManagment.h"
#include "CourseUserManagment.h"
class FinishedCoursesManagment
{
private:
	std::string person;
public:

	FinishedCoursesManagment();
	FinishedCoursesManagment(std::string);
	std::string GetPerson()const;
	void SetPerson(std::string);
	void WriteFinishedCourse(std::string, int);
	std::vector<std::pair<std::string, int>> ReadAllFinishedCourses();
};