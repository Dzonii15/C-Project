#include "FinishedCoursesManagment.h"
FinishedCoursesManagment::FinishedCoursesManagment() :person("") {}
FinishedCoursesManagment::FinishedCoursesManagment(std::string Person) : person(Person) {}
std::string FinishedCoursesManagment::GetPerson()const
{
	return this->person;
}
void FinishedCoursesManagment::SetPerson(std::string Person)
{
	this->person = Person;
}
void FinishedCoursesManagment::WriteFinishedCourse(std::string course, int grade)
{
	UserDirectoryManagment directory;
	directory.CreateUserDir(this->person);
	CourseUserManagment scanner(this->person, course);
	scanner.DeleteCourseFromUserList();
	std::string filepath = (directory.GetPath() + this->person + "FinishedCourses.txt");
	std::ofstream outFile(filepath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << course << "," << grade << std::endl;
		outFile.close();
	}
}
std::vector<std::pair<std::string, int>> FinishedCoursesManagment::ReadAllFinishedCourses()
{
	UserDirectoryManagment directory;
	directory.CreateUserDir(this->person);
	std::string filepath = (directory.GetPath() + this->person + "FinishedCourses.txt");
	std::string CourseName, grade;
	std::vector<std::pair<std::string, int>> FinishedVec;
	std::ifstream inFile(filepath, std::ios::in);
	if (inFile.is_open())
	{
		while (inFile.good())
		{
			std::getline(inFile, CourseName, ',');
			std::getline(inFile, grade, '\n');
			FinishedVec.push_back({ CourseName,stoi(grade) });
			inFile >> std::ws;
		}
		inFile.close();
	}
	return FinishedVec;
}