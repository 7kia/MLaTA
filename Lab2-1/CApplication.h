#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>

#include "Lab.h"

class CApplication : public CLabAaSD
{
public:
	CApplication(int argc , char *argv[]);
	~CApplication();

	void Run();

private:
	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";
	const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";

	const int AMOUNT_ARGUMENTS = 3;

	std::string		m_nameInputFile;
	std::string		m_nameOutputFile;

	std::ifstream	m_inputFile;
	std::ofstream	m_outputFile;

private:
	void			CheckParametrs(int argc , char *argv[]);

	void			OpenFiles();
	void			CheckAndOpenFileForReading(std::ifstream &file, const std::string& fileName);
	void			CheckAndOpenFileForWriting(std::ofstream &file, const std::string& fileName);

};
