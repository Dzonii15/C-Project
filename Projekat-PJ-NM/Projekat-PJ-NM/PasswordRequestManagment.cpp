#include "PasswordRequestManagment.h"
PasswordRequestManagment::PasswordRequestManagment() :admin(""), reqUser("")
{

}
PasswordRequestManagment::PasswordRequestManagment(std::string Admin, std::string RUser) : admin(Admin), reqUser(RUser)
{

}
void PasswordRequestManagment::SetAdmin(std::string admin1)
{
	this->admin = admin1;
}
void  PasswordRequestManagment::SetUser(std::string user)
{
	this->reqUser = user;
}
std::string  PasswordRequestManagment::getAdmin()const
{
	return this->admin;
}
std::string  PasswordRequestManagment::getUser()const
{
	return this->reqUser;
}
void PasswordRequestManagment::sendRequest(std::string newPass)
{
	UserDirectoryManagment directory;
	directory.CreateUserDir(this->admin);
	std::string filePath = directory.GetPath() + "PasswordRequest.txt";
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		outFile << this->reqUser << "," << newPass << '\n';
	}
	else
		throw std::exception("Something went wrong");
}
std::vector<std::pair<std::string, std::string>> PasswordRequestManagment::readRequests(std::ifstream& inFile)
{
	std::string user, pass;
	std::vector<std::pair<std::string, std::string>> ReqVek;
	while (inFile.good())
	{
		std::getline(inFile, user, ',');
		std::getline(inFile, pass, '\n');
		inFile >> std::ws;
		ReqVek.push_back({ user,pass });

	}
	return ReqVek;
}
void PasswordRequestManagment::WriteRequests(const std::vector<std::pair<std::string, std::string>>& reqVek)
{
	UserDirectoryManagment directory;
	directory.CreateUserDir(this->admin);
	std::string filePath = directory.GetPath() + "PasswordRequest.txt";
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		for (auto element : reqVek)
		{
			outFile << element.first << "," << element.second << std::endl;
		}
	}
	else
		throw std::exception("Something went wrong");
}