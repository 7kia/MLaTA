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

	//inputString.insert(inputString.begin(), '#');
	//inputString.insert(inputString.begin(), searchString.begin(), searchString.end());
	result.resize(inputString.size(), 0);

	string prefix;
	string suffix;
	for (size_t index = 1; index < inputString.size(); index++)
	{
		////////////////////
		// TODO n ^ 3
		////////////////////
		for (size_t index2 = 1; (index2)  < index; index2++)
		{
			prefix = inputString.substr(0, index2);
			suffix = inputString.substr(index - index2 + 1, index2);
			if ((!suffix.empty() && !prefix.empty()) && (prefix == suffix))
			{
				result[index] = index2;
			}
		}
		////////////////////
	}
	return result;// TODO
}