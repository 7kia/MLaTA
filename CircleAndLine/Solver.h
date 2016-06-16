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

#pragma warning (disable: 4996)


#include "SPoint.h"

struct SDataForSolver
{
	SPoint firstPoint;
	SPoint secondPoint;
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

class CSolver
{
private:
	const std::string				MESSAGE_INCORRECT_SIZE = "Size map must have value more 0!!!";
	const std::string				MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
	const std::string				MESSAGE_WIDTH_MORE_EXPECTED = "Amount strings more expected!!!";

	const int						AMOUNT_ARGUMENTS = 5;
private:
	void							CheckAmountStrings();
protected:
	size_t							m_amountStrings = 0;
	size_t							m_countStrings = 0;

protected:
	void							CheckStringsCounters();

	float							GetDistanseLineConectTwoPoints(const std::string & inputString);
	Words							SplitWords(std::string const & text);
	SDataForSolver					ExtractData(std::ifstream & file);
	SDataForSolver					ExtractData(const std::string & inputString);
	SCoefficientForLineEquation		GetLineEquation(const SPoint & firstPosition, const SPoint & secondPosition);

	std::pair<SPoint, SPoint>		GetPointsIntersection(const SDataForSolver & data);
	bool							CheckIntersection(const SPoint & point
													, const SPoint & startLine
													, const SPoint & endLine);
	float							GetLineLength(const SPoint & firstPosition, const SPoint & secondPosition);
	float							GetLineLength(const std::pair<SPoint, SPoint> & pair);

	float							GetCircleArcLength(const std::pair<SPoint, SPoint>& pair, float radius);
	float							GetCircleArcLength(const SPoint & firstPosition, const SPoint & secondPosition, float radius);

	float							GetDistanseBetweenPointAndTangent(const SPoint & point, const float radius);
	float							GetAngleBetweenCathetusAndHypotenuse(float cathetus, float hypotenuse);

	boost::numeric::ublas::matrix<float>	GetRotationMatrix(float angle, bool considered—ounterclockwise);

	SPoint							GetPointTangent(const SPoint & point, const SPoint & pointIntersection, const float radius);
	SPoint							GetNearPoint(const SPoint & point, const std::pair<SPoint, SPoint>& pointsIntersection);

};

float GetDiscriminant(float A, float B, float C);
float Dot(const SPoint & firstPosition, const SPoint & secondPosition);