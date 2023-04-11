#pragma once
#include "AccoutManagment.h"
class InboxInteraction
{
public:
	static void FlagProfessor(std::string, std::string);
	static std::vector<std::string> ReadFlags(std::string);
	static void WriteAllFlags(std::string, const std::vector<std::string>&);
	static void chat(std::ostream&, std::istream&, const User*, const std::vector<User*>&, const std::vector<Course>&);
	static void filterChat(std::ostream&, std::istream&, const User*);
};