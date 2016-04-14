#include "stdafx.h"
#include "Solver.h"

Graph CSolver::ReadGraph(std::ifstream &file)
{
	Graph result;
	m_countRoads = 0;

	int firstTown = 0;
	int secondTown = 0;
	int cargo = 0;
	while (!file.eof())
	{
		if ((m_amountTowns == 0) && (m_amountRoads == 0))
		{
			file >> m_amountTowns;
			file >> m_amountRoads;

			CheckAmountTownsAndRoads();

			std::string passString;
			std::getline(file , passString);

			result.resize(m_amountTowns, std::vector<int>(m_amountTowns, 0));
		}

		file >> firstTown;
		file >> secondTown;
		file >> cargo;
		result[--firstTown][--secondTown] = cargo;

		m_countRoads++;
		CheckCountersWidthMap();
	}
	CheckCountersWidthMap();

	return result;
}

void CSolver::CheckAmountTownsAndRoads()
{
	if ((m_amountTowns < 1) && (m_amountRoads < 1))
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}

void CSolver::CheckCountersWidthMap()
{
	if ((static_cast<int>(m_countRoads) > m_amountRoads))
	{
		//throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}

SPoint::SPoint()
	: x(0)
	, y(0)
{
}

SPoint::SPoint(size_t first, size_t second)
	: x(first)
	, y(second)
{
}

SRange::SRange()
{
}

SRange::SRange(size_t indexStart, size_t indexEnd)
{
	m_indexStart = indexStart;
	m_indexEnd = indexEnd;
}
