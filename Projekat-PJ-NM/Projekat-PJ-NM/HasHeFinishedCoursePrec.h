#pragma once
#include "Precondition.h"
class HasHeFinishedCoursePrec : public Precondition
{
private:
	std::string FCourse;
public:
	HasHeFinishedCoursePrec(std::string);
	std::string GetCourse()const;
	void SetCourse(std::string);
	virtual bool CoursePrecondition(Student*)const;
	virtual std::string GetType()const;
	virtual std::string getDescription()const;
};