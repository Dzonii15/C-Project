#pragma once
#include <string>
#include <filesystem>
class CourseDirectoryManagment
{
private:
	std::string path;
public:
	//napravi direktorijum za usere
	CourseDirectoryManagment();
	std::string GetPath()const;
	//napravi direktorijum za posebnog usera
	void CreateCourseDir(std::string);
};