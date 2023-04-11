#pragma once
#include "Student.h"
#include "Professor.h"
#include "Administrator.h"
class AccountManagment
{
public:
	//Funkcija upisuje sve korisnike u fajl
	static void WriteAllUsers(const std::vector<User*>&);
	//Funkcija ucitava sve korisnike iz fajla
	static std::vector<User*> ReadAllUsers();
	//Ucitava jednog korisnika
	static User* ReadOneUser(std::ifstream&);
	//Upisuje korisnika na kraj
	static void WriteUserAtEnd(const User*);
};