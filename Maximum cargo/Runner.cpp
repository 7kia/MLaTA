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

void CRunner::Run()
{
	OpenFiles();

	Graph graph = ReadGraph(m_inputFile);

	WriteVectorInFile(m_outputFile, GetMaxCargoForOtherTowns(graph));

	//PrisesArray prises;
	//FillPrisesList(m_inputFile, prises);
	//size_t maxCost = GetMaxCost(prises);

	//size_t secondMaxCost = GetLessMaxCost(prises);
	//m_outputFile << secondMaxCost;
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
