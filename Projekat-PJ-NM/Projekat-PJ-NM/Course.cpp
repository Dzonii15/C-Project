#include "Course.h"
Course::Course() :Name(""), Type(""), Professor("")
{
}
Course::Course(std::string name, std::string type, std::string Prof) : Name(name), Type(type), Professor(Prof)
{

}
std::string Course::GetName()const
{
	return this->Name;
}
std::string Course::GetType()const
{
	return this->Type;
}
std::string Course::GetProfessor()const
{
	return this->Professor;
}
void Course::SetName(std::string name)
{
	this->Name = name;
}
void Course::SetProfessor(std::string profesor)
{
	this->Professor = profesor;
}
void Course::SetType(std::string tip)
{
	this->Type = tip;
}