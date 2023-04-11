#pragma once
#include "GlobalFunctions.h"
#include "UserDirectoryManagment.h"

//Klasa se bavi prijavama na kurs
//Prijave se pisu u direktorijum od profesora u fajl za zahtjeve za prijavu na kurs
class CourseRequestManagment
{
private:
	//Profesor koji je nadlezan za kurs
	std::string Professor;
	//Student koji salje zahtjev
	std::string Student;
	//Kurs koji je u pitanju
	std::string Course;
public:
	//Konstruktori
	CourseRequestManagment();
	CourseRequestManagment(std::string, std::string, std::string);

	//Seteri
	void SetProfessor(std::string);
	void SetStudent(std::string);
	void SetCourse(std::string);

	//Funkcija za prijavu na kurs
	void CourseSignUp();

	//Skup funkcija za ucitavanje prijava iz fajla
	void ReadRequest(std::ifstream&, std::string&, std::string&);
	std::vector<std::pair<std::string, std::string>>LoadRequests(std::ifstream&);
	std::vector<std::pair<std::string, std::string>> LoadCourseRequests(std::string path);

	//Funkcija upisuje sve zahtjeve iz vektora u fajl
	void writeAllRequests(std::string, std::vector<std::pair<std::string, std::string>>&);
	bool CheckRequest(std::ifstream&);

};