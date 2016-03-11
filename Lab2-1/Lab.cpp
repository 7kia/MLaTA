#include "stdafx.h"
#include "Lab.h"

void CLabAaSD::FillPrisesList(std::ifstream &file, prises &prises)
{
	countPrises = 0;

	int number = 0;

	while (!file.eof())
	{
		if ((amountPrises == 0) && (amountNumbers == 0))
		{
			file >> amountPrises;
			file >> amountNumbers;

			std::string passString;
			std::getline(file , passString);
		}


		if (checkAmountPrisesAndNumbers())
		{
			/*
			std::string addString;
			std::getline(file , addString);

			countNumbers = addString.size();
			if (checkCounterWidthMap())
			{
				forest.push_back(addString);

				if (checkCounterHeightMap())
				{
					countHeight++;
				}
			}
			*/

			file >> number;

			prises.push_back(number);
			//lastNumber = number;

		}

	}
}

bool CLabAaSD::checkAmountPrisesAndNumbers()
{
	if ((amountPrises < 1) && (amountNumbers < 1))
	{
		throw MESSAGE_INCORRECT_SIZE;
		return false;
	}
	return true;
}

bool CLabAaSD::checkCounterWidthMap()
{
	if ((static_cast<int>(countPrises) > amountPrises) && (static_cast<int>(countNumbers) < 0) && (amountNumbers > 0))
	{
		throw MESSAGE_WIDTH_MORE_EXPECTED;
		return false;
	}
	return true;
}

/*
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


void CLabAaSD::GetMaxCost(prises & prises)
{
}

point::point()
{
}

point::point(size_t first, size_t second)
{
	x = first;
	y = second;
}
