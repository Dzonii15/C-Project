#include "AccoutManagment.h"

void AccountManagment::WriteAllUsers(const std::vector<User*>& UserVec)
{
	UserDirectoryManagment scanner;
	std::string filePath = (scanner.GetPath() + "Users.csv");
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		for (auto element : UserVec)
		{
			outFile << element->GetUserName() << ',' << element->GetUserPassword() << ',' << element->GetName() << ',' << element->GetSurname() << ',' << element->GetJMBG() << ',' << element->GetType() << '\n';
		}
		outFile.close();
	}
	else
		throw std::exception("Unable to open file");
}
User* AccountManagment::ReadOneUser(std::ifstream& inFile)
{
	std::string userName, password, name, surname, jmbg, type;
	std::getline(inFile, userName, ',');
	std::getline(inFile, password, ',');
	std::getline(inFile, name, ',');
	std::getline(inFile, surname, ',');
	std::getline(inFile, jmbg, ',');
	std::getline(inFile, type, '\n');
	inFile >> std::ws;
	if (type == "Student")
		return new Student(userName, password, name, surname, jmbg);
	else if (type == "Professor")
		return new Professor(userName, password, name, surname, jmbg);
	else return new Administrator(userName, password, name, surname, jmbg);
}
std::vector<User*> AccountManagment::ReadAllUsers()
{
	UserDirectoryManagment scanner;
	std::string filePath = (scanner.GetPath() + "Users.csv");
	std::vector<User*> UserVec;
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile.is_open())
	{
		while (inFile.good())
		{
			UserVec.push_back(AccountManagment::ReadOneUser(inFile));
		}
		inFile.close();
	}
	return UserVec;
}
void AccountManagment::WriteUserAtEnd(const User* korisnik)
{
	UserDirectoryManagment scanner;
	std::string filePath = (scanner.GetPath() + "Users.csv");
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << korisnik->GetUserName() << ',' << korisnik->GetUserPassword() << ',' << korisnik->GetName() << ',' << korisnik->GetSurname() << ',' << korisnik->GetJMBG() << ',' << korisnik->GetType() << '\n';
		outFile.close();
	}
	else throw std::exception("Unable to open file");
}