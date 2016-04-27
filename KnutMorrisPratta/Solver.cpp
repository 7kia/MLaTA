#include "stdafx.h"
#include "Solver.h"

using namespace boost::numeric::ublas;


// TODO : delete
std::vector<std::string> SplitWords(std::string const& text)
{
	std::string trimmed = boost::trim_copy(text);

	std::vector<std::string> words;
	boost::split(words, trimmed, boost::is_space(), boost::token_compress_on);
	return words;
}


void CSolver::WritePositions(std::ostream & strm, size_t sizeSearchString,
							const PrefixFunction & prefixFunction)
{
	for (size_t index = 0; index < prefixFunction.size(); index++)
	{
		if (prefixFunction[index] == sizeSearchString)
		{
			strm << index + 1 << ' ' << index + sizeSearchString << std::endl;
		}
	}

}

PrefixFunction CSolver::GetPrefixFunction(const std::string & searchString, const std::string & inputString)
{
	SRange<size_t> current;

	PrefixFunction result;
	return result;// TODO
}