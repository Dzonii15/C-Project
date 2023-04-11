#include "ProfessorInteraction.h"

void ProfessorInteraction::GradeStudent(std::ostream& os, std::istream& is, const Professor* profa, const std::vector<User*>& UserVek, const std::vector<Course>& CourseVek)
{
	std::getchar();
	std::string studentUname, courseName;
	os << "Unesite studenta koga zelite ocijeniti:"; std::getline(is, studentUname);
	auto student = std::find_if(UserVek.begin(), UserVek.end(), [studentUname](const User* korisnik) {return korisnik->GetType() == "Student" && korisnik->GetUserName() == studentUname; });
	os << "Unesite kurs koji zelite ocijeniti datog studenta:"; std::getline(is, courseName);
	auto courseToGrade = std::find_if(CourseVek.begin(), CourseVek.end(), [courseName](const Course& kurs) {return kurs.GetName() == courseName; });
	if (student == UserVek.end())
	{
		os << "Ne postoji student sa tim usernameom" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	if (courseToGrade == CourseVek.end())
	{
		os << "Ne postoji kurs sa tim nazivom" << std::endl;
		os << "Prekid akcije" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	if ((*courseToGrade).GetProfessor() != profa->GetUserName())
	{
		os << "Niste nadlezni za ovaj kurs!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	auto courses = (*student)->GetCourses();
	auto kurs = std::find(courses.begin(), courses.end(), courseName);
	if (kurs == courses.end())
	{
		os << "Student ne pohadja dati kurs" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	FinishedCoursesManagment FCourseScanner(studentUname);
	int ocjena;
	os << "Unesite ocjenu studenta na ovom kursu (6-10):"; is >> ocjena;
	FCourseScanner.WriteFinishedCourse(courseName, ocjena);
	CourseManagment course(courseName);
	course.StudentFinishedCourse(studentUname);
	os << "Uspjesno ste ocijenili datog studenta!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");


}