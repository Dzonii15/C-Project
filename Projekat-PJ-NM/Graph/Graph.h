#pragma once
#include <queue>
#include <functional>
class Graph
{
	int** matrix;
	int numberNodes;
public:
	Graph(int** matrix1, int nnodes) :matrix(matrix1), numberNodes(nnodes)
	{
	}
	~Graph()
	{
		if (matrix != nullptr)
		{
			for (int i = 0; i < numberNodes; i++)
				delete[] matrix[i];
			delete[] matrix;
		}
	}
	double findMinDistance(int beginingNode, int endNode)
	{
		bool* visited = new bool[numberNodes];
		for (int i = 0; i < numberNodes; i++)
			visited[i] = false;
		visited[beginingNode] = true;
		std::queue<int> red;
		red.push(beginingNode);
		double* counter = new double[numberNodes];
		for (int i = 0; i < numberNodes; i++)
			counter[i] = 0;
		while (!red.empty())
		{
			int curr = red.front();
			red.pop();
			for (int u = 0; u < numberNodes; u++)
			{
				if (matrix[curr][u] == 1 && !visited[u])
				{
					visited[u] = true;
					red.push(u);
					counter[u] = counter[curr] + 1;
				}

			}
			if (visited[endNode] == true)
				break;
		}
		delete[]visited;
		int d = counter[endNode];
		delete[] counter;
		return d;
	}


};