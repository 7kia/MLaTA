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

typedef std::vector<std::string> Forest;
typedef std::vector<SPoint> Queue;

class CSolver
{
private:
	const std::string MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string MESSAGE_WIDTH_MORE_EXPECTED = "Width row more expected!!!";
	const std::string MESSAGE_HEIGHT_MORE_EXPECTED = "Height map more expected!!!";

	const char charTree = '1';
	const char emptyChar = '0';
	const char searchChar = '+';

	int		m_widthMap = 0;
	int		m_heightMap = 0;
	size_t	m_countWidth = 0;
	size_t	m_countHeight = 0;
private:
	bool	CheckBorderSymbols(const Forest & Forest) const;
	void	ReplaceSymbol(Forest & Forest, char search, char replace);

	size_t	GetAmountWallsForTree(const Forest &Forest , long x , long y) const;

	void	CheckWidthAndHeight();
	void	CheckCountersMap();
public:
	void	FillForestMap(std::ifstream &file , Forest &Forest);
	size_t	GetAmountWallsForTrees(Forest &Forest);
	size_t	GetInsideWalls(size_t x, size_t y, const Forest & Forest) const;

	void	Push(Forest & Forest, size_t x, size_t y, Queue & paths);
	void	Fill(Forest & Forest, size_t x, size_t y);
	void	FillIInsidePlace(Forest &Forest);
};
