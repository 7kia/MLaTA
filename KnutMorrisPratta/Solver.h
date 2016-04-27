#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <limits>
#include <array>

#include "SRange.h"

struct SDataForSolver
{
	SRange<size_t> firstPoint;
	SRange<size_t> secondPoint;
	float radiusCircle;
};

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
	const std::string				SYMBOL_DIVIDER = "#";
protected:
	void							WritePositions(std::ostream &strm, size_t sizeSearchString,
													const PrefixFunction & prefixFunction, size_t anchorPosition);
	PrefixFunction					GetPrefixFunction(const std::string & inputString);
};
