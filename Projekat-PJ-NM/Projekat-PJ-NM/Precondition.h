#pragma once
#include "Student.h"
#include "FinishedCoursesManagment.h"
class Precondition
{

public:
	virtual bool CoursePrecondition(Student*)const = 0;
	virtual std::string GetType()const = 0;
	virtual std::string getDescription()const = 0;
};
/*
Svaki kurs ce u svom direktorijumu imati fajl sa uslovima da se upise
Kada profesor bude prihvato studente na kurs morace se provjeriti ti uslovi
prije toga moraju se ucitati
ucitavanje
id kursa - dodatni zahtjevi
neka klasa koja ucitava zahtjeve za dati kurs
problem
kursevi zahtjevaju svaki posebno
*/