#pragma once
#include "UserDirectoryManagment.h"
#include <fstream>
class PasswordRequestManagment
{
	std::string admin;
	std::string reqUser;
public:
	PasswordRequestManagment();
	PasswordRequestManagment(std::string, std::string);
	void SetAdmin(std::string);
	void SetUser(std::string);
	std::string getAdmin()const;
	std::string getUser()const;
	void sendRequest(std::string);
	std::vector<std::pair<std::string, std::string>>readRequests(std::ifstream&);
	void WriteRequests(const std::vector<std::pair<std::string, std::string>>& reqVek);
};