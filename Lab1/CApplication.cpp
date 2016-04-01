#include "stdafx.h"
#include "CApplication.h"

using namespace std;

CApplication::CApplication(int argc, char * argv[])
{
	CheckParametrs(argc, argv);

	m_nameInputFile = argv[1];
	m_nameOutputFile = argv[2];
}

CApplication::~CApplication()
{
}

void CApplication::Run()
{
	OpenFiles();

	forest forest;
	FillForestMap(m_inputFile, forest);
	FillIInsidePlace(forest);
	size_t amountWalls = GetAmountWallsForTrees(forest);
	//RemoveInsideWalls(amountWalls , forest);
	m_outputFile << amountWalls;
}

void CApplication::CheckParametrs(int argc, char *argv[])
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + to_string(AMOUNT_ARGUMENTS));
	}
}

void CApplication::OpenFiles()
{
	CheckAndOpenFileForReading(m_inputFile, m_nameInputFile);
	CheckAndOpenFileForWriting(m_outputFile, m_nameOutputFile);
}


void CApplication::CheckAndOpenFileForReading(ifstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ifstream::badbit);
	if (!file.is_open())
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_READING);
	}
}

void CApplication::CheckAndOpenFileForWriting(ofstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ofstream::badbit);
	if (!file.is_open())
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}
}