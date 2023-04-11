#include "UserDirectoryManagment.h"

UserDirectoryManagment::UserDirectoryManagment()
{

	namespace fs = std::filesystem;
	std::string directory = fs::current_path().string() + "/Users/";
	if (!fs::exists(directory))
		fs::create_directories(directory);
	this->path = directory;

}
std::string UserDirectoryManagment::GetPath()const
{
	return this->path;
}
void UserDirectoryManagment::CreateUserDir(std::string UName)
{
	namespace fs = std::filesystem;
	this->path += UName;
	this->path += "/";
	std::string directory = this->path;
	if (!fs::exists(directory))
		fs::create_directories(directory);
	this->path = directory;

}