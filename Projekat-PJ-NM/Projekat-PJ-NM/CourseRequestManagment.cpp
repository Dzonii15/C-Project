#include "CourseRequestManagment.h"

CourseRequestManagment::CourseRequestManagment() :Professor(""), Student(""), Course("")
{

}
CourseRequestManagment::CourseRequestManagment(std::string prof, std::string stu, std::string cour) : Professor(prof), Student(stu), Course(cour)
{

}
void CourseRequestManagment::CourseSignUp()
{
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(this->Professor);
	std::string filePath = (scanner.GetPath() + this->Professor + "CourseRequest.txt");
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << this->Student << "," << this->Course << '\n';
		outFile.close();
	}
	else
		throw std::exception("Unable to open file");
}
void CourseRequestManagment::ReadRequest(std::ifstream& inFile, std::string& Student, std::string& Course)
{
	std::getline(inFile, Student, ',');
	std::getline(inFile, Course, '\n');
	inFile >> std::ws;
}
void  CourseRequestManagment::SetProfessor(std::string prof)
{
	this->Professor = prof;
}
void  CourseRequestManagment::SetStudent(std::string stu)
{
	this->Student = stu;
}
void  CourseRequestManagment::SetCourse(std::string cour)
{
	this->Course = cour;
}
std::vector<std::pair<std::string, std::string>> CourseRequestManagment::LoadRequests(std::ifstream& inFile)
{
	std::string Student;
	std::string Course;
	std::vector<std::pair<std::string, std::string>> requests;
	while (inFile.good())
	{
		this->ReadRequest(inFile, Student, Course);
		requests.push_back({ Student,Course });
	}
	return requests;
}
bool  CourseRequestManagment::CheckRequest(std::ifstream& inFile)
{
	if (GlobalFunctions::IsFileEmpty(inFile))
	{
		return false;
	}
	inFile.seekg(0, std::ios::beg);
	return true;
}
std::vector<std::pair<std::string, std::string>> CourseRequestManagment::LoadCourseRequests(std::string path)
{
	std::vector<std::pair<std::string, std::string>>CourseRequests;
	std::ifstream InFile(path, std::ios::in);
	if (InFile.is_open())
	{
		if (this->CheckRequest(InFile))
		{
			CourseRequests = this->LoadRequests(InFile);
		}
		InFile.close();
	}
	else
		throw std::exception("Unable to open file");

	return CourseRequests;
}
void CourseRequestManagment::writeAllRequests(std::string path, std::vector<std::pair<std::string, std::string>>& Requests)
{

	if (Requests.empty())
	{

		std::ofstream ofs;
		ofs.open(path, std::ofstream::trunc);
		if (ofs.is_open())
			ofs.close();
		else throw std::exception("Unable to open file");

	}
	else {
		std::ofstream outFile(path, std::ios::out);
		if (outFile.is_open())
		{
			for (auto element : Requests)
			{
				outFile << element.first << "," << element.second << '\n';
			}
			outFile.close();
		}
	}
}

