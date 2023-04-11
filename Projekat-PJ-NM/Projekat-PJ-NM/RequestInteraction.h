#pragma once
#include "Student.h"
#include "Professor.h"
#include "CoursePreconditionManagment.h"
#include "PasswordRequestManagment.h"
class RequestInteraction
{
public:
	//User option
	static void SendFriendRequest(std::ostream&, std::istream&, User*, std::vector<User*>);
	static void AcceptFriendRequest(std::ostream&, std::istream&, User*, std::vector<User*>);

	//Student option
	static void SendCourseEnrollmentRequest(std::ostream&, std::istream&, Student*, std::vector<Course>&);

	//Professor option

	static void AcceptStudentToCourse(std::ostream&, std::istream&, Professor*, std::vector<User*>&, std::vector<Course>&);

	static void passwordChangeRequest(std::ostream&, std::istream&, User*, const std::vector<User*>&);
};