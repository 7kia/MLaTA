#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <limits>
#include <array>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>

#include "SPoint.h"

struct SDataForSolver
{
	SRange firstPoint;
	SRange secondPoint;
	float radiusCircle;
};

struct SCoefficientForLineEquation
{
	// TODO: rename
	float A;
	float B;
	float C;
};

typedef std::vector<std::string> Words;
typedef std::vector<SRange> FindPositions;
typedef std::vector<size_t> PrefixFunction;

class CSolver
{
private:
	const std::string				MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string				MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
	const std::string				MESSAGE_WIDTH_MORE_EXPECTED = "Amount strings more expected!!!";

	const int						AMOUNT_ARGUMENTS = 5;
protected:
	void							CheckStringsCounters();

	float							GetDistanseLineConectTwoPoints(const std::string & inputString);
	Words							SplitWords(std::string const & text);
	SDataForSolver					ExtractData(const std::string & inputString);
	SCoefficientForLineEquation		GetLineEquation(const SRange & firstPosition, const SRange & secondPosition);

	std::pair<SRange, SRange>		GetPointsIntersection(const SDataForSolver & data);
	float							GetLineLength(const SRange & firstPosition, const SRange & secondPosition);
	float							GetLineLength(const std::pair<SRange, SRange> & pair);

	float							GetCircleArcLength(const std::pair<SRange, SRange>& pair, float radius);
	float							GetCircleArcLength(const SRange & firstPosition, const SRange & secondPosition, float radius);

	float							GetDistanseBetweenPointAndTangent(const SRange & point, const float radius);
	float							GetAngleBetweenCathetusAndHypotenuse(float cathetus, float hypotenuse);

	boost::numeric::ublas::matrix<float>	GetRotationMatrix(float angle, bool considered—ounterclockwise);

	SRange							GetPointTangent(const SRange & point, const SRange & pointIntersection, const float radius);
	SRange							GetNearPoint(const SRange & point, const std::pair<SRange, SRange>& pointsIntersection);

	//////////////////////////////////////////////////////////////////
	void							WritePositions(std::ostream &strm, const PrefixFunction & prefixFunction);
};

float GetDiscriminant(float A, float B, float C);
float Dot(const SRange & firstPosition, const SRange & secondPosition);