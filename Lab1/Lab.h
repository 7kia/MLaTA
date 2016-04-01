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

typedef std::vector<std::string> forest;
typedef std::vector<point> Queue;

class CLabAaSD
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
	bool	CheckBorderSymbols(forest & forest);
	void	ReplaceSymbol(forest & forest, char search, char replace);

	size_t	GetAmountWallsForTree(forest &forest , int x , int y);

	void	CheckWidthAndHeight();
	void	CheckCountersMap();
public:
	void	FillForestMap(std::ifstream &file , forest &forest);
	size_t	GetAmountWallsForTrees(forest &forest);
	size_t	GetInsideWalls(size_t x, size_t y, forest & forest);
	bool	SearchEmptyPlace(int & x, int & y, forest & forest);

	void	Push(forest & forest, size_t x, size_t y, Queue & paths);
	void	Fill(forest & forest, size_t x, size_t y);
	void	FillIInsidePlace(forest &forest);
};
