#ifndef LAB_H
#define LAB_H

#pragma once
#include "stdafx.h"

#include <string>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <map>

struct point
{
	point();
	point(size_t first, size_t second);
	size_t x;
	size_t y;
};

typedef std::vector<int> intVec;

class CLabAaSD
{
private:
	const std::string MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string MESSAGE_AMOUNT_MORE_EXPECTED = "Width row more expected!!!";

	int amountElements = 0;
	size_t countElements = 0;
private:
	bool checkAmountElements();
	bool checkCounterElements();
public:
	void FillVector(std::ifstream &file , intVec &vec);
	void FindAmountRepeat(intVec &vec);
};
#endif