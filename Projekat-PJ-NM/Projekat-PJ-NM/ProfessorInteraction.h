#pragma once
#include "AccoutManagment.h"
class ProfessorInteraction
{
public:
	static void GradeStudent(std::ostream&, std::istream&, const Professor*, const std::vector<User*>&, const std::vector<Course>&);
	/*
	ocijeni studenta, da mu ocjenu, kurs se brise iz liste kurseva studenta, dodaje se u fajl polozenih zajedno sa ocjenom i brise se iz liste kurseva i stavlja u fajl rijesenih

	*/
};