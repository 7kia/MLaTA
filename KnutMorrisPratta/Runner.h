#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <memory>

#include "Solver.h"

class CRunner : public CSolver
{
public:
	CRunner(std::string nameInputFile, std::string nameOutputFile);
	~CRunner();

	void			Run();

private:
	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";

	std::string		m_nameInputFile;
	std::string		m_nameOutputFile;

	std::ifstream	m_inputFile;
	std::ofstream	m_outputFile;

	std::ifstream	m_investigateFile;
	std::string		m_searchString;
	std::string		m_nameInvestigateFile;


private:
	void			OpenFiles();
	void			ReadArgumentsForSearch();

	void			CheckAndOpenFileForReading(std::ifstream &file, const std::string& fileName);
	void			CheckAndOpenFileForWriting(std::ofstream &file, const std::string& fileName);

	void			WriteVectorInFile(std::ofstream &file, const std::vector<int> &vector);
};
