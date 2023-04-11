#pragma once
#include <chrono>
#include <thread>
#include "AccountTraits.h"
#include "InboxFileManagment.h"
#include "RequestsFileManagment.h"
#include "Course.h"
#include "CourseRequestManagment.h"
#include "CourseManagment.h"
#include "CourseUserManagment.h"
#include "FinishedCoursesManagment.h"

class User
{
protected:
	std::string name;
	std::string surname;
	std::string JMBG;
	AccountTraits accountInfo;
	std::vector<std::string>friendList;
public:
	User();
	User(std::string, std::string, std::string, std::string, std::string);
	virtual ~User() {}
	//Seteri
	void SetName(std::string);
	void SetSurname(std::string);
	void SetJMBG(std::string);
	void ChangePassword(std::string);

	//Geteri
	std::string GetUserPassword()const;
	std::string GetUserName()const;
	std::string GetName()const;
	std::string GetSurname()const;
	std::string GetJMBG()const;
	std::vector<std::string>& GetFriends();
	virtual std::vector<std::string> GetCourses()const = 0;
	virtual std::string GetType()const = 0;
	virtual User* clone()const = 0;

	void printFriends(std::ostream&)const;
	bool CheckAccountValidity(const AccountTraits&) const;

	//FriendInteraction
	bool CheckFriend(std::string)const;
};