#pragma 
#include "AccoutManagment.h"
#include "CoursePreconditionManagment.h"
#include "PasswordRequestManagment.h"
#include "CourseInteraction.h"
#include "GraphSupport.h"
class AdministratorInteraction
{
public:
	static void CreateAccount(std::ostream&, std::istream&, std::vector<User*>&);
	static void DeleteAccount(std::ostream&, std::istream&, std::vector<User*>&, std::vector<Course>&);
	static void CreateCourse(std::ostream&, std::istream&, std::vector<Course>&, const std::vector<User*>&);
	static void DeleteCourse(std::ostream&, std::istream&, std::vector<Course>&, std::vector<User*>&);
	static void AcceptPasswordChange(std::ostream&, std::istream&, std::vector<User*>&, const Administrator*);
	static void CourseInspection(std::ostream&, std::istream&, const std::vector<Course>&);
	static void ModifyCourse(std::ostream&, std::istream&, std::vector<Course>&);
	static void GraphMenu(std::ostream&, std::istream&, const std::vector<User*>&);

};