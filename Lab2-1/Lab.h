#ifndef LAB_H
#define LAB_H

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
typedef std::vector<point> Queue;

class CLabAaSD
{
private:
	const std::string MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string MESSAGE_WIDTH_MORE_EXPECTED = "Width row more expected!!!";
	const std::string MESSAGE_HEIGHT_MORE_EXPECTED = "Height map more expected!!!";

	int amountPrises = 0;
	int amountNumbers = 0;
	size_t countPrises = 0;
	size_t countNumbers = 0;

	size_t indexStart = 0;
	size_t indexEnd = 0;

	size_t indexMaxStart = 0;
	size_t indexMaxEnd = 0;

	size_t indexSecondMaxStart = 0;
	size_t indexSecondMaxEnd = 0;

private:
	bool checkAmountPrisesAndNumbers();
	bool checkCounterWidthMap();
public:
	size_t GetMaxCost(prises & prises);

	size_t GetLessMaxCost(prises & prises);

	void FillPrisesList(std::ifstream & file, prises & prises);

};
#endif