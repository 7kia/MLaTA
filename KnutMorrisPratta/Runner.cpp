#include "stdafx.h"
#include "Runner.h"

using namespace std;

CRunner::CRunner(std::string nameInputFile, std::string nameOutputFile)
{
	m_nameInputFile = nameInputFile;
	m_nameOutputFile = nameOutputFile;
}

CRunner::~CRunner()
{
}

void CRunner::ReadArgumentsForSearch()
{
	getline(m_inputFile, m_searchString);

	getline(m_inputFile, m_nameInvestigateFile);
}

void CRunner::Run()
{
	OpenFiles();

	ReadArgumentsForSearch();
	CheckAndOpenFileForReading(m_investigateFile, m_nameInvestigateFile);

	std::string inputString;
	FindPositions findPositions;

	size_t anchor = 0;
	string investigateString;
	while (getline(m_investigateFile, inputString))
	{
		investigateString = m_searchString + SYMBOL_DIVIDER + inputString;
		PrefixFunction prefixFunction = GetPrefixFunction(investigateString);
		WritePositions(m_outputFile, m_searchString.size(), prefixFunction, anchor);
		anchor += inputString.size();
	}

}

void CRunner::OpenFiles()
{
	CheckAndOpenFileForReading(m_inputFile, m_nameInputFile);
	CheckAndOpenFileForWriting(m_outputFile, m_nameOutputFile);
}

void CRunner::CheckAndOpenFileForReading(ifstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ifstream::badbit);
	if (!file.is_open())
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_READING);
	}
}

void CRunner::CheckAndOpenFileForWriting(ofstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ofstream::badbit);
	if (!file.is_open())
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}
}

void CRunner::WriteVectorInFile(std::ofstream & file, const std::vector<int>& vector)
{
	for (auto & element : vector)
	{
		file << element << '\n';
	}
}
