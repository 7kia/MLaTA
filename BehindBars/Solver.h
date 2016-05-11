#pragma once
#include "stdafx.h"

#include <string>
#include <algorithm>
#include <iostream>// for std::cin and std::cout
#include <fstream>
#include <vector>
#include <limits>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>

#include "SPoint.h"


struct SDataForSolver
{
	SPoint startFirstLine;
	SPoint endFirstLine;
	SPoint startSecondLine;
	SPoint endSecondLine;
};



struct SCoefficientForLineEquation
{
	// TODO: rename
	float A = 0.f;
	float B = 0.f;
	float C = 0.f;
};

typedef std::vector<std::string> Words;
static const float ACCURACY = 0.01f;

class CSolver
{
private:
	const std::string				MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string				MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
	const std::string				MESSAGE_WIDTH_MORE_EXPECTED = "Amount strings more expected!!!";

	const int						AMOUNT_ARGUMENTS = 5;
	const int						AMOUNT_POINTS = 4;
private:
	// TODO
protected:
	// TODO
protected:
	SDataForSolver					ExtractData(std::istream & strm);
	float							GetDistanseBetweenLines(const SDataForSolver & data);

	SCoefficientForLineEquation		GetLineEquation(const SPoint & firstPosition, const SPoint & secondPosition);

	float							GetLineLength(const SPoint & firstPosition, const SPoint & secondPosition);
	float							GetLineLength(const std::pair<SPoint, SPoint> & pair);

	SPoint							GetNearPoint(const SPoint & point
												, const std::pair<SPoint, SPoint>& pointsIntersection);
	SPoint							GetNearPoint(const SPoint & point
												, const SPoint & startPointLine
												, const SPoint & endPointLine);

	//Words							SplitWords(std::string const & text);
	//SDataForSolver					ExtractData(const std::string & inputString);

	//std::pair<SPoint, SPoint>		GetPointsIntersection(const SDataForSolver & data);

	//float							GetCircleArcLength(const std::pair<SPoint, SPoint>& pair, float radius);
	//float							GetCircleArcLength(const SPoint & firstPosition, const SPoint & secondPosition, float radius);

	//float							GetDistanseBetweenPointAndTangent(const SPoint & point, const float radius);
	//float							GetAngleBetweenCathetusAndHypotenuse(float cathetus, float hypotenuse);


	//SPoint							GetPointTangent(const SPoint & point, const SPoint & pointIntersection, const float radius);

};

float GetDiscriminant(float A, float B, float C);
float Dot(const SPoint & firstPosition, const SPoint & secondPosition);

bool IsEqual(float first, float second);