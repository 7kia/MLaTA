#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <limits>
#include <boost/algorithm/string.hpp>


struct SPoint
{
	SPoint();
	SPoint(float x, float y);
	float x;
	float y;
}; 

struct SDataForSolver
{
	SPoint firstPoint;
	SPoint secondPoint;
	float radiusCircle;
};

struct SCoefficientForLineEquation
{
	float A;
	float B;
	float C;
};

typedef std::vector<std::string> Words;

class CSolver
{
private:
	const std::string				MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string				MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
	const std::string				MESSAGE_WIDTH_MORE_EXPECTED = "Amount strings more expected!!!";

	const int						AMOUNT_ARGUMENTS = 5;
private:
	void							CheckAmountStrings();
protected:
	size_t							m_amountStrings = 0;
	size_t							m_countStrings = 0;

protected:
	void							CheckStringsCounters();

	float							GetLengthLineConectTwoPoints(const std::string & inputString);
	Words							SplitWords(std::string const & text);
	SDataForSolver					ExtractData(const std::string & inputString);
	SCoefficientForLineEquation		GetLineEquation(const SPoint & firstPosition, const SPoint & secondPosition);

	float							GetDiscriminant(const float A, const float B, const float C) const;
	std::pair<SPoint, SPoint>		GetPointsIntersection(const SDataForSolver & data);
	float							GetLengthLine(const SPoint & firstPosition, const SPoint & secondPosition);


};