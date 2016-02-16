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

size_t CLabAaSD::GetAmountWallsForTree(forest &forest, int x , int y)
{
	size_t amountWalls = 4;

	for (int x1 = -1; x1 <= 1; x1++)
	{
		for (int y1 = -1; y1 <= 1; y1++)
		{


			if (abs(x1) != abs(y1))
			{
				// Проверка допустимости
				//std::cout << x1 << " " << y1 << std::endl;
				//std::cout << (x + x1) << " " << widthMap << " || " << (y + y1) << " " << (forest.size() - 1) << std::endl;
				//std::cout << ((x + x1) < widthMap) << " " << ((y + y1) < (forest.size() - 1)) << std::endl;


				if ( (((x + x1) >= 0) && ((y + y1) >= 0))
						&& ((x + x1) <= widthMap) && ((y + y1) < forest.size()))
				{

					if (forest[y + y1][x + x1] == charTree)
					{

						std::cout << forest[y + y1][x + x1] << " " << x + x1 << " !!! " << y + y1 << std::endl;

						amountWalls--;
					}
				}
				//
			}
		}

	}
	std::cout << amountWalls << " " << x << "  " << y << std::endl;

	return amountWalls;
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
