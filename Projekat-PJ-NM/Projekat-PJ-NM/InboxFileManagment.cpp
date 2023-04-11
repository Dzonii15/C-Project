#include "InboxFileManagment.h"
InboxFileManagment::InboxFileManagment(std::string FUname, std::string SUname) :firstPerson(FUname), secondPerson(SUname)
{
	namespace fs = std::filesystem;
	std::string directory = fs::current_path().string() + "/Inbox/";
	if (!fs::exists(directory))
		fs::create_directories(directory);
	this->filePath = directory;
	if (FUname < SUname)
		this->filePath += FUname + SUname;
	else
		this->filePath += SUname + FUname;
	this->filePath += "Inbox.txt";
}
void InboxFileManagment::SendMessage(std::ostream& os, std::istream& is)
{
	std::string Msg;
	std::ofstream InboxFile(this->filePath, std::ios::app);
	if (InboxFile.is_open()) {
		this->ShowInbox(os);
		os << std::endl;
		os << "Unesite poruku ovdje:";
		std::getline(is, Msg);
		InboxFile << this->firstPerson << ":" << Msg << '\n';
		InboxFile.close();
	}
	else
		throw std::exception("Unable to open file");

}
void InboxFileManagment::ShowInbox(std::ostream& os)
{
	std::string Msg;
	std::ifstream InboxFile(this->filePath, std::ios::in);
	if (InboxFile.is_open())
	{
		if (GlobalFunctions::IsFileEmpty(InboxFile))
		{
			os << "Inbox je prazan" << std::endl;
		}
		else
		{
			InboxFile.seekg(0, std::ios::beg);
			while (InboxFile.good())
			{
				std::getline(InboxFile, Msg);
				os << Msg << std::endl;
			}
		}
		InboxFile.close();
	}
	else
		throw std::exception("Unable to open file");
}
void InboxFileManagment::filterInbox(std::ostream& os, std::string filterWord)
{
	std::ifstream InboxFile(this->filePath, std::ios::in);
	if (InboxFile.good())
	{
		std::string temp;
		while (InboxFile.good())
		{
			std::getline(InboxFile, temp, '\n');
			if (temp.find(filterWord) != std::string::npos)
				os << temp << std::endl;
		}

	}
}