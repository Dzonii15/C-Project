#include "CourseInteraction.h"


void CourseInteraction::CourseIntersection(const std::set<std::string>& fVec, const std::set<std::string>& sVec, std::set<std::string>& intersection)
{
	std::set_intersection(fVec.begin(), fVec.end(),
		sVec.begin(), sVec.end(),
		std::inserter(intersection, intersection.begin()));

}
void  CourseInteraction::CourseUnion(const std::set<std::string>& fVec, const std::set<std::string>& sVec, std::set<std::string>& sunion)
{
	std::set_union(fVec.begin(), fVec.end(),
		sVec.begin(), sVec.end(),
		std::inserter(sunion, sunion.begin()));

}
void CourseInteraction::CourseDifference(const std::set<std::string>& fVec, const std::set<std::string>& sVec, std::set<std::string>& sdiffrence)
{

	std::set_difference(fVec.begin(), fVec.end(),
		sVec.begin(), sVec.end(),
		std::inserter(sdiffrence, sdiffrence.begin()));
}
void CourseInteraction::ReadStudents(int option, std::string CourseName, std::set<std::string>& List)
{
	CourseDirectoryManagment scanner;
	scanner.CreateCourseDir(CourseName);
	std::string filePath, user;
	if (option == 1)
	{
		filePath = scanner.GetPath() + "StudentList.txt";
		std::ifstream inFile(filePath, std::ios::in);
		if (inFile.is_open())
		{
			while (inFile.good())
			{
				std::getline(inFile, user);
				inFile >> std::ws;
				List.insert(user);
			}
			inFile.close();

		}
	}
	else if (option == 2)
	{
		filePath = scanner.GetPath() + "StudentListFinished.txt";
		std::ifstream inFile(filePath, std::ios::in);
		if (inFile.is_open())
		{
			while (inFile.good())
			{
				std::getline(inFile, user);
				List.insert(user);
			}
			inFile.close();

		}

	}
	else throw std::exception("Something went wrong");
}