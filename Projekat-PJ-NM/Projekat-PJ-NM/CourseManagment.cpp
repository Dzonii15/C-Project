#include "CourseManagment.h"
CourseManagment::CourseManagment() :Name("")
{

}
CourseManagment::CourseManagment(std::string cours) : Name(cours)
{

}
void CourseManagment::SetCourseName(std::string Course)
{
	this->Name = Course;
}
void CourseManagment::CourseStudentUpdate(std::string User)
{
	CourseDirectoryManagment scanner;
	scanner.CreateCourseDir(this->Name);
	std::string filePath = (scanner.GetPath() + "StudentList.txt");
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << User << '\n';
		outFile.close();
	}
}
std::vector<Course> CourseManagment::ReadCourses()
{
	CourseDirectoryManagment scanner;
	std::vector<Course> courses;
	std::string nameTemp, typeTemp, profTemp;
	std::string filePath = (scanner.GetPath() + "Courses.csv");
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile.is_open())
	{
		while (inFile.good())
		{
			std::getline(inFile, nameTemp, ',');
			std::getline(inFile, typeTemp, ',');
			std::getline(inFile, profTemp, '\n');
			inFile >> std::ws;
			courses.push_back(Course(nameTemp, typeTemp, profTemp));
		}
	}
	return courses;


}
void CourseManagment::WriteAllCourses(const std::vector<Course>& CourVec)
{
	CourseDirectoryManagment scanner;
	std::string filePath = (scanner.GetPath() + "Courses.csv");
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		for (auto element : CourVec)
		{
			outFile << element.GetName() << ',' << element.GetType() << ',' << element.GetProfessor() << '\n';
		}
		outFile.close();
	}
	else throw std::exception("Unable to open file");

}

void CourseManagment::WriteCourseAtTheEnd(const Course& kurs)
{
	CourseDirectoryManagment scanner;
	std::string filePath = (scanner.GetPath() + "Courses.csv");
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << kurs.GetName() << ',' << kurs.GetType() << "," << kurs.GetProfessor() << '\n';
		outFile.close();
	}
	else
		throw std::exception("Unable to open file");
}
void  CourseManagment::ReadCourseStudents(std::vector<std::string>& studentList)
{
	CourseDirectoryManagment CourseScanner;
	CourseScanner.CreateCourseDir(this->Name);
	std::string filePath = (CourseScanner.GetPath() + "StudentList.txt");
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile.is_open())
	{
		std::string temp;
		while (inFile.good())
		{
			std::getline(inFile, temp, '\n');
			inFile >> std::ws;
			studentList.push_back(temp);
		}
		inFile.close();
	}
}
void CourseManagment::WriteAllStudents(std::vector<std::string>& studentlist, std::ofstream& outFile)
{
	for (auto element : studentlist)
	{
		outFile << element << '\n';
	}
}
void CourseManagment::DeleteFromCourse(std::string person)
{
	CourseDirectoryManagment CourseScanner;
	CourseScanner.CreateCourseDir(this->Name);
	std::vector <std::string>studentList;
	this->ReadCourseStudents(studentList);
	std::string filePath = CourseScanner.GetPath() + "StudentList.txt";
	auto it = find(studentList.begin(), studentList.end(), person);
	studentList.erase(it);
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		this->WriteAllStudents(studentList, outFile);
		outFile.close();
	}
}
void CourseManagment::StudentFinishedCourse(std::string person)
{
	this->DeleteFromCourse(person);
	CourseDirectoryManagment CourseScanner;
	CourseScanner.CreateCourseDir(this->Name);
	std::string filePath = CourseScanner.GetPath() + "StudentListFinished.txt";
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << person << std::endl;
		outFile.close();
	}
}
