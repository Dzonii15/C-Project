#pragma once
#include <vector>
#include "FriendAccountManagment.h"
#include "GlobalFunctions.h"

//Klasa se bavi fajlom za zahtjeve za prijateljstvo 
class RequestsFileManagment
{
private:
	//Dva korisnika koja su ukljucena u radnju
	std::string firstUser;
	std::string secondUser;
public:
	//Konstruktor
	RequestsFileManagment(std::string, std::string);

	//Ukoliko hocu da posaljem,otvaram request datoteku od trazenog prijatelja i dodajem na kraj
	void SendRequest();
	//Provjeravam licnu datoteku ukoliko imam zahtjeva
	bool CheckRequest(std::ifstream&);

	//Ucitavam sve zahtjeve
	std::vector<std::string> LoadRequests(std::ifstream&);
	//Ispisujem zahtjeve u fajl
	void writeAllRequests(std::string, std::vector<std::string>&);
	//Ispisujem sve zahtjeve
	void PrintFriendRequests(std::ostream&);

};