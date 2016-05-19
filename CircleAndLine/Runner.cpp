#include "stdafx.h"
#include "Runner.h"

using namespace std;

CRunner::CRunner() 
{
}

CRunner::~CRunner()
{
}

void CRunner::Run(const std::string & nameInputFile
				, const std::string & nameOutputFile)
{
	SetInputFile(nameInputFile);
	SetOutputFile(nameOutputFile);

	std::string inputString;

	m_inputFile.open(nameInputFile);// TODO : �� ������, ������� ����������
	m_outputFile.open(nameOutputFile);// TODO : �� ������, ������� ����������
	while (getline(m_inputFile, inputString))
	{
		m_outputFile << GetDistanseLineConectTwoPoints(inputString);
	}
}