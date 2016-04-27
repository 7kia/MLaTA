#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <limits>
#include <array>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>

#include "SPoint.h"

struct SDataForSolver
{
	SRange<size_t> firstPoint;
	SRange<size_t> secondPoint;
	float radiusCircle;
};

struct SCoefficientForLineEquation
{
	// TODO: rename
	float A;
	float B;
	float C;
};

typedef std::vector<std::string> Words;
typedef std::vector<SRange<size_t>> FindPositions;
typedef std::vector<size_t> PrefixFunction;

class CSolver
{
private:
	const std::string				MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string				MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
	const std::string				MESSAGE_WIDTH_MORE_EXPECTED = "Amount strings more expected!!!";

	const int						AMOUNT_ARGUMENTS = 5;
protected:
	void							WritePositions(std::ostream &strm, size_t sizeSearchString,
													const PrefixFunction & prefixFunction);
	PrefixFunction					GetPrefixFunction(const std::string & searchString, std::string inputString);
};
