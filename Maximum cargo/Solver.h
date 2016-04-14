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

typedef std::vector<std::vector<int>> Graph;

class CSolver
{
private:
	const std::string MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string MESSAGE_WIDTH_MORE_EXPECTED = "Width row more expected!!!";
	const std::string MESSAGE_HEIGHT_MORE_EXPECTED = "Height map more expected!!!";

	int		m_amountTowns = 0;
	int		m_amountRoads = 0;
	size_t	m_countRoads = 0;
	size_t	m_countNumbers = 0;

	SRange	m_current;
	SRange	m_max;
	SRange	m_secondMax;

private:
	void	CheckAmountTownsAndRoads();
	void	CheckCountersWidthMap();
protected:
	Graph	ReadGraph(std::ifstream & file);

public:
	//size_t	GetMaxCost(PrisesArray & prises);

	//size_t	GetLessMaxCost(PrisesArray & prises);

	//void	FillPrisesList(std::ifstream & file, PrisesArray & prises);

};