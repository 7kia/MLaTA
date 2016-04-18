#include "stdafx.h"
#include "Solver.h"

Graph CSolver::ReadGraph(std::ifstream &file)
{
	Graph result;
	m_countRoads = 0;

	size_t firstTown = 0;
	size_t secondTown = 0;
	int cargo = 0;
	while (!file.eof())
	{
		if ((m_amountTowns == 0) && (m_amountRoads == 0))
		{
			file >> m_amountTowns;
			file >> m_amountRoads;

			CheckAmountTownsAndRoads();

			std::string passString;
			std::getline(file , passString);

			result.resize(m_amountTowns, std::vector<int>(m_amountTowns, std::numeric_limits<int>::min()));
		}

		file >> firstTown;
		file >> secondTown;
		file >> cargo;
		result[--firstTown][--secondTown] = cargo;
		result[secondTown][firstTown] = cargo;

		m_countRoads++;
		CheckRoadCounters();
	}
	CheckRoadCounters();

	return result;
}


void CSolver::CheckAmountTownsAndRoads()
{
	if ((m_amountTowns < 1) && (m_amountRoads < 1))
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}

void CSolver::CheckRoadCounters()
{
	if ((static_cast<int>(m_countRoads) > m_amountRoads))
	{
		//throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}


std::vector<int> CSolver::GetMaxCargoForOtherTowns(const Graph & graph)
{
	size_t graphSize = graph.size();
	std::vector<int> label(graphSize, std::numeric_limits<int>::min());

	std::vector<bool> isVisited(graphSize, false);// Отладочная информация
	ExploredPaths isVisitedPath(graphSize, std::vector<bool>(graphSize, false));
	size_t indexMaxCargo = 0;
	for (size_t index1 = 0; index1 < graphSize; index1++)
	{

		SearchPathToNotExplored(index1, graphSize, graph,
								isVisitedPath, label, indexMaxCargo);

		isVisited[indexMaxCargo] = true;

		SearchPathFromVertexWithMaxCargo(graph, graphSize, label,
										isVisitedPath, indexMaxCargo);

		
		SearchPathFromVertexWithMaxCargo(graph, graphSize, label,
										isVisitedPath, index1);
	}

	label.erase(label.begin());

	return label;
}

void CSolver::SearchPathToNotExplored(size_t index1, size_t graphSize, const Graph & graph,
	ExploredPaths &isVisitedPath, std::vector<int> &label, size_t &indexMaxCargo)
{
	int valueMaxCargo = -1;

	for (size_t index2 = 1; index2 < graphSize; index2++)
	{
		if ((graph[index1][index2] > label[index2])
			&& (label[index2] == std::numeric_limits<int>::min()))
		{
			if ((label[index1] > std::numeric_limits<int>::min())
				&& (graph[index2][index1] > label[index1]))	
			{
				// Грузоподъёмность от соседнего города
				label[index2] = label[index1];
			}
			else
			{
				// Грузоподъёмность взятой дуги
				label[index2] = graph[index2][index1];
			}

			NoteThatThePathIsTraveled(graph, isVisitedPath, SPoint(index2, index1));

			if (valueMaxCargo < label[index2])
			{
				valueMaxCargo = label[index2];
				indexMaxCargo = index2;
			}
		}
		NoteThatThePathIsTraveled(graph, isVisitedPath, SPoint(index2, index1));

	}

}


void CSolver::SearchPathFromVertexWithMaxCargo(const Graph & graph, size_t graphSize,
	std::vector<int> &label, ExploredPaths &isVisitedPath, size_t indexMaxCargo)
{
	for (size_t index2 = 0; index2 < graphSize; index2++)
	{
		if (
			(label[indexMaxCargo] != std::numeric_limits<int>::min())
			&& (graph[indexMaxCargo][index2] >= label[indexMaxCargo])
			&& (graph[indexMaxCargo][index2] != std::numeric_limits<int>::min())
			)
		{
			isVisitedPath[indexMaxCargo][index2] = true;

			if (label[index2] < label[indexMaxCargo])
			{
				label[index2] = label[indexMaxCargo];
			}
		};
	}
}

// TODO : delete
void CSolver::NoteThatThePathIsTraveled(const Graph & graph, ExploredPaths &isVisitedPath,
										SPoint path)
{
	if (graph[path.y][path.x] > std::numeric_limits<int>::min())
	{
		isVisitedPath[path.y][path.x] = true;
	}
}

SPoint::SPoint()
	: x(0)
	, y(0)
{
}

SPoint::SPoint(size_t x, size_t y)
	: x(x)
	, y(y)
{
}
