#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>

struct SPoint
{
	SPoint();
	SPoint(size_t first, size_t second);
	size_t x;
	size_t y;
};

struct SRange
{
	SRange();
	SRange(size_t indexStart, size_t indexEnd);
	size_t	m_indexStart = 0;
	size_t	m_indexEnd = 0;
};

typedef std::vector<int> prises;

class CSolver
{
private:
	const std::string MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string MESSAGE_WIDTH_MORE_EXPECTED = "Width row more expected!!!";
	const std::string MESSAGE_HEIGHT_MORE_EXPECTED = "Height map more expected!!!";

	int		m_amountPrises = 0;
	int		m_amountNumbers = 0;
	size_t	m_countPrises = 0;
	size_t	m_countNumbers = 0;

	SRange	m_current;
	SRange	m_Max;
	SRange	m_SecondMax;

private:
	void	CheckAmountPrisesAndNumbers();
	void	CheckCountersWidthMap();
public:
	size_t	GetMaxCost(prises & prises);

	size_t	GetLessMaxCost(prises & prises);

	void	FillPrisesList(std::ifstream & file, prises & prises);

};