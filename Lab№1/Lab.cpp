#include "stdafx.h"
#include "Lab.h"

void CLabAaSD::FillForestMap(std::ifstream &file , forest &forest)
{
	widthMap = 0;
	heightMap = 0;
	countHeight = 0;
	while (!file.eof())
	{
		if ((widthMap == 0) && (heightMap == 0))
		{
			file >> heightMap;
			file >> widthMap;

			std::string passString;
			std::getline(file , passString);
		}


		if (checkWidthAndHeight())
		{
			std::string addString;
			std::getline(file , addString);

			countWidth = addString.size();
			if (checkCounterWidthMap())
			{
				forest.push_back(addString);

				if (checkCounterHeightMap())
				{
					countHeight++;
				}
			}

		}

	}
}

bool CLabAaSD::checkWidthAndHeight()
{
	if ((heightMap < 1) && (widthMap < 1))
	{
		throw MESSAGE_INCORRECT_SIZE;
		return false;
	}
	return true;
}

bool CLabAaSD::checkCounterWidthMap()
{
	if ((static_cast<int>(countWidth) > widthMap) && (static_cast<int>(countWidth) < 0) && (widthMap > 0))
	{
		throw MESSAGE_WIDTH_MORE_EXPECTED;
		return false;
	}
	return true;
}

bool CLabAaSD::checkCounterHeightMap()
{
	if ((static_cast<int>(countHeight) > heightMap) && (static_cast<int>(countHeight) < 0) && (heightMap > 0))
	{
		throw MESSAGE_HEIGHT_MORE_EXPECTED;
		return false;
	}
	return true;
}

size_t CLabAaSD::GetAmountWallsForTrees(forest &forest)
{
	size_t amountWalls = 0;

	for (size_t y = 0; y < forest.size(); y++)
	{
		for (size_t x = 0; x < forest[y].size(); x++)
		{
			if (forest[y][x] == charTree)
			{
				amountWalls += GetAmountWallsForTree(forest, x, y);

			}
		}
	}

	return amountWalls;
}

size_t CLabAaSD::GetInsideWalls(size_t x, size_t y, forest & forest)
{

	size_t amountNeightbos = 0;


	int X = static_cast<int>(x);
	int Y = static_cast<int>(y);

	for (int x1 = -1; x1 <= 1; x1++)
	{
		for (int y1 = -1; y1 <= 1; y1++)
		{
			if (abs(x1) != abs(y1))
			{
				// Проверка допустимости
				if ((((X + x1) >= 0) && ((Y + y1) >= 0))
					&& ((X + x1) <= widthMap) && ((Y + y1) < forest.size()))
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

bool CLabAaSD::SearchEmptyPlace(int &x, int &y, forest & forest)
{
	// Поиск соседа
	for (int x1 = -1; x1 <= 1; x1++)
	{
		for (int y1 = -1; y1 <= 1; y1++)
		{

			if (abs(x1) != abs(y1))
			{
				// Проверка допустимости
				if ((((x + x1) >= 0) && ((y + y1) >= 0))
					&& ((x + x1) <= widthMap) && ((y + y1) < forest.size()))
				{
					if ((forest[y + y1][x + x1] == emptyChar))
					{
						// Проверка боковых значений
						if (((x1 != 0)
							&&
							((forest[y + 1][x + x1] == charTree)
								^
							(forest[y - 1][x + x1] == charTree))
								)
							//
							||
							//
							((y1 != 0)
								&&
								((forest[y + y1][x + 1] == charTree)
									^
									(forest[y + y1][x - 1] == charTree))
								)
							)
							//
						{
							forest[y][x] = searchChar;
							x += x1;
							y += y1;
							return true;
						}
					}
				}
				else
				{
					x++;
					return false;
				}
				//
			}

			

		}
	}

	return false;
}


void CLabAaSD::Push(forest & forest, size_t x, size_t y, Queue & paths) {
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

void CLabAaSD::Fill(forest & forest, size_t x, size_t y)
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


void CLabAaSD::FillIInsidePlace(forest & forest)
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

bool CLabAaSD::CheckBorderSymbols(forest & forest)
{
	// Поиск вверху
	for (size_t x = 0, y = 0; x < forest[y].size(); x++)
	{
		if (forest[y][x] == searchChar)
		{
			return false;
		}
	}

	// Поиск посередине
	for (size_t y = 1; y < forest.size(); y++)
	{
		if ((forest[y][0] == searchChar) || ((forest[y].size() - 1) == searchChar))
		{
			return false;
		}
		if ((forest[y][forest[y].size() - 1] == searchChar) || ((forest[y].size() - 1) == searchChar))
		{
			return false;
		}
	}

	// Поиск внизу
	for (size_t x = 0, y = forest.size() - 1; x < forest.size(); x++)
	{
		if (forest[y][x] == searchChar)
		{
			return false;
		}
	}

	return true;
}

void CLabAaSD::ReplaceSymbol(forest & forest, char search, char replace)
{
	for (auto &y : forest)
	{
		for (auto &x : y)
		{
			if (x == search)
			{
				x = replace;
			}
		}
	}
}

size_t CLabAaSD::GetAmountWallsForTree(forest &forest, int x , int y)
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
				// Проверка допустимости
				if ( (((x + x1) >= 0) && ((y + y1) >= 0))
						&& ((x + x1) <= widthMap) && ((y + y1) < forest.size()))
				{

					if (forest[y + y1][x + x1] == charTree)
					{
						amountWalls--;
					}
				}
				//
			}

		}

	}

	return amountWalls;
}

point::point()
{
}

point::point(size_t first, size_t second)
{
	x = first;
	y = second;
}
