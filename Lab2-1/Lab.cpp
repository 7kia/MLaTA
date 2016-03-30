#include "stdafx.h"
#include "Lab.h"

void CLabAaSD::FillPrisesList(std::ifstream &file, prises &prises)
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

void CLabAaSD::CheckAmountPrisesAndNumbers()
{
	if ((m_amountPrises < 1) && (m_amountNumbers < 1))
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}

void CLabAaSD::CheckCountersWidthMap()
{
	if ((static_cast<int>(m_countPrises) > m_amountPrises) || (static_cast<int>(m_countNumbers) < 0) && (m_amountNumbers > 0))
	{
		throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}

size_t CLabAaSD::GetMaxCost(prises & prises)
{
	int result = 0;
	int summa = 0;
	int lastElement = prises[0];

	while ((m_indexStart < prises.size()) && (m_indexEnd <= prises.size()))
	{
		if ((m_indexEnd - m_indexStart) < m_amountNumbers)
		{
			if (m_indexEnd < prises.size())
			{
				summa += prises[m_indexEnd];
			}							
		}
		else
		{
			if (result <= summa)
			{
				result = summa;
				m_indexMaxStart = m_indexStart;
				m_indexMaxEnd = m_indexEnd;
			}
			m_indexEnd = m_indexStart;
			m_indexStart += 1;
			
			summa = 0;
		}
		m_indexEnd++;		
	}
	return result;
}

size_t CLabAaSD::GetLessMaxCost(prises & prises)
{
	int result = 0;
	int summa = 0;
	int lastElement = prises[0];

	m_indexStart = 0;
	m_indexEnd = 0;

	while ((m_indexStart < prises.size()) && (m_indexEnd <= prises.size()))
	{
		if ((m_indexMaxStart == m_indexStart))
		{
			m_indexStart = m_indexMaxEnd + 1;
			m_indexEnd = m_indexStart;
		}

		if (((m_indexEnd - m_indexStart) < m_amountNumbers)
			&& (m_indexMaxStart != m_indexEnd))
		{
			if (m_indexEnd < prises.size())
			{
				summa += prises[m_indexEnd];
			}
		}
		else
		{
			if (result <= summa)
			{
				result = summa;
				m_indexSecondMaxStart = m_indexStart;
				m_indexSecondMaxEnd = m_indexEnd - 1;
			}
			m_indexEnd = m_indexStart;
			m_indexStart += 1;

			summa = 0;
		}
		
		m_indexEnd++;
	}

	return result;
}

point::point()
	:x(0),
	y(0)
{
}

point::point(size_t first, size_t second)
	:x(first),
	y(second)
{
}
