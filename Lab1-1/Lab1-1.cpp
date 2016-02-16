// Lab1-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

static const char GARDEN = '#';
static const char EMPTY = '.';


struct point
{
	size_t x;
	size_t y;
};

typedef std::vector<point> Garden;
typedef std::vector<Garden> vectorGarden;

bool HaveNeighbors(int x , int y , Garden &garden)
{
	for (auto element : garden)
	{


		for (int x1 = -1; x1 <= 1; x1++)
		{

			for (int y1 = -1; y1 <= 1; y1++)
			{
				if ((y1 != 0) || (x1 != 0))
				{
					// Проверка допустимости
					if (((x + x1) >= 0) && ((y + y1) >= 0))
					{
						if ((element.x == (x + x1)) && (element.y == (y + y1)))
						{
							return true;
						}
					}
					//
				}
			}

		}


	}
	return false;
}

bool IsIn(int x , int y , Garden &garden)
{
	for (size_t index1 = 0; index1 < garden.size(); index1++)
	{
		if ((garden[index1].x == x) && (garden[index1].y == y))
		{
			return true;
		}
	}
	return false;
}

bool PushInGarden(int x , int y , vectorGarden &vectorGarden)
{
	bool continueSearch = false;
	size_t indexFindGarden = 0;

	for (size_t index1 = 0; index1 < vectorGarden.size(); index1++)
	{
		if (!continueSearch)
		{
			if (!IsIn(x , y , vectorGarden[index1]) && HaveNeighbors(x , y , vectorGarden[index1]))
			{
				point add;
				add.x = x;
				add.y = y;
				vectorGarden[index1].push_back(add);
				continueSearch = true;
				indexFindGarden = index1;
			}
		}
		else
		{
			if (IsIn(x , y , vectorGarden[index1]) || HaveNeighbors(x , y , vectorGarden[index1]))
			{
				point add;
				add.x = x;
				add.y = y;

				// Присоединяем найденную грядку
				for (auto element : vectorGarden[index1])
				{
					vectorGarden[indexFindGarden].insert(vectorGarden[indexFindGarden].end() , element);
				}
				vectorGarden.erase(vectorGarden.begin() + index1);// удаляем просоединённую
			}
		}

	}
	return continueSearch;
}

void SearchGarden(std::string *strings, size_t numberFirstString, vectorGarden &vectorGarden)
{
	for (size_t indexStrings = numberFirstString; indexStrings < (numberFirstString + 3); indexStrings++)
	{
		for (size_t index1 = 0; index1 < strings[indexStrings].size(); index1++)
		{
			switch (strings[indexStrings][index1])
			{
			case GARDEN:
				if (!PushInGarden(static_cast<int>(index1) , static_cast<int>(indexStrings) , vectorGarden))
				{
					Garden addGarden;
					point add;
					add.x = index1;
					add.y = indexStrings;
					addGarden.push_back(add);
					vectorGarden.push_back(addGarden);
				}
				break;
			case EMPTY:
				break;
			default:
				break;
			}

		}

	}
	
}

int main()
{
	/*
	
	*/
	std::string nameInputFile = "input.txt";
	std::string nameOutputFile = "output.txt";

	std::ifstream inputFile;
	inputFile.open(nameInputFile);
	if (!inputFile.is_open())
	{
		cout << "Failed to open" << nameInputFile << endl;
	}

	std::ofstream outputFile(nameOutputFile);
	if (!outputFile.is_open())
	{
		cout << "Failed to open" << nameOutputFile << endl;
	}


	vectorGarden vectorGarden;
	std::string inputStrings[3];
	size_t indexStrings = 0;
	size_t numberString = 0;
	while (!inputFile.eof())
	{

		if (indexStrings < 3)
		{
			getline(inputFile , inputStrings[indexStrings]);
			indexStrings++;
		}
		else
		{
			SearchGarden(inputStrings , numberString , vectorGarden);
			numberString++;

			inputStrings[0] = inputStrings[1];// 1 << 2
			inputStrings[1] = inputStrings[2];// 2 << 3
			getline(inputFile , inputStrings[indexStrings]);// 3 << следующую
			indexStrings = 3;
		}

	}

	cout << vectorGarden.size() << endl;

	outputFile << vectorGarden.size();

  return 0;
}

