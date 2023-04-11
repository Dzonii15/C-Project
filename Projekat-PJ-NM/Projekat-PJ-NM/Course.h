#pragma once
#include <string>
#include <iostream>
class Course
{
private:
	//Ime Kursa
	std::string Name;
	//Tip Kursa
	std::string Type;
	//Profesor koji vodi kurs
	std::string Professor;
public:
	//Konstruktori
	Course();
	Course(std::string, std::string, std::string);

	//Geteri
	std::string GetName()const;
	std::string GetType()const;
	std::string GetProfessor()const;

	//Seteri
	void SetName(std::string);
	void SetType(std::string);
	void SetProfessor(std::string);
};