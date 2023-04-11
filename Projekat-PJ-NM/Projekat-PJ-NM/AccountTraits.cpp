#include "AccountTraits.h"

AccountTraits::AccountTraits() :userName(""), password("")
{
}
AccountTraits::AccountTraits(std::string UName, std::string Password) : userName(UName), password(Password)
{
}
void AccountTraits::SetUserName(std::string UName)
{
	this->userName = UName;
}
void AccountTraits::SetPassword(std::string Password)
{
	this->password = Password;
}
std::string AccountTraits::GetUserName()const
{
	return this->userName;
}
std::string AccountTraits::GetPassword()const
{
	return this->password;
}
bool AccountTraits::operator==(const AccountTraits& other) const
{
	return (this->password == other.password && this->userName == other.userName);
}