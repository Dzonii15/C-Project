#include "User.h"

User::User() :accountInfo(), name(""), surname(""), JMBG("")
{
}
User::User(std::string UserName, std::string Password, std::string Name, std::string Surname, std::string jmbg) : accountInfo(UserName, Password), name(Name), surname(Surname), JMBG(jmbg)
{
	FriendAccountManagment Scanner;
	Scanner.SetPerson1(this->accountInfo.GetUserName());
	Scanner.ReadFriends(this->friendList);
}
void User::SetName(std::string Name)
{
	this->name = Name;
}
void User::SetSurname(std::string Surname)
{
	this->surname = Surname;
}
void User::SetJMBG(std::string jmbg)
{
	this->JMBG = jmbg;
}
std::string User::GetUserPassword()const
{
	return this->accountInfo.GetPassword();
}
std::string User::GetUserName()const
{
	return this->accountInfo.GetUserName();
}
std::string User::GetName()const
{
	return this->name;
}
std::string User::GetSurname()const
{
	return this->surname;
}
std::string User::GetJMBG()const
{
	return this->JMBG;
}
std::vector<std::string>& User::GetFriends()
{
	return this->friendList;
}
bool User::CheckAccountValidity(const AccountTraits& other) const
{
	return other == this->accountInfo;
}
void User::ChangePassword(std::string newPass)
{

	this->accountInfo.SetPassword(newPass);

}
bool User::CheckFriend(std::string UName)const
{

	auto it = find(this->friendList.begin(), this->friendList.end(), UName);
	return it != this->friendList.end();
}
void User::printFriends(std::ostream& os)const
{
	for (auto el : this->friendList)
		os << el << std::endl;
}
