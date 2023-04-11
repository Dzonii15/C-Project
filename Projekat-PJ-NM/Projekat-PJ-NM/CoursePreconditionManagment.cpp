#include "CoursePreconditionManagment.h"

CoursePreconditionManagment::CoursePreconditionManagment(std::string Course1) :course(Course1)
{

}
std::string CoursePreconditionManagment::GetCourse()const
{
	return this->course;
}
void CoursePreconditionManagment::SetCourse(std::string Course1)
{
	this->course = Course1;
}
void CoursePreconditionManagment::WriteOnePrecondition(const Precondition* precondition)
{
	CourseDirectoryManagment scanner;
	scanner.CreateCourseDir(this->course);
	std::string filePath = (scanner.GetPath() + this->course + "Preconditions.txt");
	std::ofstream outFile(filePath, std::ios::app);
	if (outFile.is_open())
	{
		const NumOfCoursesPrec* prec = dynamic_cast<const NumOfCoursesPrec*>(precondition);

		if (prec != nullptr)
		{
			outFile << prec->GetType() << "," << prec->getNumOfCourse() << std::endl;
		}
		else
		{
			const HasHeFinishedCoursePrec* prec2 = dynamic_cast<const HasHeFinishedCoursePrec*>(precondition);

			if (prec2 != nullptr)
			{
				outFile << prec2->GetType() << "," << prec2->GetCourse() << std::endl;
			}
		}
	}
}
void CoursePreconditionManagment::WritePreconditions(const std::vector<Precondition*>& PrecVek)
{
	CourseDirectoryManagment scanner;
	scanner.CreateCourseDir(this->course);
	std::string filePath = (scanner.GetPath() + this->course + "Preconditions.txt");
	std::ofstream outFile(filePath, std::ios::out);
	if (outFile.is_open())
	{
		for (auto precondition : PrecVek)
		{
			std::string type = precondition->GetType();
			int tip = stoi(type);

			switch (tip)
			{
			case(1):
			{
				NumOfCoursesPrec* prec = dynamic_cast<NumOfCoursesPrec*>(precondition);

				if (prec != nullptr)
				{
					outFile << prec->GetType() << "," << prec->getNumOfCourse() << std::endl;
				}
			}break;
			case(2):
			{
				HasHeFinishedCoursePrec* prec2 = dynamic_cast<HasHeFinishedCoursePrec*>(precondition);

				if (prec2 != nullptr)
				{
					outFile << prec2->GetType() << "," << prec2->GetCourse() << std::endl;
				}
			}break;
			default:
				break;

			}

		}
		outFile.close();
	}
}
void CoursePreconditionManagment::ReadCoursePreconditions(std::vector<Precondition*>& preconditions)
{
	std::string type, trait;
	CourseDirectoryManagment scanner;
	scanner.CreateCourseDir(this->course);
	std::string filePath = (scanner.GetPath() + this->course + "Preconditions.txt");
	std::ifstream inFile(filePath, std::ios::in);
	if (inFile.is_open())
	{
		while (inFile.good())
		{
			std::getline(inFile, type, ',');
			if (type == "1")
			{
				//NumofCoursesPrec
				std::getline(inFile, trait, '\n');
				inFile >> std::ws;
				Precondition* prec = new NumOfCoursesPrec(stoi(trait));
				preconditions.push_back(prec);
			}
			else if (type == "2")
			{
				std::getline(inFile, trait, '\n');
				inFile >> std::ws;
				Precondition* prec = new HasHeFinishedCoursePrec(trait);
				preconditions.push_back(prec);
			}
		}
		inFile.close();
	}
}
