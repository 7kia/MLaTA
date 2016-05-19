#include "stdafx.h"
#include "FileManager.h"

using namespace std;

CFileManager::CFileManager()
{
}

CFileManager::~CFileManager()
{
}

void CFileManager::SetInputFile(const string & nameInputFile)
{
	if (m_nameInputFile.size() == 0)
	{
		m_nameInputFile = nameInputFile;
		CheckAndOpenFileForReading(m_inputFile, m_nameInputFile);
	}
	else
	{
		throw logic_error(MESSAGE_FILE_IS_OPEN + nameInputFile + MESSAGE_FAILED_OPEN_FOR_READING);
	}
}

void CFileManager::SetOutputFile(const string & nameOutputFile)
{
	if (m_nameOutputFile.size() == 0)
	{
		m_nameOutputFile = nameOutputFile;
		CheckAndOpenFileForWriting(m_outputFile, m_nameOutputFile);
	}
	else
	{
		throw logic_error(MESSAGE_FILE_IS_OPEN + nameOutputFile + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}

}


void CFileManager::CheckAndOpenFileForReading(ifstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ifstream::badbit);
	if (!file.is_open())
	{
		throw ifstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_READING);
	}
}

void CFileManager::CheckAndOpenFileForWriting(ofstream & file, const string& fileName)
{
	file.open(fileName);
	file.exceptions(ofstream::badbit);
	if (!file.is_open())
	{
		throw ofstream::failure(MESSAGE_FAILED_OPEN + fileName + MESSAGE_FAILED_OPEN_FOR_WRITING);
	}
}