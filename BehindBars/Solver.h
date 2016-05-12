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
static const float ACCURACY = 0.2f;

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

	float							GetLengthPerdendicular(SPoint intersectionPoint
															, SPoint startFirstLine
															, SPoint endFirstLine
															, SPoint startSecondLine
															, SPoint endSecondLine);

	bool							IsParallel(const SCoefficientForLineEquation & firstLineEquation
												, const SCoefficientForLineEquation & secondLineEquation);

	bool							IsNotPerdendiculars(SPoint firstSourceNormal
														, SPoint secondSourceNormal
														, SPoint startCheckLine
														, SPoint endCheckLine);

	float							SearchFromNearPoints(const SDataForSolver & data);

	bool							CheckIntersection(const SPoint & point
														, const SPoint & startLine
														, const SPoint & endLine);

	SCoefficientForLineEquation		GetLineEquation(const SPoint & firstPosition, const SPoint & secondPosition);
	SCoefficientForLineEquation		GetLineEquationForPerpendicular(const SPoint & point
																	, const SCoefficientForLineEquation & equation);

	float							GetLineLength(const SPoint & firstPosition, const SPoint & secondPosition);
	float							GetLineLength(const std::pair<SPoint, SPoint> & pair);

	SPoint							GetNearPoint(const SPoint & point
												, const std::pair<SPoint, SPoint>& pointsIntersection);
	SPoint							GetNearPoint(const SPoint & point
												, const SPoint & startPointLine
												, const SPoint & endPointLine);

	SPoint							GetPointIntersectionByPerpendicular(const SPoint & point
																		, const SPoint & startPointLine
																		, const SPoint & endPointLine);

	float							GetAngleBetweenVectors(SPoint startFirst
															, SPoint endFirst
															, SPoint startSecond
															, SPoint endSecond);
	SPoint							GetPointIntersection(const SCoefficientForLineEquation & first, const SCoefficientForLineEquation & second);
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