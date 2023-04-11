#include "RequestInteraction.h"
void RequestInteraction::SendFriendRequest(std::ostream& os, std::istream& is, User* korisnik, std::vector<User*> UserVec)
{
	int opcija;
	std::string FUName;
	os << "Da li zelite pregledati username svih dostupnih korisnika?" << std::endl;
	os << "                       (1)Da | (2)Ne" << std::endl;
	os << "Opcija:"; is >> opcija;
	int printcounter = 0;
	if (opcija == 1)
	{
		for (auto element : UserVec)
		{
			printcounter++;
			os << element->GetUserName() << " | ";
			if (printcounter == 5)
			{
				os << std::endl << std::endl;
			}
		}
	}
	std::getchar();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	system("CLS");
	os << std::endl;
	os << "Unesi username korisnika koga zelite dodati:";
	std::getline(is, FUName);
	auto it = find_if(UserVec.begin(), UserVec.end(), [FUName](const User* korisnik)
		{
			return korisnik->GetUserName() == FUName;
		});
	if (it != UserVec.end())
	{
		if (korisnik->GetType() == "Student" && ((*it)->GetType() == "Professor" || (*it)->GetType() == "Administrator"))
		{
			os << "Ne mozete poslati njima zahtjev za prijateljstvo!" << std::endl;
			os << "Prekid akcije" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			return;
		}
		RequestsFileManagment scanner(korisnik->GetUserName(), FUName);
		scanner.SendRequest();
	}
	else
	{
		os << "Neuspjesan unos, korisnik sa unesenim username-om ne postoji!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	os << "Korisniku je poslan zahtjev!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");
}
void RequestInteraction::AcceptFriendRequest(std::ostream& os, std::istream& is, User* korisnik, std::vector<User*> UserVek)
{
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(korisnik->GetUserName());
	RequestsFileManagment scanner2(korisnik->GetUserName(), "");
	std::string temp = scanner.GetPath();
	std::string FilePath = temp + korisnik->GetUserName() + "Requests.txt";
	std::vector<std::string>FRequests;
	std::vector<std::string>tempvector;
	std::ifstream InFile(FilePath, std::ios::in);
	if (InFile.is_open())
	{
		if (scanner2.CheckRequest(InFile))
		{
			FRequests = scanner2.LoadRequests(InFile);
		}
		else
		{
			os << "Trenutno nemate zahtjeva za prijateljstvo";
			os << "Prekid akcije." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			return;
		}
		InFile.close();
	}
	else
		throw std::exception("Unable to open file");

	for (auto it = FRequests.begin(); it != FRequests.end(); it++)
	{
		auto iterator = find_if(UserVek.begin(), UserVek.end(), [it](const User* korisnik) {return *it == korisnik->GetUserName(); });
		if (iterator == UserVek.end())
		{
			tempvector.push_back(*it);
		}
		else
		{
			int opcija;
			os << "Da li zelite prihvatiti zahtjev od korisnika sa username-om: " << *it << std::endl;
			os << "        (1)Da | (2)Ne | (3)Nisam odlucio" << std::endl;
			os << "Opcija:"; is >> opcija;
			if (opcija == 1)
			{
				FriendAccountManagment scannerf(korisnik->GetUserName(), *it);
				scannerf.AddFriend();
				tempvector.push_back(*it);
			}
			else if (opcija == 2)
			{
				tempvector.push_back(*it);
			}
			system("CLS");
		}
	}
	for (auto element : tempvector)
	{
		auto it = std::find(FRequests.begin(), FRequests.end(), element);
		FRequests.erase(it);
	}
	scanner2.writeAllRequests(FilePath, FRequests);
	system("CLS");


}
void RequestInteraction::SendCourseEnrollmentRequest(std::ostream& os, std::istream& is, Student* student, std::vector<Course>& AllCourses)
{
	int option;
	std::string CourseOption;
	std::vector<std::string> courses = student->GetCourses();
	os << "Da li zelite da prvo pregledate kurseve na koje se mozete prijaviti" << std::endl;
	os << "                                (1)Da|(2)Ne" << std::endl;
	is >> option;
	if (option == 1)
	{
		for (auto element : AllCourses)
			os << element.GetName() << " ";
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		system("CLS");
	}
	os << std::endl;
	os << "Unesite kurs na koji se zelite prijaviti:";
	std::getchar();
	std::getline(is, CourseOption);
	auto iterator = find(courses.begin(), courses.end(), CourseOption);
	if (iterator != courses.end())
	{
		os << "Vec ste prijavljeni na dati kurs!" << std::endl;
		os << "Prekid akcije" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	auto it = std::find_if(AllCourses.begin(), AllCourses.end(),
		[CourseOption](const Course& element)
		{
			return CourseOption == element.GetName();
		});
	if (it == AllCourses.end())
	{
		os << "Neispravan unos!" << std::endl << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	CourseRequestManagment scanner((*it).GetProfessor(), student->GetUserName(), (*it).GetName());
	scanner.CourseSignUp();
	os << "Prijava je poslata profesoru nadleznom za kurs!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");

}



void RequestInteraction::AcceptStudentToCourse(std::ostream& os, std::istream& is, Professor* prof, std::vector<User*>& Vekt, std::vector<Course>& CourseVec)
{
	//Definisanje puta do zahtjeva za prijavu na kurs
	UserDirectoryManagment scanner3;
	scanner3.CreateUserDir(prof->GetUserName());
	std::string FilePath = (scanner3.GetPath() + prof->GetUserName() + "CourseRequest.txt");

	//Vektor gdje ce se smjestiti preduslovi datog kursa
	std::vector<Precondition*> preconditions;


	//Definisanje skenera za rad sa prijavama na kurs
	CourseRequestManagment scanner;
	scanner.SetProfessor(prof->GetUserName());
	//Ucitavanje zahtjeva za kurs
	std::vector<std::pair<std::string, std::string>>CourseRequests = scanner.LoadCourseRequests(FilePath);
	std::vector<std::pair<std::string, std::string>>tempvect;

	if (CourseRequests.empty())
	{
		os << "Trenutno nemate zahtjeva za prijavu na kurseve" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	else
	{
		int Option;
		//Glavna perlja koja prolazi kroz zahtjeve
		for (auto element : CourseRequests)
		{
			//Provjera da li je slucajno dati kurs ili dati korisnik izbrisan
			auto iterator1 = find_if(CourseVec.begin(), CourseVec.end(), [element](const Course& kurs) {return element.second == kurs.GetName(); });
			auto iterator2 = find_if(Vekt.begin(), Vekt.end(), [element](const User* korisnik) {return element.first == korisnik->GetUserName(); });

			if (iterator1 == CourseVec.end() || iterator2 == Vekt.end())
			{
				tempvect.push_back(element);
			}
			else
			{
				os << "Prikaz zahtjeva:" << std::endl;
				os << "Student sa usernameom: " << element.first << " zeli pristupiti kursu " << element.second << std::endl;
				os << "Da li zelite obraditi zahtjev?" << std::endl;
				os << "        (1)Da | (2)Ne" << std::endl;
				os << "Opcija:"; is >> Option;
				if (Option == 1)
				{
					CoursePreconditionManagment scanPrec(element.second);
					scanPrec.ReadCoursePreconditions(preconditions);
					//Trazi studenta na osnovu datog username-a
					auto it = find_if(Vekt.begin(), Vekt.end(), [element](const User* x)
						{
							return element.first == x->GetUserName() && x->GetType() == "Student";
						});
					//Provjera da li studenat ispunjava uslove za dati kurs
					int ensurance = 1;
					Student* student = dynamic_cast<Student*>(*it);
					for (auto prec : preconditions)
					{
						if (!prec->CoursePrecondition(student))
							ensurance = 0;
					}
					//Ako ispunjava upisuje se na kurs
					if (ensurance == 1)
					{
						CourseManagment Coursescanner(element.second);
						//Upisuje studenta u direktorijum za kurseve da ga pohadja
						Coursescanner.CourseStudentUpdate(element.first);
						CourseUserManagment Userscanner(element.first, element.second);
						//Upisuje kurs u direktorijum studenta da ga pohadja
						Userscanner.UpdateUserCourseList();
						tempvect.push_back(element);
					}
					else
					{
						//Ako ne ispunjava uslov
						tempvect.push_back(element);
					}
				}
				system("CLS");
			}
		}
		//Brisemo obradjene zahtjeve
		for (auto element : tempvect)
		{
			auto it = std::find(CourseRequests.begin(), CourseRequests.end(), element);
			CourseRequests.erase(it);
		}
		//Upisujemo neobradjene
		scanner.writeAllRequests(FilePath, CourseRequests);
		for (auto prec : preconditions)
			delete prec;
	}


}
void RequestInteraction::passwordChangeRequest(std::ostream& os, std::istream& is, User* korisnik, const std::vector<User*>& UserVek)
{
	std::string newPass;
	std::string oldPass;
	std::string jmbgCheck;
	int PassChangeOption;
	os << "Da li ste zaboravili staru sifru?" << std::endl;
	os << "             (1)Da | (2)Ne" << std::endl;
	os << "Opcija:"; is >> PassChangeOption;
	if (PassChangeOption == 1)
	{
		os << "Unesite svoj JBMG kao validaciju:";
		is >> jmbgCheck;
		if (jmbgCheck != korisnik->GetJMBG())
		{
			os << "Niste unijeli dati podatak dobro" << std::endl;
			os << "Prekid akcije!" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			return;
		}
	}
	else
	{
		os << "Unesite staru sifru za validaciju:";
		is >> oldPass;
		if (oldPass != korisnik->GetUserPassword())
		{
			os << "Niste unijeli dati podatak dobro" << std::endl;
			os << "Prekid akcije!" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			system("CLS");
			return;
		}
	}
	os << "Unesite sifru koju zelite postaviti kao novu:";
	is >> newPass;
	auto it = std::find_if(UserVek.begin(), UserVek.end(), [](const User* korisnik) {return korisnik->GetType() == "Administrator"; });
	if (it == UserVek.end())
		throw std::exception("Something went wrong");
	PasswordRequestManagment passScaner((*it)->GetUserName(), korisnik->GetUserName());
	passScaner.sendRequest(newPass);
	os << "Zahtjev je poslan administratoru sistema!" << std::endl;
	os << "Javicemo vam ako je zahtjev prihvacen!" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");

}