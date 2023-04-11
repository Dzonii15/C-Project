#pragma once
#include "Graph.h"
#include "NumOfCoursesPrec.h"
#include "HasHeFinishedCoursePrec.h"
class GraphSupport
{
public:

	static void CalculateShortestDistance(std::ostream&, std::istream&, const std::vector<User*>&);
	static void CalculateAverageDistance(std::ostream&, std::istream&, const std::vector<User*>&);
	static int** CreateAdjacencyMatrix(const std::vector<User*>&);

};