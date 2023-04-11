#pragma once
#include <string>
#include <filesystem>
class UserDirectoryManagment
{
private:
	std::string path;
public:
	//napravi direktorijum za usere
	UserDirectoryManagment();
	std::string GetPath()const;
	//napravi direktorijum za posebnog usera
	void CreateUserDir(std::string);
};