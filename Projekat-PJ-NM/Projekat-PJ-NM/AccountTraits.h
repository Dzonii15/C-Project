#pragma once
#include <string>
class AccountTraits
{
private:
	std::string userName;
	std::string password;
public:
	AccountTraits();
	AccountTraits(std::string, std::string);
	void SetUserName(std::string);
	void SetPassword(std::string);
	std::string GetUserName()const;
	std::string GetPassword()const;
	bool operator==(const AccountTraits&) const;
};