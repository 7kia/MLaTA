#include "stdafx.h"
#include "Solver.h"

void CSolver::FillForestMap(std::ifstream &file , Forest &forest)
{
	m_widthMap = 0;
	m_heightMap = 0;
	m_countHeight = 0;
	while (!file.eof())
	{
		if ((m_widthMap == 0) && (m_heightMap == 0))
		{
			file >> m_heightMap;
			file >> m_widthMap;

			std::string passString;
			std::getline(file , passString);
		}


		CheckWidthAndHeight();
		
		std::string addString;
		std::getline(file , addString);

		m_countWidth = addString.size();
		CheckCountersMap();
			
		forest.push_back(addString);

		CheckCountersMap();
		m_countHeight++;
	}
}

void CSolver::CheckWidthAndHeight()
{
	if ((m_heightMap < 1) && (m_widthMap < 1))
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}

void CSolver::CheckCountersMap()
{
	if ((static_cast<long>(m_countHeight) > m_heightMap) 
		|| ((static_cast<long>(m_countWidth) < 0L) && (m_widthMap > 0L)))
	{
		throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}

size_t CSolver::GetAmountWallsForTrees(Forest &forest)
{
	size_t amountWalls = 0;

	for (size_t y = 0; y < forest.size(); y++)
	{
		for (size_t x = 0; x < forest[y].size(); x++)
		{
			if (forest[y][x] == charTree)
			{
				amountWalls += GetAmountWallsForTree(forest, static_cast<long>(x), static_cast<long>(y));
			}
		}
	}

	return amountWalls;
}

size_t CSolver::GetInsideWalls(size_t x, size_t y, const Forest & forest) const
{
	size_t amountNeightbos = 0;

	long X = static_cast<long>(x);
	long Y = static_cast<long>(y);

	for (int x1 = -1; x1 <= 1; x1++)
	{
		for (int y1 = -1; y1 <= 1; y1++)
		{
			if (abs(x1) != abs(y1))
			{
				// Проверка допустимости
				if ((((X + x1) >= 0) && ((Y + y1) >= 0))
					&& (static_cast<long>(X + x1) <= m_widthMap) && (static_cast<long>(Y + y1) < forest.size()))
				{
					if (forest[Y + y1][X + x1] == charTree)
					{
						amountNeightbos++;
					}
				}
				//
			}
		}
	}

	return amountNeightbos;
}

void CSolver::Push(Forest & forest, size_t x, size_t y, Queue & paths) {
	if (x < forest[0].size() && x >= 0)
	{
		if (y < forest.size() && y >= 0)
		{
			if (forest[y][x] == charTree)
				return;
			if (forest[y][x] == searchChar)
				return;
			if (forest[y][x] == emptyChar)
				forest[y][x] = searchChar;
			paths.push_back({ x + 1, y });
			paths.push_back({ x - 1, y });
			paths.push_back({ x, y - 1 });
			paths.push_back({ x, y + 1 });
		}
	}
}

void CSolver::Fill(Forest & forest, size_t x, size_t y)
{
	Queue paths;
	do
	{
		if (paths.size() > 0)
		{
			x = paths[0].x;
			y = paths[0].y;
			paths.erase(paths.begin());
			if (x < 0 || x >= forest.size())
				continue;
			if (x < forest.size() && x >= 0)
			{
				if (y >= forest[x].size() || y < 0)
					continue;
			}
		}
		Push(forest, x, y, paths);
	} while (!paths.empty());
}

void CSolver::FillIInsidePlace(Forest & forest)
{

	for (size_t y = 1; y < (forest.size() - 1); y++)
	{
		for (size_t x = 1; x < (forest[y].size() - 1); x++)
		{
			if (forest[y][x] == emptyChar)
			{
				Fill(forest, x, y);
				if (CheckBorderSymbols(forest))
				{
					ReplaceSymbol(forest, searchChar, charTree);
				}
				else
				{
					ReplaceSymbol(forest, searchChar, emptyChar);
				}
			}

		}
	}
}

bool CSolver::CheckBorderSymbols(const Forest & forest) const
{
	for (size_t x = 0, y = 0; x < forest[y].size(); x++)
	{
		if (forest[y][x] == searchChar)
		{
			return false;
		}
	}

	for (size_t y = 1; y < forest.size(); y++)
	{
		if (forest[y][0] == searchChar)
		{
			return false;
		}
		if (forest[y][forest[y].size() - 1] == searchChar)
		{
			return false;
		}
	}

	for (size_t x = 0, y = forest.size() - 1; x < forest.size(); x++)
	{
		if (forest[y][x] == searchChar)
		{
			return false;
		}
	}

	return true;
}

void CSolver::ReplaceSymbol(Forest & forest, char search, char replace)
{
	for (auto &column : forest)
	{
		for (auto &row : column)
		{
			if (row == search)
			{
				row = replace;
			}
		}
	}
}

size_t CSolver::GetAmountWallsForTree(const Forest &forest, long x , long y) const
{
	size_t amountWalls = 4;

	for (int x1 = -1; x1 <= 1; x1++)
	{
		for (int y1 = -1; y1 <= 1; y1++)
		{

			// X+X
			// +X+     X - не проходит проверку
			// X+X     + - проходит проверку
			if (abs(x1) != abs(y1))
			{
				if ( (((x + x1) >= 0) && ((y + y1) >= 0))
						&& ((x + x1) <= m_widthMap) && ((y + y1) < forest.size()))
				{

					if (forest[y + y1][x + x1] == charTree)
					{
						amountWalls--;
					}
				}

			}

		}

	}

	return amountWalls;
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