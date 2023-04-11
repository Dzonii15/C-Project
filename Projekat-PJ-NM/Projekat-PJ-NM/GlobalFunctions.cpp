#include "GlobalFunctions.h"

bool GlobalFunctions::IsFileEmpty(std::ifstream& inFile)
{
	inFile.seekg(0, std::ios::end);
	if (inFile.tellg() == 0)
		return true;
	return false;
}