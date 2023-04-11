#pragma once
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "CourseDirectoryManagment.h"
class CourseInteraction
{
public:
	static void ReadStudents(int, std::string, std::set<std::string>&);
	static void CourseIntersection(const std::set<std::string>&, const std::set<std::string>&, std::set<std::string>&);
	static void CourseUnion(const std::set<std::string>&, const std::set<std::string>&, std::set<std::string>&);
	static void CourseDifference(const std::set<std::string>&, const std::set<std::string>&, std::set<std::string>&);
};