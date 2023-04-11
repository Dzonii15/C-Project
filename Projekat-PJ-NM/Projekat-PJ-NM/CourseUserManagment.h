#pragma once
#include "UserDirectoryManagment.h"
#include <fstream>
//Klasa sluzi za upravljanje fajla za listu kurseva kod korisnika
class CourseUserManagment
{
private:
	//Korisnik u kojeg se upisuje kurs 
	std::string user;
	//Kurs 
	std::string course;
public:

	//Konstruktori
	CourseUserManagment();
	CourseUserManagment(std::string, std::string);

	//Seteri
	void SetUser(std::string);
	void SetCourse(std::string);

	//Funkcija dodaje novi kurs na kraj fajla
	void UpdateUserCourseList();
	//Funkcija upisuje sve kurseve u fajl
	void WriteAllCoursesofUser(const std::vector<std::string>&);

	//Funkcija brise kurs iz liste korisnika
	void DeleteCourseFromUserList();
	//Funkcija cita sve kurseve od korisnika
	std::vector < std::string > ReadAllCourses();
private:
	std::string FilePath();

};