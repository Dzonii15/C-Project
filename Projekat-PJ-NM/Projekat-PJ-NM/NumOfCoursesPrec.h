#pragma once
#include "Precondition.h"

class NumOfCoursesPrec :public Precondition
{
private:
	int numOfCourses;
public:
	NumOfCoursesPrec();
	NumOfCoursesPrec(int);
	int getNumOfCourse()const;
	void setNumOfCourses(int);
	virtual bool CoursePrecondition(Student*)const;
	virtual std::string GetType()const;
	virtual std::string getDescription()const;
};