#pragma once
#include "CourseDirectoryManagment.h"
#include <fstream>
#include "Course.h"
//Klasa se bavi direkotrijumom kurseva i fajlovima unutar
class CourseManagment
{
private:
	std::string Name;
public:
	//Konstruktor
	CourseManagment();
	CourseManagment(std::string);
	//Seter
	void SetCourseName(std::string);
	//Azurira listu studenata koji slusaju dati kurs
	void CourseStudentUpdate(std::string);
	//Upisuje vektor studenata u fajl 
	void WriteAllStudents(std::vector<std::string>&, std::ofstream&);
	//Brise Studenta iz kursa
	void DeleteFromCourse(std::string);
	//Ucitava sve studente iz kursa
	void ReadCourseStudents(std::vector<std::string>&);
	//Funkcija ucitava sve kurseve na pocetku programa
	static std::vector<Course> ReadCourses();
	//Funkcija upisuje sve kurseve u fajl za kurseve
	static void WriteAllCourses(const std::vector<Course>&);
	//Funkcija upisuje jedan kurs na kraj fajla
	static void WriteCourseAtTheEnd(const Course&);
	//Prebacuje studenta u fajl studenata koji su zavrsili kurs
	void StudentFinishedCourse(std::string);
};