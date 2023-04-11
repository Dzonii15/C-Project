#include "InboxFileManagment.h"
#include "Course.h"
#include "RequestInteraction.h"
#include "InboxInteraction.h"
#include "ProfessorInteraction.h"
#include "AdministratorInteraction.h"
#include "LogIn.h"
#include "GraphSupport.h"

int main()
{
	std::vector<User*>UserVector;
	std::vector<Course>CourseVector;
	//Ucitavanje svih korisnika i kurseva
	CourseVector = CourseManagment::ReadCourses();
	UserVector = AccountManagment::ReadAllUsers();
	User* korisnik;
	//Radi
	LogIn::Login(std::cout, std::cin, UserVector, &korisnik);
	Student* student = dynamic_cast<Student*>(korisnik);
	Professor* profesor = dynamic_cast<Professor*>(korisnik);
	Administrator* administrator = dynamic_cast<Administrator*>(korisnik);
	int Option;
	if (student != nullptr)
	{
		std::cout << "Ulogovali ste se kao student!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		do
		{
			std::cout << "(1)Prijava na kurs" << std::endl;
			std::cout << "(2)Poslati zahtjev za prijateljstvo" << std::endl;
			std::cout << "(3)Poslati poruku" << std::endl;
			std::cout << "(4)Prihvatiti zahtjev za prijateljstvo" << std::endl;
			std::cout << "(5)Filtrirati Razgovor" << std::endl;
			std::cout << "(6)Zahtjev za promjenu sifre" << std::endl;
			std::cout << "(7)Kraj" << std::endl;
			std::cout << "Opcija:"; std::cin >> Option;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			if (Option == 1)
			{
				//Radi
				RequestInteraction::SendCourseEnrollmentRequest(std::cout, std::cin, student, CourseVector);
			}
			else if (Option == 2)
			{
				//Radi
				RequestInteraction::SendFriendRequest(std::cout, std::cin, student, UserVector);
			}
			else if (Option == 3)
			{
				//Radi
				InboxInteraction::chat(std::cout, std::cin, student, UserVector, CourseVector);
			}
			else if (Option == 4)
			{
				//Radi
				RequestInteraction::AcceptFriendRequest(std::cout, std::cin, student, UserVector);
			}
			else if (Option == 5)
			{
				//Radi
				InboxInteraction::filterChat(std::cout, std::cin, student);
			}
			else if (Option == 6)
			{
				RequestInteraction::passwordChangeRequest(std::cout, std::cin, student, UserVector);
			}
		} while (Option != 7);
	}
	else if (profesor != nullptr)
	{
		std::cout << "Ulogovali ste se kao profesor!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		do {
			std::cout << "(1)Prihvatanje studenta na kurs" << std::endl;
			std::cout << "(2)Poslati zahtjev za prijateljstvo" << std::endl;
			std::cout << "(3)Poslati poruku" << std::endl;
			std::cout << "(4)Prihvatiti zahtjev za prijateljstvo" << std::endl;
			std::cout << "(5)Filtrirati Razgovor" << std::endl;
			std::cout << "(6)Ocijeni studenta " << std::endl;
			std::cout << "(7)Zahtjev za promjenu sifre" << std::endl;
			std::cout << "(8)Kraj" << std::endl;
			std::cout << "Opcija:"; std::cin >> Option;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");

			if (Option == 1)
			{
				//Radi
				RequestInteraction::AcceptStudentToCourse(std::cout, std::cin, profesor, UserVector, CourseVector);
			}
			else if (Option == 2)
			{
				//Radi
				RequestInteraction::SendFriendRequest(std::cout, std::cin, profesor, UserVector);
			}
			else if (Option == 3)
			{
				//Radi
				InboxInteraction::chat(std::cout, std::cin, profesor, UserVector, CourseVector);
			}
			else if (Option == 4)
			{
				//Radi
				RequestInteraction::AcceptFriendRequest(std::cout, std::cin, profesor, UserVector);
			}
			else if (Option == 5)
			{
				//Radi
				InboxInteraction::filterChat(std::cout, std::cin, profesor);
			}
			else if (Option == 6)
			{
				//Radi
				ProfessorInteraction::GradeStudent(std::cout, std::cin, profesor, UserVector, CourseVector);
			}
			else if (Option == 7)
			{
				RequestInteraction::passwordChangeRequest(std::cout, std::cin, profesor, UserVector);
			}
		} while (Option != 8);
	}
	else if (administrator != nullptr)
	{
		std::cout << "Ulogovali ste se kao administrator!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		do {
			std::cout << "(1)Kreiranje Naloga" << std::endl;
			std::cout << "(2)Brisanje Naloga" << std::endl;
			std::cout << "(3)Kreiranje Kursa" << std::endl;
			std::cout << "(4)Brisanje Kursa" << std::endl;
			std::cout << "(5)Ispitivanje grafa poznanstva" << std::endl;
			std::cout << "(6)Prihvati zahtjeve za promjenu sifre" << std::endl;
			std::cout << "(7)Operacije nad kursevima" << std::endl;
			std::cout << "(8)Modifikacija kursa (Promjena tipa)" << std::endl;
			std::cout << "(9)Kraj" << std::endl;
			std::cout << "Opcija:"; std::cin >> Option;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			if (Option == 1)
			{
				//Radi
				AdministratorInteraction::CreateAccount(std::cout, std::cin, UserVector);
			}
			else if (Option == 2)
			{
				//Radi
				AdministratorInteraction::DeleteAccount(std::cout, std::cin, UserVector, CourseVector);
			}
			else if (Option == 3)
			{
				//Radi
				AdministratorInteraction::CreateCourse(std::cout, std::cin, CourseVector, UserVector);
			}
			else if (Option == 4)
			{
				//Radi, potencijali bug-ovi?
				AdministratorInteraction::DeleteCourse(std::cout, std::cin, CourseVector, UserVector);
			}
			else if (Option == 5)
			{
				std::getchar();
				GraphSupport::CalculateAverageDistance(std::cout, std::cin, UserVector);
			}
			else if (Option == 6)
			{
				AdministratorInteraction::AcceptPasswordChange(std::cout, std::cin, UserVector, administrator);
			}
			else if (Option == 7)
			{
				AdministratorInteraction::CourseInspection(std::cout, std::cin, CourseVector);
			}
			else if (Option == 8)
			{
				AdministratorInteraction::ModifyCourse(std::cout, std::cin, CourseVector);
			}
		} while (Option != 9);
	}
	for (auto el : UserVector)
		delete el;
}