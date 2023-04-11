#include "CourseDirectoryManagment.h"

CourseDirectoryManagment::CourseDirectoryManagment()
{
	namespace fs = std::filesystem;
	std::string directory = fs::current_path().string() + "/Courses/";
	if (!fs::exists(directory))
		fs::create_directories(directory);
	this->path = directory;
}
std::string CourseDirectoryManagment::GetPath()const
{
	return this->path;
}
void CourseDirectoryManagment::CreateCourseDir(std::string Name)
{
	namespace fs = std::filesystem;
	this->path += Name;
	this->path += "/";
	std::string directory = this->path;
	if (!fs::exists(directory))
		fs::create_directories(directory);
	this->path = directory;

}