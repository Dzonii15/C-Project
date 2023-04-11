#include "RequestsFileManagment.h"


RequestsFileManagment::RequestsFileManagment(std::string fname, std::string sname) :firstUser(fname), secondUser(sname)
{

}
void RequestsFileManagment::SendRequest()
{
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(this->secondUser);
	std::string temp = scanner.GetPath();
	std::string FilePath = temp + this->secondUser + "Requests.txt";
	std::ofstream ReqFile(FilePath, std::ios::app);
	if (ReqFile.is_open())
	{
		ReqFile << this->firstUser << '\n';
		ReqFile.close();
	}
	else
		throw std::exception("Unable to open file");
}
bool RequestsFileManagment::CheckRequest(std::ifstream& inFile)
{
	if (GlobalFunctions::IsFileEmpty(inFile))
	{
		return false;
	}
	inFile.seekg(0, std::ios::beg);
	return true;
}
std::vector<std::string>  RequestsFileManagment::LoadRequests(std::ifstream& inFile)
{
	std::string Request;
	std::vector<std::string> requests;
	while (inFile.good())
	{
		std::getline(inFile, Request, '\n');
		requests.push_back(Request);
		inFile >> std::ws;
	}
	return requests;
}
void RequestsFileManagment::writeAllRequests(std::string path, std::vector<std::string>& FRequests)
{
	std::ofstream outFile(path, std::ios::out);
	if (FRequests.empty())
	{

		std::ofstream ofs;
		ofs.open(path, std::ofstream::trunc);
		if (ofs.is_open())
			ofs.close();
		else throw std::exception("Unable to open file");

	}
	else {
		if (outFile.is_open())
		{
			for (auto element : FRequests)
			{
				outFile << element << '\n';
			}
			outFile.close();
		}
	}
}

void RequestsFileManagment::PrintFriendRequests(std::ostream& os)
{
	UserDirectoryManagment scanner;
	scanner.CreateUserDir(this->firstUser);
	std::string temp = scanner.GetPath();
	std::string FilePath = temp + this->firstUser + "Requests.txt";
	std::ifstream InFile(FilePath, std::ios::in);
	std::vector<std::string> FRequests;
	if (InFile.is_open())
	{
		FRequests = this->LoadRequests(InFile);
		InFile.close();
	}
	for (auto element : FRequests)
		os << element << std::endl;
}