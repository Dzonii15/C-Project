#include "InboxInteraction.h"
void InboxInteraction::FlagProfessor(std::string prof, std::string student)
{
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(prof);
	std::string filePath = (scanner.GetPath() + "StudentMessages.txt");
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << student << std::endl;
		outFile.close();
	}
}
std::vector<std::string> InboxInteraction::ReadFlags(std::string prof)
{
	std::vector <std::string> flags;
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(prof);
	std::string filePath = (scanner.GetPath() + "StudentMessages.txt");
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile.is_open())
	{
		std::string User;
		while (inFile.good())
		{
			std::getline(inFile, User, '\n');
			inFile >> std::ws;
			flags.push_back(User);
		}
		inFile.close();
	}
	return flags;
}
void InboxInteraction::WriteAllFlags(std::string prof, const std::vector<std::string>& FlagVekt)
{
	std::vector <std::string> flags;
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(prof);
	std::string filePath = (scanner.GetPath() + "StudentMessages.txt");
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		for (auto flag : FlagVekt)
		{
			outFile << flag << std::endl;
		}
		outFile.close();
	}
}
void InboxInteraction::chat(std::ostream& os, std::istream& is, const User* korisnik, const std::vector<User*>& UserVek, const std::vector<Course>& CourseVek)
{

	const Student* student = dynamic_cast<const Student*>(korisnik);
	if (student != nullptr)
	{
		int ChatOption;
		os << "Da li zelite poslati poruku prijatelju ili profesoru kursa kojeg vi pohadjate?" << std::endl;
		os << "                           (1)Prijatelju | (2) Profesoru" << std::endl;
		os << "Opcija: "; is >> ChatOption;
		system("CLS");
		if (ChatOption == 1)
		{
			int FriendOption;
			os << "Da li zelite prvo pregledati vasu listu prijatelja?" << std::endl;
			os << "                       (1)Da | (2)Ne" << std::endl;
			os << "Opcija: "; is >> FriendOption;
			system("CLS");
			if (FriendOption == 1)
				student->printFriends(os);
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			system("CLS");
			std::string UserName;
			os << "Unesite username prijatelja:";
			std::getchar();
			std::getline(is, UserName);
			if (student->CheckFriend(UserName))
			{
				InboxFileManagment scanner(student->GetUserName(), UserName);
				scanner.SendMessage(os, is);
			}
			else
			{
				os << "Dati korisnik vam nije prijatelj" << std::endl;
				os << "Prekid akcije!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				system("CLS");
				return;
			}


		}
		else if (ChatOption == 2)
		{
			int CheckOption;
			std::vector<std::string> Courses = student->GetCourses();
			os << "Da li zelite prvo pregledati listu kurseva koje pohadjate?" << std::endl;
			os << "                       (1)Da | (2)Ne" << std::endl;
			os << "Opcija: "; is >> CheckOption;
			system("CLS");
			if (CheckOption == 1)
			{
				student->PrintCourses(os);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			system("CLS");
			std::getchar();
			std::string CourseName;
			os << "Unesite kurs kojem profesoru zelite poslati poruku:" << std::endl;
			std::cout << "Opcija:"; std::getline(is, CourseName);

			auto CourseFinder = std::find(Courses.begin(), Courses.end(), CourseName);
			if (CourseFinder == Courses.end())
			{
				os << "Neuspjesan unos!" << std::endl;
				os << "Prekid akcije" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				system("CLS");
				return;
			}
			auto ProfFinder = std::find_if(CourseVek.begin(), CourseVek.end(), [CourseName](const Course& element) {return element.GetName() == CourseName; });
			if (ProfFinder == CourseVek.end())
				throw std::exception("Error");
			InboxFileManagment scanner(student->GetUserName(), (*ProfFinder).GetProfessor());
			scanner.SendMessage(os, is);
			std::vector<std::string> flags = InboxInteraction::ReadFlags((*ProfFinder).GetProfessor());
			auto checkifalreadyexists = find(flags.begin(), flags.end(), student->GetUserName());
			if (checkifalreadyexists == flags.end())
				InboxInteraction::FlagProfessor((*ProfFinder).GetProfessor(), student->GetUserName());

		}
	}
	else
	{
		const Professor* prof = dynamic_cast<const Professor*>(korisnik);
		if (prof != nullptr)
		{
			int ChatOption;
			os << "Da li zelite poslati poruku prijatelju ili odgovoriti studentima na poruke?" << std::endl;
			os << "                           (1)Prijatelju | (2) Studentima" << std::endl;
			os << "Opcija: "; is >> ChatOption;
			system("CLS");
			if (ChatOption == 1)
			{
				int FriendOption;
				os << "Da li zelite prvo pregledati vasu listu prijatelja?" << std::endl;
				os << "                       (1)Da | (2)Ne" << std::endl;
				os << "Opcija: "; is >> FriendOption;
				if (FriendOption == 1)
					prof->printFriends(os);
				std::this_thread::sleep_for(std::chrono::milliseconds(5000));
				system("CLS");
				std::string UserName;
				os << "Unesite username prijatelja:";
				std::getchar();
				std::getline(is, UserName);
				if (prof->CheckFriend(UserName))
				{
					InboxFileManagment scanner(prof->GetUserName(), UserName);
					scanner.SendMessage(os, is);
				}
				else
				{
					os << "Dati korisnik vam nije prijatelj" << std::endl;
					os << "Prekid akcije!" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					system("CLS");
					return;
				}
			}
			else if (ChatOption == 2)
			{
				std::vector<std::string> flags = InboxInteraction::ReadFlags(prof->GetUserName());
				std::vector<std::string>temp;
				if (flags.empty())
				{
					os << "Trenutno nemate poruka od studenata!" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					system("CLS");
					return;
				}
				for (auto element : flags)
				{
					int AnswerOption;
					os << "Da li zelite odgovoriti na poruku: " << element << "?" << std::endl;
					os << "(1)Da | (2)Ne" << std::endl;
					os << "Opcija:"; is >> AnswerOption;
					system("CLS");
					std::getchar();
					if (AnswerOption == 1)
					{
						InboxFileManagment scanner(prof->GetUserName(), element);
						scanner.SendMessage(os, is);
						temp.push_back(element);
					}
				}

				for (auto deleteFlag : temp)
				{
					auto FlagFinder = find(flags.begin(), flags.end(), deleteFlag);
					flags.erase(FlagFinder);
				}
				InboxInteraction::WriteAllFlags(prof->GetUserName(), flags);

			}
		}
	}
	system("CLS");

}
void InboxInteraction::filterChat(std::ostream& os, std::istream& is, const User* korisnik)
{
	std::string subString;
	std::string UName;
	std::getchar();
	os << "Unesite rijec po kojoj ce te filtrirati inbox:";
	std::getline(is, subString);
	os << "Unesite korisnika ciji chat zelite filtrirati:";
	std::getline(is, UName);
	os << "Poruke koje u sebi sadrze unijeti string " << subString << ":" << std::endl;
	InboxFileManagment scanner(korisnik->GetUserName(), UName);
	scanner.filterInbox(os, subString);
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	system("CLS");

}