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


size_t CLabAaSD::GetMaxCost(prises & prises)// Optima
{
	int result = 0;
	int summa = 0;
	int lastElement = prises[0];

	//size_t index1 = 0;
	while ((indexStart < prises.size()) && (indexEnd <= prises.size()))// Optima
	{

		if ((indexEnd - indexStart) < amountNumbers)
		{
			if (indexEnd < prises.size())
			{
				summa += prises[indexEnd];
			}							
		}
		else
		{
			if (result <= summa)
			{
				result = summa;
			}
			else
			{
				//indexEnd = indexStart;

				//indexStart += 1;// TODO : might error
				//summa = 0;
			}
			if (result <= summa)
			{
				indexMaxStart = indexStart;
				indexMaxEnd = indexEnd;


			}
			indexEnd = indexStart;

			indexStart += 1;
			
			summa = 0;

		}
		indexEnd++;		
	}

	//size_t costLeft

	return result;
}

size_t CLabAaSD::GetLessMaxCost(prises & prises)// Optima
{
	int result = 0;
	int summa = 0;
	int lastElement = prises[0];

	//size_t index1 = 0;
	indexStart = 0;
	indexEnd = 0;

	while ((indexStart < prises.size()) && (indexEnd <= prises.size()))// Optima
	{
		if ((indexMaxStart == indexStart))
		{
			indexStart = indexMaxEnd + 1;
			indexEnd = indexStart;

		}
		//else
		//{
			if (((indexEnd - indexStart) < amountNumbers)
				&& (indexMaxStart != indexEnd))
			{
				if (indexEnd < prises.size())
				{
					summa += prises[indexEnd];

				}
			}
			else
			{
				if (result <= summa)
				{
					result = summa;
					indexSecondMaxStart = indexStart;
					indexSecondMaxEnd = indexEnd - 1;
				}
				indexEnd = indexStart;

				indexStart += 1;


				summa = 0;

			}
		//}
		
		indexEnd++;
	}

	return result;
}

point::point()
:x(0),
y(0)
{
}

point::point(size_t first, size_t second)
	:x(first),
	y(second)
{
}
