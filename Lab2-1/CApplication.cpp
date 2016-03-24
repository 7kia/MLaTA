#include "stdafx.h"
#include "CApplication.h"

using namespace std;

CApplication::CApplication(int argc , char * argv[])
{
	CheckParametrs(argc, argv);
	
	nameInputFile = argv[1];
	nameOutputFile = argv[2];	
}

CApplication::~CApplication()
{
}

void CApplication::Run()
{
	OpenFiles();

	prises prises;
	FillPrisesList(inputFile, prises);
	size_t maxCost = GetMaxCost(prises);

	size_t secondMaxCost = GetLessMaxCost(prises);
	outputFile << secondMaxCost;
}

void CApplication::CheckParametrs(int argc , char *argv[])
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + to_string(AMOUNT_ARGUMENTS));
	}
}

void CApplication::OpenFiles()
{
	inputFile.open(nameInputFile);
	inputFile.exceptions(ifstream::badbit);
	if (!CheckFileForReading(inputFile))
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + nameInputFile + MESSAGE_FAILED_OPEN_FOR_READING);
	}

	outputFile.open(nameOutputFile);
	outputFile.exceptions(ofstream::badbit);
	if (!CheckFileForWriting(outputFile))
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + nameOutputFile + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}

}


bool CApplication::CheckFileForReading(ifstream & file)
{
	if (!file.is_open())
	{
		return false;
	}

	return true;
}

bool CApplication::CheckFileForWriting(ofstream & file)
{
	if (!file.is_open())
	{
		return false;
	}

	return true;
}