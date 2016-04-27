#include "stdafx.h"
#include "Solver.h"

using namespace boost::numeric::ublas;
using namespace std;

// TODO : delete
std::vector<string> SplitWords(string const& text)
{
	string trimmed = boost::trim_copy(text);

	std::vector<string> words;
	boost::split(words, trimmed, boost::is_space(), boost::token_compress_on);
	return words;
}


void CSolver::WritePositions(ostream & strm, size_t sizeSearchString,
							const PrefixFunction & prefixFunction)
{
	for (size_t index = 0; index < prefixFunction.size(); index++)
	{
		if (prefixFunction[index] == sizeSearchString)
		{
			strm << index + 1 << ' ' << index + sizeSearchString << endl;
		}
	}

}

PrefixFunction CSolver::GetPrefixFunction(const string & searchString, string inputString)
{
	PrefixFunction result;

	// TODO : delete
	size_t counter = 0;
	//inputString.insert(inputString.begin(), '#');
	//inputString.insert(inputString.begin(), searchString.begin(), searchString.end());
	result.resize(inputString.size(), 0);

	string prefix;
	string suffix;
	for (size_t index = 1; index < inputString.size(); index++)
	{
		////////////////////
		// First optimization

		size_t startIndex = 1;
		///*
		if ((index - 1) != std::numeric_limits<size_t>::max())
		{
			if (result[index - 1] > 0)
			{
				startIndex += result[index - 1];
			}
		}
		//*/

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
		/*
		for (size_t index2 = index - 1; (index2) >= startIndex; index2--)
		{
			counter++;// TODO : delete // 45 // 37

			//prefix = inputString.substr(0, index2);
			//suffix = inputString.substr(index - index2 + 1, index2);

			char lastInPrefix = inputString[index2];
			char lastInSuffix= inputString[index];

			bool symbolsIsEqual = (lastInPrefix == lastInSuffix);


			if (symbolsIsEqual)
			{
				result[index]++;
			}

			if (startIndex != 1)
			{
				result[index] += result[index - 1];
				break;
			}

			/.*
						if ((!suffix.empty() && !prefix.empty()) && (prefix == suffix))
			{
				result[index] = index2;
				break;
			}
			*./


		}
		*/
		////////////////////
		// TODO n ^ 3
		////////////////////
		///*
		for (size_t index2 = startIndex; (index2)  < index; index2++)
		{
			prefix = inputString.substr(0, index2);
			suffix = inputString.substr(index - index2 + 1, index2);
			if ((!suffix.empty() && !prefix.empty()) && (prefix == suffix))
			{
				result[index] = index2;
			}

			counter++;// TODO : delete // 45 // 37 // 19
		}
		//*/
		////////////////////
	}
	return result;// TODO
}