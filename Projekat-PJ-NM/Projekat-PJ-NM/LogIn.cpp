#include "LogIn.h"
bool LogIn::Login(std::ostream& os, std::istream& is, std::vector<User*>& UserVec, User** korisnik)
{
	std::string UserName, Password;
	if (UserVec.empty())
	{
		std::string username, password, name, surname, jmbg;
		os << "Dobrodosli u prvu prijavu na sistem!" << std::endl;
		os << "Duzni ste da napravite administratora sistema! " << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		std::getchar();
		os << "Unesite ime administratora:"; is >> name;
		os << "Unesite prezime administratora:"; is >> surname;
		os << "Unesite JMBG administratora:"; is >> jmbg;
		os << "Unesite username administratora:"; std::getline(is, username);
		os << "Unesite sifru administratora:"; is >> password;
		*korisnik = new Administrator(username, password, name, surname, jmbg);
		Administrator* temp = new Administrator(username, password, name, surname, jmbg);
		UserVec.push_back(temp);
		AccountManagment::WriteUserAtEnd(UserVec[0]);

	}
	else
	{

		std::vector<User*>::iterator it;
		int option;
		os << "Unesite tip naloga na koji se hocete prijaviti:" << std::endl;
		os << "(1)Student" << std::endl;
		os << "(2)Professor" << std::endl;
		os << "(3)Administrator" << std::endl;
		os << "Unesite opciju:"; is >> option;
		system("CLS");
		os << "Imate 3 pokusaja da se ulogujete!" << std::endl;
		int i = 0;
		std::getchar();
		while (i < 3)
		{
			os << "Unesite username:";
			std::getline(is, UserName);
			os << "Unesite password:";
			std::getline(is, Password);
			AccountTraits acc(UserName, Password);
			it = find_if(UserVec.begin(), UserVec.end(), [acc](const User* korisnik)
				{return korisnik->CheckAccountValidity(acc); });
			if (it != UserVec.end())
				break;
			auto iterator = it = find_if(UserVec.begin(), UserVec.end(), [UserName](const User* korisnik)
				{return korisnik->GetUserName() == UserName; });
			if (iterator == UserVec.end() || i > 0)
			{
				i++;
				os << "Neuspjesna prijava!" << std::endl;
				os << "Ostalo je jos " << 3 - i << " pokusaja!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1500));
				system("CLS");
			}
			else
			{
				UserDirectoryManagment userdir;
				userdir.CreateUserDir(UserName);
				std::string filePath = userdir.GetPath() + "PasswordChange.txt";
				std::ifstream inFile(filePath, std::ios::in);
				if (!GlobalFunctions::IsFileEmpty(inFile))
				{
					inFile.seekg(0, std::ios::beg);
					int check;
					inFile >> check;
					if (check == 1)
					{
						os << "Vas zahtjev za promjenu je prihvacen molimo vas unesite novu sifru!" << std::endl;
						i++;
						os << "Ostalo je jos " << 3 - i << " pokusaja!" << std::endl;
						std::remove(filePath.c_str());
						std::this_thread::sleep_for(std::chrono::milliseconds(1500));
						system("CLS");
					}
					else if (check == 0)
					{
						os << "Vas zahtjev nije prihvacen moracete unijeti staru sifru" << std::endl;
						i++;
						os << "Ostalo je jos " << 3 - i << " pokusaja!" << std::endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(1500));
						system("CLS");
					}
					inFile.close();
					std::ofstream cleaner(filePath, std::ios::trunc);
					cleaner.close();


				}
				else
				{
					i++;
					os << "Neuspjesna prijava!" << std::endl;
					os << "Ostalo je jos " << 3 - i << " pokusaja!" << std::endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(1500));
					system("CLS");
				}
			}
		}

		if (i == 3)
		{
			os << "Iskoristen maksimalan broj prijava!" << std::endl;
			os << "Prekid akcije!" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			system("CLS");
			return false;
		}
		if (option == 1)
		{
			if ((*it)->GetType() != "Student")
			{
				os << "Vas nalog ne odgovara odabranom tipu!" << std::endl;
				os << "Prekid akcije!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("CLS");
				return false;
			}
			Student* user = dynamic_cast<Student*>(*it);
			*korisnik = new Student(*user);
		}
		else if (option == 2)
		{
			if ((*it)->GetType() != "Professor")
			{
				os << "Vas nalog ne odgovara odabranom tipu!" << std::endl;
				os << "Prekid akcije!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("CLS");
				return false;
			}
			Professor* user = dynamic_cast<Professor*>(*it);
			*korisnik = new Professor(*user);
		}
		else if (option == 3)
		{
			if ((*it)->GetType() != "Administrator")
			{
				os << "Vas nalog ne odgovara odabranom tipu!" << std::endl;
				os << "Prekid akcije!" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				system("CLS");
				return false;
			}
			Administrator* user = dynamic_cast<Administrator*>(*it);
			*korisnik = new Administrator(*user);
		}

		return true;
	}

}