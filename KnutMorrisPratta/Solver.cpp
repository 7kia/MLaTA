#include "stdafx.h"
#include "Solver.h"

using namespace std;

void CSolver::WritePositions(ostream & strm, size_t sizeSearchString,
							const PrefixFunction & prefixFunction, size_t anchorPosition)
{
	SRange<size_t> range;
	for (size_t index = 0; index < prefixFunction.size(); index++)
	{
		if (prefixFunction[index] == sizeSearchString)
		{
			range.end = anchorPosition + (index + 1 - sizeSearchString - SYMBOL_DIVIDER.size());
			range.start = range.end - prefixFunction[index] + 1;

			strm << range.start << ' ' << range.end << endl;
		}
	}
}

PrefixFunction CSolver::GetPrefixFunction(const string & inputString)
{
	PrefixFunction result;

	// TODO : delete // value counter for check effect optimization 45 // 37 // 19
	size_t counter = 0;

	result.resize(inputString.size(), 0);

	string prefix;
	string suffix;
	for (size_t index = 1; index < inputString.size(); index++)
	{
		////////////////////
		// First optimization
		size_t startIndex = 1;
		if ((index - 1) != std::numeric_limits<size_t>::max())
		{
			if (result[index - 1] > 0)
			{
				startIndex += result[index - 1];
			}
		}
		////////////////////
		// Second optimization
		if (startIndex != 1)
		{
			char lastInPrefix = inputString[startIndex - 1];
			char lastInSuffix = inputString[index];

			bool symbolsIsEqual = (lastInPrefix == lastInSuffix);

			if (symbolsIsEqual)
			{
				result[index] += result[index - 1] + 1;
				continue;
			}
		}
		////////////////////
		for (size_t index2 = 1; (index2)  < index; index2++)
		{
			prefix = inputString.substr(0, index2);
			suffix = inputString.substr(index - index2 + 1, index2);
			if ((!suffix.empty() && !prefix.empty()) && (prefix == suffix))
			{
				result[index] = index2;
			}

			counter++;// TODO : delete // value counter for check effect optimization 45 // 37 // 19
		}
		
	}

	return result;// TODO
}