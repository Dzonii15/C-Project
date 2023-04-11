#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <exception>
#include "GlobalFunctions.h"
class InboxFileManagment
{
private:
	//ImeFajla : PrviUsername + DrugiUserName + Inbox.txt
	std::string firstPerson;
	std::string secondPerson;
	std::string filePath;

public:
	InboxFileManagment(std::string, std::string);
	void SendMessage(std::ostream&, std::istream&);
	void ShowInbox(std::ostream&);
	void filterInbox(std::ostream&, std::string);

};