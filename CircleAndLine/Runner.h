#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <memory>

#include "Solver.h"
#include "FileManager.h"

class CRunner 
	 :	public CSolver
	,	public CFileManager
{
public:
	CRunner();
	~CRunner();

	void			Run(const std::string & nameInputFile
						, const std::string & nameOutputFile);


private:
	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";

	std::string		m_nameInputFile;
	std::string		m_nameOutputFile;

	std::ifstream	m_inputFile;
	std::ofstream	m_outputFile;

private:
};
