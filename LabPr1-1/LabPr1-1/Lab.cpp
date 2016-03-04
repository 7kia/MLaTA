#include "stdafx.h"
#include "Lab.h"

bool CLabAaSD::checkAmountElements()
{
	return true;
}

bool CLabAaSD::checkCounterElements()
{
	return true;
}

void CLabAaSD::FillVector(std::ifstream &file, intVec &vec)
{
	amountElements = 0;
	countElements = 0;
	while (!file.eof())
	{
		if (amountElements == 0)
		{
			file >> amountElements;

			std::string passString;
			std::getline(file , passString);
		}


		if (checkAmountElements())
		{
			int element;

			file >> element;

			amountElements += 1;
			if (checkCounterElements())
			{
				vec.push_back(element);
			}

		}

	}
}

void CLabAaSD::FindAmountRepeat(intVec & vec)
{
	std::sort(vec.begin(), vec.end());

	std::map<int, size_t> mapIntVec;

	// Формирование карты
	for (size_t index = 0; index < vec.size(); index++)
	{
		if (mapIntVec.find(vec[index]) == mapIntVec.end())
		{
			mapIntVec.insert({ vec[index], 1 });
		}
		else
		{
			mapIntVec[vec[index]] += 1;
		}

	}

	//
	std::map<int, size_t> maxIntVec;

	int maxElement = std::numeric_limits<int>::min();
	size_t maxKey = 0;

	// Поиск максимального значения встречаемости
	for (auto it = mapIntVec.begin(); it != mapIntVec.end(); it++)
	{
		if (it->second > maxKey)
		{
			maxKey = it->second;
		}
	}

	// Добавление в maxIntVec
	for (const auto &element : mapIntVec)
	{
		if (element.second == maxKey)
		{
			maxIntVec.insert(element);
		}
	}

	// Поиск элемента с мин. ключом
	int minKey = std::numeric_limits<int>::max();
	for (auto it = maxIntVec.begin(); it != maxIntVec.end(); it++)
	{
		if (it->first < minKey)
		{
			minKey = it->first;
		}
	}


}

/*
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

*/

point::point()
{
}

point::point(size_t first, size_t second)
{
	x = first;
	y = second;
}
