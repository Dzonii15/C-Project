#include "FriendAccountManagment.h"

FriendAccountManagment::FriendAccountManagment() :Person1(""), Person2("")
{

}
FriendAccountManagment::FriendAccountManagment(std::string person1, std::string person2) : Person1(person1), Person2(person2)
{

}
void FriendAccountManagment::SetPerson1(std::string person1)
{
	this->Person1 = person1;
}
void FriendAccountManagment::SetPerson2(std::string person2)
{
	this->Person2 = person2;
}
void FriendAccountManagment::AddFriend()
{
	UserDirectoryManagment Person1Scanner;
	UserDirectoryManagment Person2Scanner;
	Person1Scanner.CreateUserDir(this->Person1);
	Person2Scanner.CreateUserDir(this->Person2);
	std::string filePath = (Person1Scanner.GetPath() + this->Person1 + "FriendList.txt");
	std::ofstream inFile(filePath, std::ios::app);
	if (inFile.is_open())
	{
		inFile << Person2 << '\n';
		inFile.close();
	}
	else
		throw std::exception("Unable to open file");
	filePath = (Person2Scanner.GetPath() + "/" + this->Person2 + "FriendList.txt");
	inFile.open(filePath, std::ios::app);
	if (inFile.is_open())
	{
		inFile << Person1 << '\n';
		inFile.close();
	}
	else
		throw std::exception("Unable to open file");
}

void FriendAccountManagment::ReadFriends(std::vector<std::string>& FriendList)
{
	UserDirectoryManagment PersonScanner;
	PersonScanner.CreateUserDir(this->Person1);
	std::string filePath = PersonScanner.GetPath() + this->Person1 + "FriendList.txt";
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile.is_open())
	{
		std::string temp;
		while (inFile.good())
		{
			std::getline(inFile, temp, '\n');
			inFile >> std::ws;
			FriendList.push_back(temp);
		}
		inFile.close();
	}

}
void FriendAccountManagment::WriteAllFriends(std::vector <std::string>& Vec, std::ofstream& outFile)
{
	for (auto element : Vec)
		outFile << element << '\n';
}
void FriendAccountManagment::DeleteFromFriendList()
{
	//Person1 osoba iz koje brisem Person2
	UserDirectoryManagment PersonScanner;
	PersonScanner.CreateUserDir(this->Person1);
	std::vector <std::string>friendList;
	this->ReadFriends(friendList);
	std::string filePath = PersonScanner.GetPath() + this->Person1 + "FriendList.txt";
	auto it = find(friendList.begin(), friendList.end(), this->Person2);
	friendList.erase(it);
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		this->WriteAllFriends(friendList, outFile);
		outFile.close();
	}




}