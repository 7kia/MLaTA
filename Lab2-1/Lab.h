#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>

struct point
{
	point();
	point(size_t first, size_t second);
	size_t x;
	size_t y;
};

typedef std::vector<int> prises;

class CLabAaSD
{
private:
	const std::string MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string MESSAGE_WIDTH_MORE_EXPECTED = "Width row more expected!!!";
	const std::string MESSAGE_HEIGHT_MORE_EXPECTED = "Height map more expected!!!";

	int		m_amountPrises = 0;
	int		m_amountNumbers = 0;
	size_t	m_countPrises = 0;
	size_t	m_countNumbers = 0;

	size_t	m_indexStart = 0;
	size_t	m_indexEnd = 0;

	size_t	m_indexMaxStart = 0;
	size_t	m_indexMaxEnd = 0;

	size_t	m_indexSecondMaxStart = 0;
	size_t	m_indexSecondMaxEnd = 0;

private:
	void	CheckAmountPrisesAndNumbers();
	void	CheckCounterWidthMap();
public:
	size_t	GetMaxCost(prises & prises);

	size_t	GetLessMaxCost(prises & prises);

	void	FillPrisesList(std::ifstream & file, prises & prises);

};