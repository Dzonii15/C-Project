#include "GraphSupport.h"

int** GraphSupport::CreateAdjacencyMatrix(const std::vector<User*>& UserVec)
{
	int n = UserVec.size();
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
	}
	int i = 0, j = 0;
	for (i; i < n; i++)
	{

		for (int j = 0; j < n; j++)
		{
			if (UserVec[i]->CheckFriend(UserVec[j]->GetUserName()))
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
	return matrix;
}
void GraphSupport::CalculateShortestDistance(std::ostream& os, std::istream& is, const std::vector<User*>& UserVec)
{
	const int n = UserVec.size();
	Graph graf(GraphSupport::CreateAdjacencyMatrix(UserVec), n);
	std::string firstStudent;
	std::string secondStudent;
	os << "Unesite prvog studenta:"; std::getline(is, firstStudent);
	os << "Unesite drugog studenta:"; std::getline(is, secondStudent);
	auto FirstStudent = std::find_if(UserVec.begin(), UserVec.end(),
		[firstStudent](const User* korisnik) {return firstStudent == korisnik->GetUserName() && korisnik->GetType() == "Student"; });
	auto SecondStudent = std::find_if(UserVec.begin(), UserVec.end(),
		[secondStudent](const User* korisnik) {return secondStudent == korisnik->GetUserName() && korisnik->GetType() == "Student"; });
	if (FirstStudent == UserVec.end() || SecondStudent == UserVec.end())
	{
		os << "Nepravilan unos!" << std::endl;
		os << "Prekid akcije!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	int firstIndex = FirstStudent - UserVec.begin();
	int secondIndex = SecondStudent - UserVec.begin();

	os << "Najbliza putanja je duga:" << graf.findMinDistance(firstIndex, secondIndex);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	system("CLS");

}
void GraphSupport::CalculateAverageDistance(std::ostream& os, std::istream& is, const std::vector<User*>& UserVec)
{
	const int n = UserVec.size();
	if (n == 0)
	{
		os << "Nemoguce izracunati";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		system("CLS");
		return;
	}
	Graph graf(GraphSupport::CreateAdjacencyMatrix(UserVec), n);
	Precondition* firstprec, * secondprec;
	int FirstOption, SecondOption;
	os << "Odaberite 2 preduslova za definisanje uslova po kojim ce se traziti prosjecna duzina:" << std::endl;
	os << "(1)Da je pohadja X kurseva?" << std::endl;
	os << "(2)Da je polozio odredjeni predmet?" << std::endl;
	os << "Prva opcija:"; is >> FirstOption;
	os << "Druga opcija:"; is >> SecondOption;
	system("CLS");
	double distance = 0;
	if (FirstOption == 1)
	{
		int num;
		os << "Definisite broj kurseva koji trebaju pohadjat za uslov" << std::endl;
		os << "Broj: "; is >> num;
		firstprec = new NumOfCoursesPrec(num);
		system("CLS");
	}
	else
	{
		std::getchar();
		std::string finishedCourse;
		os << "Definisite kurs koji se treba poloziti za uslov:" << std::endl;
		os << "Kurs: "; std::getline(is, finishedCourse);
		firstprec = new HasHeFinishedCoursePrec(finishedCourse);
		system("CLS");
	}
	if (SecondOption == 1)
	{
		int num;
		os << "Definisite broj kurseva koji trebaju pohadjat za uslov" << std::endl;
		os << "Broj: "; is >> num;
		secondprec = new NumOfCoursesPrec(num);
		system("CLS");
	}
	else
	{
		std::getchar();
		std::string finishedCourse;
		os << "Definisite kurs koji se treba poloziti za uslov:" << std::endl;
		os << "Kurs: "; std::getline(is, finishedCourse);
		secondprec = new HasHeFinishedCoursePrec(finishedCourse);
		system("CLS");
	}
	for (int i = 0; i < n; i++)
	{
		Student* student1 = dynamic_cast<Student*>(UserVec[i]);
		if (student1 != nullptr && firstprec->CoursePrecondition(student1))
		{
			for (int j = 0; j < n; j++)
			{
				Student* student2 = dynamic_cast<Student*>(UserVec[j]);
				if (student2 != nullptr && secondprec->CoursePrecondition(student2))
				{
					auto iterator1 = std::find_if(UserVec.begin(), UserVec.end(),
						[student1](const User* korisnik) {return student1->GetUserName() == korisnik->GetUserName(); });
					auto iterator2 = std::find_if(UserVec.begin(), UserVec.end(),
						[student2](const User* korisnik) {return student2->GetUserName() == korisnik->GetUserName(); });
					int firstIndex = iterator1 - UserVec.begin();
					int secondIndex = iterator2 - UserVec.begin();
					distance += graf.findMinDistance(firstIndex, secondIndex);
				}
			}
		}

	}

	os << "Prosjecna duzina:" << std::endl;
	os << distance * (1 / ((double)n * ((double)n - 1))) << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	system("CLS");
	delete firstprec;
	delete secondprec;



}