#pragma once
#include <iostream>
#include <fstream>
#include <exception>
#include "UserDirectoryManagment.h"
//Klasa se bavi fajlom za listu prijatelja datog korisnika
class FriendAccountManagment
{
private:
	//Osobe koje su u kontaktu
	std::string Person1;
	std::string Person2;
public:
	//Konstruktori
	FriendAccountManagment();
	FriendAccountManagment(std::string, std::string);

	//Seteri
	void SetPerson1(std::string);
	void SetPerson2(std::string);

	//Dodaje prijatelja na kraj fajla za oba korisnika
	void AddFriend();
	//Cita sve prijatelje datog korisnika
	void ReadFriends(std::vector<std::string>&);
	//Upisuje sve prijatelje u fajl datog korisnika
	void WriteAllFriends(std::vector <std::string>&, std::ofstream&);
	//Brise prijatelja iz liste prijatelja
	void DeleteFromFriendList();
};