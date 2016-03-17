#include "stdafx.h"
#include "CApplication.h"

using namespace std;

CApplication::CApplication(int argc , char * argv[])
{
	if (CheckParametrs(argc , argv))
	{
		nameInputFile = argv[1];
		nameOutputFile = argv[2];

		isCorrectInputDate = true;
	}
	else
	{
		isCorrectInputDate = false;
	}
}

CApplication::~CApplication()
{
}

bool CApplication::Run()
{
	if (isCorrectInputDate)
	{
		if (OpenFiles())
		{
			try
			{
			prises prises;
			FillPrisesList(inputFile, prises);
			size_t maxCost = GetMaxCost(prises);

			size_t secondMaxCost = GetLessMaxCost(prises);
			//outputFile << maxCost;


			}
			catch(std::exception e)
			{
				cout << e.what() << endl;
			}
			return true;
		}
	}

	return false;
}

bool CApplication::CheckParametrs(int argc , char *argv[])
{
	if (argc == AMOUNT_ARGUMENTS)
	{
		return true;
	}
	cout << MESSAGE_INCORRECT_AMOUNT_ARGUMENTS << AMOUNT_ARGUMENTS << endl;

	return false;
}

bool CApplication::OpenFiles()
{
	inputFile.open(nameInputFile);
	if (!CheckFileForReading(inputFile))
	{
		return false;
	}

	outputFile.open(nameOutputFile);
	if (!CheckFileForWriting(outputFile))
	{
		return false;
	}

	return true;
}


bool CApplication::CheckFileForReading(ifstream & file)
{
	if (!file.is_open())
	{
		cout << MESSAGE_FAILED_OPEN << nameInputFile << MESSAGE_FAILED_OPEN_FOR_READING << endl;
		return false;
	}

	return true;
}

bool CApplication::CheckFileForWriting(ofstream & file)
{
	if (!file.is_open())
	{
		cout << MESSAGE_FAILED_OPEN << nameInputFile << MESSAGE_FAILED_OPEN_FOR_WRITING << endl;
		return false;
	}

	return true;
}