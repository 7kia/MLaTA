#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <memory>


class CFileManager
{
public:
	CFileManager();
	virtual ~CFileManager();

protected:
	void			SetInputFile(const std::string & nameInputFile);
	void			SetOutputFile(const std::string & nameOutputFile);

protected:
	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";
	const std::string MESSAGE_FILE_IS_OPEN = "Exist open file ";


	std::string		m_nameInputFile;
	std::string		m_nameOutputFile;

	std::ifstream	m_inputFile;
	std::ofstream	m_outputFile;


protected:
	void			CheckAndOpenFileForReading(std::ifstream &file, const std::string& fileName);
	void			CheckAndOpenFileForWriting(std::ofstream &file, const std::string& fileName);
};