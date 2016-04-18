#include "stdafx.h"
#include "Solver.h"

Graph CSolver::ReadGraph(std::ifstream &file)
{
	Graph result;
	m_countRoads = 0;

	int firstTown = 0;
	int secondTown = 0;
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
	int graphSize = static_cast<int>(graph.size());
	std::vector<int> label(graphSize, std::numeric_limits<int>::min());
	std::vector<bool> isVisited(graphSize, false);

	ExploredPaths isVisitedPath(graphSize, std::vector<bool>(graphSize, false));
	size_t indexMaxCargo = 0;
	for (size_t index1 = 0; index1 < graphSize; index1++)
	{

		SearchPathToNotExplored(index1, graphSize, graph,
								isVisitedPath, label, indexMaxCargo);

		isVisited[indexMaxCargo] = true;

		SearchPathFromVertexWithMaxCargo(graph, graphSize,
										isVisited, label,
										isVisitedPath, indexMaxCargo);

	}
	////
	// —мотрим на макс груз с точки откуда можно попасть
	// «аписываем все пути в эту точку
	/*
	for (size_t index2 = 1; index2 < graphSize; index2++)
	{
		std::vector<int> cargoInTheVertex;
		bool isFind = false;
		for (size_t index3 = 0; index3 < graphSize; index3++)
		{
			if (graph[index3][index2] > std::numeric_limits<int>::min())
			{
				if ((label[index3] > label[index2])///
					&& (label[index3] > std::numeric_limits<int>::min()))
				{
					
						cargoInTheVertex.push_back(label[index2]);
					
				}
				else
				{
					cargoInTheVertex.push_back(label[index3]);
				}
			}
		}

		std::vector<int> cargoFromPath;
		for (size_t index3 = 0; index3 < cargoInTheVertex.size(); index3++)
		{
			if (cargoInTheVertex[index3] > 0)
			{
				cargoFromPath.push_back(cargoInTheVertex[index3]);
			}
		}

		auto iter = std::max_element(cargoFromPath.begin(), cargoFromPath.end());
		if (iter != cargoFromPath.end())
		{
			int max = *iter;
			if (label[index2] > max)
			{
				label[index2] = max;
			}
		}
		//if ((graph[index1][index2] > label[index1])
		//	&& (label[index1] != std::numeric_limits<int>::min()
		//		))
		//{
		
		//}
		////
	}
	//*/

	label.erase(label.begin());

	return label;
}

void CSolver::FindPath(size_t graphSize, const Graph & graph,
						ExploredPaths &isVisitedPath, std::vector<int> &label)
{
	for (size_t index2 = 1; index2 < graphSize; index2++)
	{
		std::vector<int> cargoInTheVertex;
		bool isFind = false;
		for (size_t index3 = 0; index3 < graphSize; index3++)
		{
			if (isVisitedPath[index3][index2] && graph[index3][index2] > std::numeric_limits<int>::min())
			{
				if ((label[index3] > graph[index3][index2])
					&& (label[index3] > std::numeric_limits<int>::min()))
				{
					if (!isFind)
					{
						isFind = true;
						cargoInTheVertex.clear();
						cargoInTheVertex.push_back(label[index3]);
					}
					else if (cargoInTheVertex[0] > label[index3])
					{
						cargoInTheVertex[0] = label[index3];
					}
				}
				else
				{
					cargoInTheVertex.push_back(graph[index3][index2]);
				}
			}
		}

		std::vector<int> cargoFromPath;
		for (size_t index3 = 0; index3 < cargoInTheVertex.size(); index3++)
		{
			if (cargoInTheVertex[index3] > 0)
			{
				cargoFromPath.push_back(cargoInTheVertex[index3]);
			}
		}

		auto iter = std::max_element(cargoFromPath.begin(), cargoFromPath.end());
		if (iter != cargoFromPath.end())
		{
			int max = *iter;
			if (label[index2] > max)
			{
				label[index2] = max;
			}
		}
		//if ((graph[index1][index2] > label[index1])
		//	&& (label[index1] != std::numeric_limits<int>::min()
		//		))
		//{

		//}
		////
	}

}

void CSolver::SearchPathToNotExplored(size_t index1, size_t graphSize, const Graph & graph,
	ExploredPaths &isVisitedPath, std::vector<int> &label, size_t &indexMaxCargo)
{
	int valueMaxCargo = -1;

	for (size_t index2 = 1; index2 < graphSize; index2++)
	{
		if ((graph[index1][index2] > label[index2])
			//&& !isVisited[index2]
			&& (label[index2] == std::numeric_limits<int>::min()))
		{

			label[index2] = graph[index1][index2];

			if ((label[index1] > std::numeric_limits<int>::min())
				&& (graph[index2][index1] > label[index1]))

		
			{
				label[index2] = label[index1];
			}

			//SearchMaxPath(graphSize, graph, isVisitedPath, label, SPoint(index2, index1));
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
	std::vector<bool> &isVisited, std::vector<int> &label,
	ExploredPaths &isVisitedPath, size_t indexMaxCargo)
{
	for (size_t index2 = 0; index2 < graphSize; index2++)
	{
		if (
			((!isVisited[index2]
				&& (label[indexMaxCargo] != std::numeric_limits<int>::min())
				&& (graph[indexMaxCargo][index2] >= label[indexMaxCargo])
				&& (graph[indexMaxCargo][index2] != std::numeric_limits<int>::min()))
				)

			)
		{
			isVisitedPath[indexMaxCargo][index2] = true;


			//SearchMaxPath(graphSize, graph, isVisitedPath, label, SPoint(index2, indexMaxCargo));
			label[index2] = label[indexMaxCargo];
		};
	}
}

void CSolver::SearchMaxPath(size_t graphSize, const Graph & graph, 
	ExploredPaths &isVisitedPath, std::vector<int> &label,
	const SPoint &coordinates)
{

	std::vector<int> paths;
	for (size_t index1 = 0; index1 < graphSize; index1++)
	{
		//			откуда       куда
		if (graph[index1][coordinates.x] > std::numeric_limits<int>::min())
		{
			paths.push_back(label[index1]);
		}
	}

	auto iter = std::max_element(paths.begin(), paths.end());
	if (iter != paths.end())
	{
		int max = *iter;
		if (label[coordinates.x] > max)
		{
			label[coordinates.x] = max;
		}
	}
}

void CSolver::NoteThatThePathIsTraveled(const Graph & graph, ExploredPaths &isVisitedPath,
										SPoint position)
{
	if (graph[position.y][position.x] > std::numeric_limits<int>::min())
	{
		isVisitedPath[position.y][position.x] = true;
	}
}

SPoint::SPoint()
	: x(0)
	, y(0)
{
}

SPoint::SPoint(size_t first, size_t second)
	: x(first)
	, y(second)
{
}

SRange::SRange()
{
}

SRange::SRange(size_t indexStart, size_t indexEnd)
{
	m_indexStart = indexStart;
	m_indexEnd = indexEnd;
}

