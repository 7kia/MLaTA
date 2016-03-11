#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <time.h> // for clock()
#include <sys/stat.h>// for search file size

#include "Lab.h"

class CApplication : public CLabAaSD
{
public:
	CApplication(int argc , char *argv[]);
	~CApplication();

	bool Run();

private:
	const std::string MESSAGE_FAILED_OPEN = "Failed to open ";
	const std::string MESSAGE_FAILED_OPEN_FOR_READING = " for reading!";
	const std::string MESSAGE_FAILED_OPEN_FOR_WRITING = " for writing!";
	const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";

	const int AMOUNT_ARGUMENTS = 3;

	bool isCorrectInputDate = false;

	std::string nameInputFile;
	std::string nameOutputFile;

	std::ifstream inputFile;
	std::ofstream outputFile;

private:
	bool CheckParametrs(int argc , char *argv[]);

	bool OpenFiles();
	bool CheckFileForReading(std::ifstream &file);
	bool CheckFileForWriting(std::ofstream &file);

};

#endif
