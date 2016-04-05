#include "stdafx.h"
#include "Solver.h"

void CSolver::FillPrisesList(std::ifstream &file, prises &prises)
{
	m_countPrises = 0;

	int number = 0;

	while (!file.eof())
	{
		if ((m_amountPrises == 0) && (m_amountNumbers == 0))
		{
			file >> m_amountPrises;
			file >> m_amountNumbers;

			CheckAmountPrisesAndNumbers();

			std::string passString;
			std::getline(file , passString);
		}

		file >> number;
		prises.push_back(number);
		m_countPrises++;
		CheckCountersWidthMap();
	}
	CheckCountersWidthMap();

}

void CSolver::CheckAmountPrisesAndNumbers()
{
	if ((m_amountPrises < 1) && (m_amountNumbers < 1))
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}

void CSolver::CheckCountersWidthMap()
{
	if ((static_cast<int>(m_countPrises) > m_amountPrises) || (static_cast<int>(m_countNumbers) < 0) && (m_amountNumbers > 0))
	{
		//throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}

size_t CSolver::GetMaxCost(prises & prises)
{
	int result = 0;
	int summa = 0;

	while ((m_current.m_indexStart < prises.size()) && (m_current.m_indexEnd <= prises.size()))
	{
		if ((m_current.m_indexEnd - m_current.m_indexStart) < m_amountNumbers)
		{
			if (m_current.m_indexEnd < prises.size())
			{
				summa += prises[m_current.m_indexEnd];
			}							
		}
		else
		{
			if (result <= summa)
			{
				result = summa;
				m_Max.m_indexStart = m_current.m_indexStart;
				m_Max.m_indexEnd = m_current.m_indexEnd;
			}
			m_Max.m_indexEnd = m_current.m_indexStart;
			m_Max.m_indexStart += 1;
			
			summa = 0;
		}
		m_current.m_indexEnd++;
	}
	return result;
}

size_t CSolver::GetLessMaxCost(prises & prises)
{
	int result = 0;
	int summa = 0;

	m_current.m_indexStart = 0;
	m_current.m_indexEnd = 0;

	while ((m_current.m_indexStart < prises.size()) && (m_current.m_indexEnd <= prises.size()))
	{
		if ((m_Max.m_indexStart == m_current.m_indexStart))
		{
			m_current.m_indexStart = m_Max.m_indexEnd + 1;
			m_current.m_indexEnd = m_current.m_indexStart;
		}

		if (((m_current.m_indexEnd - m_current.m_indexStart) < m_amountNumbers)
			&& (m_Max.m_indexStart != m_current.m_indexEnd))
		{
			if (m_current.m_indexEnd < prises.size())
			{
				summa += prises[m_current.m_indexEnd];
			}
		}
		else
		{
			if (result <= summa)
			{
				result = summa;
				m_SecondMax.m_indexStart = m_current.m_indexStart;
				m_SecondMax.m_indexEnd = m_current.m_indexEnd - 1;
			}
			m_current.m_indexEnd = m_current.m_indexStart;
			m_current.m_indexStart += 1;

			summa = 0;
		}
		
		m_current.m_indexEnd++;
	}

	return result;
}

SPoint::SPoint()
	:x(0),
	y(0)
{
}

SPoint::SPoint(size_t first, size_t second)
	:x(first),
	y(second)
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
