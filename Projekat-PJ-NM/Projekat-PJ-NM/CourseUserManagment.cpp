#include "CourseUserManagment.h"
CourseUserManagment::CourseUserManagment() :user(""), course("")
{

}
CourseUserManagment::CourseUserManagment(std::string USER, std::string COURSE) : user(USER), course(COURSE)
{

}
void CourseUserManagment::SetUser(std::string User)
{
	this->user = User;
}
void CourseUserManagment::SetCourse(std::string Course)
{
	this->course = Course;
}
void CourseUserManagment::UpdateUserCourseList()
{
	std::string filepath = this->FilePath();
	std::ofstream outFile(filepath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << this->course << '\n';
		outFile.close();
	}
	else
		throw std::exception("Unable to open file");
}
std::vector<std::string> CourseUserManagment::ReadAllCourses()
{
	std::vector<std::string>courses;
	std::string temp;
	std::string filepath = this->FilePath();
	std::ifstream inFile(filepath, std::ios::in);
	if (inFile.is_open())
	{
		while (inFile.good())
		{
			std::getline(inFile, temp, '\n');
			inFile >> std::ws;
			courses.push_back(temp);
		}
		inFile.close();
	}
	return courses;
}
void CourseUserManagment::WriteAllCoursesofUser(const std::vector<std::string>& CourseVec)
{

	std::string filepath = this->FilePath();
	std::ofstream outFile(filepath, std::ios::out);
	if (outFile.is_open())
	{
		for (auto el : CourseVec)
			outFile << el << "\n";
		outFile.close();
	}
	else
		throw std::exception("Could not open file");

}
void  CourseUserManagment::DeleteCourseFromUserList()
{
	std::vector<std::string> CourseVec = this->ReadAllCourses();
	auto it = find(CourseVec.begin(), CourseVec.end(), this->course);
	if (it == CourseVec.end())
		throw std::invalid_argument("This course does not exist");
	CourseVec.erase(it);
	this->WriteAllCoursesofUser(CourseVec);
}
std::string CourseUserManagment::FilePath()
{
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(this->user);
	return (scanner.GetPath() + this->user + "CourseList.txt");
}