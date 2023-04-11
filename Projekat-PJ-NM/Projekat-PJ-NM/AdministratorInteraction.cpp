#include "AdministratorInteraction.h"

void AdministratorInteraction::CreateAccount(std::ostream& os, std::istream& is, std::vector<User*>& UserVec)
{
	int option;

	std::string username, password, name, surname, jmbg;
	os << "Unesite vrstu naloga koji zelite napraviti:" << std::endl;
	os << "(1)Student" << std::endl;
	os << "(2)Professor" << std::endl;
	os << "Opcija:"; is >> option;
	system("CLS");
	std::getchar();
	os << "Unesite username korisnika:"; std::getline(is, username);
	os << "Unesite sifru korisnika:"; is >> password;
	os << "Unesite ime korisnika:"; is >> name;
	os << "Unesite prezime korisnika:"; is >> surname;
	os << "Unesite JMBG korinsika:"; is >> jmbg;
	int i = 0;
	do
	{

		auto it = find_if(UserVec.begin(), UserVec.end(), [username](const User* korisnik)
			{return korisnik->GetUserName() == username; });
		if (it == UserVec.end())
			break;
		os << "Nalog sa tim username-om vec postoji!" << std::endl;
		os << "Unesite username ponovo:"; is >> username;

	} while (i++ < 3);
	if (i >= 3)
	{
		os << "Prekoracili ste broj unosa (3)" << std::endl;
		os << "Prekid Akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		system("CLS");
		return;
	}

	if (option == 1)
	{
		Student* novi = new Student(username, password, name, surname, jmbg);
		UserVec.push_back(novi);
		AccountManagment::WriteUserAtEnd(novi);

	}

	else if (option == 2)
	{
		Professor* novi = new Professor(username, password, name, surname, jmbg);
		UserVec.push_back(novi);
		AccountManagment::WriteUserAtEnd(novi);
	}
	os << "Nalog je napravljen i dodat u sistem!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("CLS");
}
void AdministratorInteraction::DeleteAccount(std::ostream& os, std::istream& is, std::vector<User*>& UserVekt, std::vector<Course>& CourVek)
{
	std::getchar();
	std::string userName;
	os << "Unesite username korisnika koga zelite izbrisati:";
	std::getline(is, userName);
	auto user = find_if(UserVekt.begin(), UserVekt.end(), [userName](const User* korisnik)
		{return userName == korisnik->GetUserName(); });
	if (user == UserVekt.end())
	{
		os << "Neispravan unos, korisnik sa datim username-om ne postoji!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	UserDirectoryManagment direktorijum;
	direktorijum.CreateUserDir(userName);
	FriendAccountManagment friendScanner;

	//Brisanje prijatelja
	friendScanner.SetPerson2((*user)->GetUserName());
	auto friendList = (*user)->GetFriends();
	for (auto element : friendList)
	{
		friendScanner.SetPerson1(element);
		friendScanner.DeleteFromFriendList();
	}
	//Brisanje iz kurseva
	Student* student = dynamic_cast<Student*>(*user);
	CourseManagment courseScanner;
	if (student != nullptr)
	{
		auto courses = student->GetCourses();
		for (auto element : courses)
		{
			courseScanner.SetCourseName(element);
			courseScanner.DeleteFromCourse(student->GetUserName());
		}
	}
	else
	{
		Professor* prof = dynamic_cast<Professor*>(*user);
		auto courses = prof->GetCourses();
		for (auto element : courses)
		{
			auto find = find_if(CourVek.begin(), CourVek.end(), [element](const Course& kurs)
				{return kurs.GetName() == element; });
			std::string newProf;
			os << "Unesite profesora koji ce ga zamijeniti:";
			std::getline(is, newProf);
			CourseUserManagment scanner(newProf, element);
			scanner.UpdateUserCourseList();
			(*find).SetProfessor(newProf);
		}
		CourseManagment::WriteAllCourses(CourVek);
	}

	std::filesystem::remove_all(direktorijum.GetPath());
	delete* user;//Potencijalna greska
	UserVekt.erase(user);
	AccountManagment::WriteAllUsers(UserVekt);
	os << "Nalog je uspjesno obrisan" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");
}
void AdministratorInteraction::CreateCourse(std::ostream& os, std::istream& is, std::vector<Course>& CourseVek, const std::vector<User*>& UserVek)
{
	std::string Ime, Coursetype, Prof;
	std::getchar();
	os << "Unesite Ime kursa:";
	std::getline(is, Ime);
	os << "Unesite tip kursa:";
	std::getline(is, Coursetype);
	os << "Unesite Profesora nadleznog za taj kurs:";
	std::getline(is, Prof);
	auto it = find_if(CourseVek.begin(), CourseVek.end(), [Ime](const Course& kurs) {return Ime == kurs.GetName(); });
	if (it != CourseVek.end())
	{
		os << "Taj kurs vec postoji!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;

	}
	auto iterator = find_if(UserVek.begin(), UserVek.end(), [Prof](const User* korisnik) {return Prof == korisnik->GetUserName() && korisnik->GetType() == "Professor"; });
	if (iterator == UserVek.end())
	{
		os << "Ne postoji profesor sa datim usernameom!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;

	}
	system("CLS");
	CoursePreconditionManagment scanPrec(Ime);
	os << "Definisite preduslove koje ce te postaviti na kurs" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");
	int PrecOption;
	os << "Detalji prvog preduslova:" << std::endl;
	Precondition* prec = new NumOfCoursesPrec(0);
	os << prec->getDescription();
	os << std::endl;
	os << "Da li zelite postaviti ovaj preduslov za ovaj kurs?" << std::endl;
	os << "              (1)Da | (2)Ne" << std::endl;
	os << "Opcija:"; is >> PrecOption;
	if (PrecOption == 1)
	{
		int courseNum;
		os << "Definisite broj kurseva potrebnih da se prijavite na ovaj kurs:";
		is >> courseNum;
		((NumOfCoursesPrec*)prec)->setNumOfCourses(courseNum);
		scanPrec.WriteOnePrecondition(prec);


	}
	delete prec;
	prec = nullptr;
	system("CLS");
	prec = new HasHeFinishedCoursePrec("");
	os << "Detalji drugog preduslova:" << std::endl;
	os << prec->getDescription();
	os << "Da li zelite postaviti ovaj preduslov za ovaj kurs?" << std::endl;
	os << "              (1)Da | (2)Ne" << std::endl;
	os << "Opcija:"; is >> PrecOption;
	if (PrecOption == 1)
	{
		std::string finishedCourse;
		os << "Definisati kurs koji se mora poloziti da bi se studenat prijavio na ovaj kurs:";
		std::getchar();
		std::getline(is, finishedCourse);
		auto checker = std::find_if(CourseVek.begin(), CourseVek.end(), [finishedCourse](const Course& kurs) {return kurs.GetName() == finishedCourse; });
		if (checker == CourseVek.end())
		{
			os << "Ne postoji dati kurs!" << std::endl;
			os << "Prekid akcije!" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			delete prec;
			return;
		}
		((HasHeFinishedCoursePrec*)prec)->SetCourse(finishedCourse);
		scanPrec.WriteOnePrecondition(prec);
	}
	if (prec != nullptr)
		delete prec;
	/*
	Definisati preduslov za polaganje datog kursa,
	*/
	Course newCourse(Ime, Coursetype, Prof);
	CourseUserManagment scanner(Prof, Ime);
	scanner.UpdateUserCourseList();
	CourseManagment::WriteCourseAtTheEnd(newCourse);
	CourseVek.push_back(newCourse);
	os << "Kurs je uspjesno kreiran!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("CLS");
}
void AdministratorInteraction::DeleteCourse(std::ostream& os, std::istream& is, std::vector<Course>& CourseVek, std::vector<User*>& UserVekt)
{
	std::getchar();
	std::string name;
	os << "Unesite ime kursa kojeg zelite obrisati:";
	std::getline(is, name);
	auto it = find_if(CourseVek.begin(), CourseVek.end(), [name](const Course& kurs) {return name == kurs.GetName(); });
	if (it == CourseVek.end())
	{
		os << "Ne postoji unijeti kurs!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	CourseDirectoryManagment direktorijum;
	direktorijum.CreateCourseDir(name);
	for (auto korisnik : UserVekt)
	{
		std::vector<std::string> vektorkurseva = korisnik->GetCourses();
		auto it = find(vektorkurseva.begin(), vektorkurseva.end(), name);
		if (it != vektorkurseva.end())
		{
			CourseUserManagment scanner(korisnik->GetUserName(), *it);
			scanner.DeleteCourseFromUserList();
		}
	}

	auto iterator = find_if(CourseVek.begin(), CourseVek.end(), [name](const Course& kurs) {return kurs.GetName() == name; });
	if (iterator == CourseVek.end())
	{
		throw std::exception("Something went wrong");
	}
	std::filesystem::remove_all(direktorijum.GetPath());
	CourseVek.erase(iterator);
	CourseManagment::WriteAllCourses(CourseVek);
	os << "Kurs je uspjesno obrisan!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");
}
void AdministratorInteraction::AcceptPasswordChange(std::ostream& os, std::istream& is, std::vector<User*>& UserVek, const Administrator* admin)
{
	UserDirectoryManagment directory;
	directory.CreateUserDir(admin->GetUserName());
	std::string filePath = (directory.GetPath() + "PasswordRequest.txt");
	std::vector<std::pair<std::string, std::string>> temp;
	std::vector<std::pair<std::string, std::string>> reqVek;
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile)
	{
		//if (GlobalFunctions::IsFileEmpty(inFile))
		//{
		//	os << "Nemate zahtjeva za promjenu sifre." << std::endl;
		//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//	system("CLS");
		//	inFile.close();
		//	return;
		//}

		PasswordRequestManagment Reqscanner;
		while (inFile.good())
		{
			std::string user, pass;

			std::getline(inFile, user, ',');
			std::getline(inFile, pass, '\n');
			inFile >> std::ws;
			reqVek.push_back({ user,pass });

		}
		for (auto element : reqVek)
		{
			UserDirectoryManagment userdir;
			userdir.CreateUserDir(element.first);
			std::string filePath = userdir.GetPath() + "PasswordChange.txt";
			std::ofstream outputFile(filePath, std::ios::out);
			auto user = std::find_if(UserVek.begin(), UserVek.end(), [element](const User* korisnik) {return korisnik->GetUserName() == element.first; });
			if (user == UserVek.end())
			{
				temp.push_back(element);
			}
			else
			{
				int pickOption;
				os << "Da li zelite prihvatiti zahtjev za promjenu sifre od " << element.first << std::endl;
				os << "                    (1)Da | (2)Ne | (3) Ostavi za poslije" << std::endl;
				os << "Opcija:"; is >> pickOption;
				if (pickOption == 1)
				{
					temp.push_back(element);
					(*user)->ChangePassword(element.second);
					outputFile << 1;

				}
				else if (pickOption == 2)
				{
					temp.push_back(element);
					outputFile << 0;
				}
			}
			outputFile.close();
		}
		inFile.close();
	}
	else
	{
		os << "Nemate zahtjeva za promjenu sifre." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	for (auto element : temp)
	{
		auto it = std::find(reqVek.begin(), reqVek.end(), element);
		reqVek.erase(it);
	}
	PasswordRequestManagment Reqscanner;
	Reqscanner.SetAdmin(admin->GetUserName());
	Reqscanner.WriteRequests(reqVek);
	AccountManagment::WriteAllUsers(UserVek);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");

}
void AdministratorInteraction::CourseInspection(std::ostream& os, std::istream& is, const std::vector<Course>& CourseVek)
{
	std::getchar();
	std::string FirstCourse, SecondCourse;
	os << "Odaberite prvi kurs:"; std::getline(is, FirstCourse);
	auto firstCourse = std::find_if(CourseVek.begin(), CourseVek.end(), [FirstCourse](const Course& kurs) {return FirstCourse == kurs.GetName(); });
	os << "Odaberite drugi kurs:"; std::getline(is, SecondCourse);
	auto secondCourse = std::find_if(CourseVek.begin(), CourseVek.end(), [SecondCourse](const Course& kurs) {return SecondCourse == kurs.GetName(); });
	if (firstCourse == CourseVek.end() || secondCourse == CourseVek.end())
	{
		os << "Pogresan unos!" << std::endl;
		os << "Prekid akcije" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	int option;
	std::set<std::string> firstCourseSet;
	std::set<std::string> secondCourseSet;
	std::set<std::string> finishedSet;

	os << "Da li vas zanimaju trenutno prijavljeni studenti ili studenti koji su zavrsili prvi kurs?" << std::endl;
	os << "                      (1)Trenutno prijavljeni | (2)Koji su zavrsili" << std::endl;
	os << "Opcija:"; is >> option;
	CourseInteraction::ReadStudents(option, FirstCourse, firstCourseSet);
	system("CLS");
	os << "Da li vas zanimaju trenutno prijavljeni studenti ili studenti koji su zavrsili drugi kurs?" << std::endl;
	os << "                      (1)Trenutno prijavljeni | (2)Koji su zavrsili" << std::endl;
	os << "Opcija:"; is >> option;
	CourseInteraction::ReadStudents(option, SecondCourse, secondCourseSet);
	system("CLS");

	os << "Odaberite koju operaciju izvrsiti nad kursevima." << std::endl;
	os << "  (1)Unija | (2)Presjek | (3)Razlika (Prvog od Drugog)" << std::endl;
	os << "Opcija:"; is >> option;
	if (option == 1)
	{
		CourseInteraction::CourseUnion(firstCourseSet, secondCourseSet, finishedSet);
		os << "Unija dva kursa:" << std::endl;
		for (auto student : finishedSet)
			os << student << std::endl;
	}
	else if (option == 2)
	{
		CourseInteraction::CourseIntersection(firstCourseSet, secondCourseSet, finishedSet);
		os << "Presjek dva kursa:" << std::endl;
		for (auto student : finishedSet)
			os << student << std::endl;
	}
	else if (option == 3)
	{
		CourseInteraction::CourseIntersection(firstCourseSet, secondCourseSet, finishedSet);
		os << "Razlika prvog kursa od drugog:" << std::endl;
		for (auto student : finishedSet)
			os << student << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	system("CLS");

}
void AdministratorInteraction::GraphMenu(std::ostream& os, std::istream& is, const std::vector<User*>& userVec)
{
	int option;
	os << "Izaberite opciju:";
	os << "(1)Ispitivanje najkrace distance izmedju dva korisnika | (2)Prosjecna duzina po uslovima " << std::endl;
	os << "Opcija:"; is >> option;
	if (option == 1)
	{
		GraphSupport::CalculateShortestDistance(os, is, userVec);
	}
	else if (option == 2)
	{
		GraphSupport::CalculateAverageDistance(os, is, userVec);
	}
	system("CLS");

}
void AdministratorInteraction::ModifyCourse(std::ostream& os, std::istream& is, std::vector<Course>& CourseVek)
{
	std::getchar();
	std::string courseName;
	os << "Unesite kurs ciji tip zelite promijeniti:"; std::getline(is, courseName);
	auto findCourse = std::find_if(CourseVek.begin(), CourseVek.end(), [courseName](Course& kurs) {return courseName == kurs.GetName()});
	if (findCourse == CourseVek.end())
	{
		os << "Ne postoji kurs sa datim username-om" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		system("CLS");
		return;

	}
	std::string newType;
	os << "Unesite novi tip:"; is >> newType;
	(*findCourse).SetType(newType);
	CourseManagment::WriteAllCourses(CourseVek);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("CLS");
}