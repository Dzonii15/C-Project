#pragma once
#include "HasHeFinishedCoursePrec.h"
#include "NumOfCoursesPrec.h"
#include "CourseDirectoryManagment.h"
class CoursePreconditionManagment
{
private:
	std::string course;

public:
	CoursePreconditionManagment(std::string);
	std::string GetCourse()const;
	void SetCourse(std::string);
	void WriteOnePrecondition(const Precondition*);
	void WritePreconditions(const std::vector<Precondition*>&);
	void ReadCoursePreconditions(std::vector<Precondition*>&);
};