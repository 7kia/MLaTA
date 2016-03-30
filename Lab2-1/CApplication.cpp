#include "stdafx.h"
#include "CApplication.h"

using namespace std;

CApplication::CApplication(int argc , char * argv[])
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

	prises prises;
	FillPrisesList(m_inputFile, prises);
	size_t maxCost = GetMaxCost(prises);

	size_t secondMaxCost = GetLessMaxCost(prises);
	m_outputFile << secondMaxCost;
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
	m_inputFile.open(m_nameInputFile);
	m_inputFile.exceptions(ifstream::badbit);
	if (!CheckFileForReading(m_inputFile))
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + m_nameInputFile + MESSAGE_FAILED_OPEN_FOR_READING);
	}

	m_outputFile.open(m_nameOutputFile);
	m_outputFile.exceptions(ofstream::badbit);
	if (!CheckFileForWriting(m_outputFile))
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + m_nameOutputFile + MESSAGE_FAILED_OPEN_FOR_WRITING);
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