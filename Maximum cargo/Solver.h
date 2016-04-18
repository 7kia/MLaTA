#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <limits>

struct SPoint
{
	SPoint();
	SPoint(size_t x, size_t y);
	size_t x;
	size_t y;
};

typedef std::vector<std::vector<int>> Graph;
typedef std::vector<std::vector<bool>> ExploredPaths;
 

class CSolver
{
private:
	const std::string	MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string	MESSAGE_WIDTH_MORE_EXPECTED = "Width row more expected!!!";
	const std::string	MESSAGE_HEIGHT_MORE_EXPECTED = "Height map more expected!!!";

	int					m_amountTowns = 0;
	int					m_amountRoads = 0;
	size_t				m_countRoads = 0;
	size_t				m_countNumbers = 0;

private:
	void				CheckAmountTownsAndRoads();
	void				CheckRoadCounters();

	void				SearchPathToNotExplored(size_t index1, size_t graphSize, const Graph & graph,
												ExploredPaths& isVisitedPath, std::vector<int>& label, size_t &indexMaxCargo);

	void				SearchPathFromVertexWithMaxCargo(const Graph & graph, size_t graphSize, std::vector<int>& label,
															ExploredPaths& isVisitedPath, size_t indexMaxCargo);

	void				NoteThatThePathIsTraveled(const Graph & graph, ExploredPaths & isVisitedPath,
													SPoint path);

protected:
	Graph				ReadGraph(std::ifstream & file);
	std::vector<int>	GetMaxCargoForOtherTowns(const Graph & graph);
};