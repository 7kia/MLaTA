#include "stdafx.h"
#include "Solver.h"

using namespace boost::numeric::ublas;

template<typename T>
bool IsBetween(T value, T first, T second)
{
	if (first > second)
	{
		T periphery = first;
		first = second;
		second = periphery;
	}
	return (second >= value) && (first <= value);
}

bool IsEqual(float a, float b)
{
	return fabs(a - b) < ACCURACY;
}

SDataForSolver CSolver::ExtractData(std::istream & strm)
{
	SDataForSolver result;

	strm >> result.startFirstLine.x;
	strm >> result.startFirstLine.y;

	strm >> result.endFirstLine.x;
	strm >> result.endFirstLine.y;

	strm >> result.startSecondLine.x;
	strm >> result.startSecondLine.y;

	strm >> result.endSecondLine.x;
	strm >> result.endSecondLine.y;

	return result;
}

float CSolver::GetDistanseBetweenLines(const SDataForSolver & data)
{
	SCoefficientForLineEquation firstLineEquation = GetLineEquation(data.startFirstLine, data.endFirstLine);
	SCoefficientForLineEquation secondLineEquation = GetLineEquation(data.startSecondLine, data.endSecondLine);

	SPoint pointIntersection = GetPointIntersection(firstLineEquation, secondLineEquation);

	if (IsIntersectionpoint(pointIntersection
		, data.startFirstLine
		, data.endFirstLine
		, data.startSecondLine
		, data.endSecondLine))
	{
		return 0.f;
	}

	if (IsParallel(firstLineEquation, secondLineEquation))
	{
		// p1 - point intersection by perpendicular by first point
		SPoint p1 = GetPointIntersectionByPerpendicular(data.startFirstLine, data.startSecondLine, data.endSecondLine);
		SPoint p2 = GetPointIntersectionByPerpendicular(data.endFirstLine, data.startSecondLine, data.endSecondLine);

		if (IsNotPerdendiculars(p1
								, p2
								, data.startSecondLine
								, data.endSecondLine))
		{
			SPoint p3 = GetPointIntersectionByPerpendicular(data.startSecondLine, data.startFirstLine, data.endFirstLine);
			SPoint p4 = GetPointIntersectionByPerpendicular(data.endSecondLine, data.startFirstLine, data.endFirstLine);

			///////////////////////
			// try on second line
			if (IsNotPerdendiculars(p3
									, p4
									, data.startFirstLine
									, data.endFirstLine))
			{
				return SearchFromNearPoints(data);
			}

			if (CheckIntersection(p3
								, data.startFirstLine
								, data.endFirstLine))
			{
				return GetLineLength(p3, GetPointIntersectionByPerpendicular(p3
																			, data.startSecondLine
																			, data.endSecondLine));
			}
			else if (CheckIntersection(p4
									, data.startFirstLine
									, data.endFirstLine))
			{
				return GetLineLength(p4, GetPointIntersectionByPerpendicular(p4
																			, data.startSecondLine
																			, data.endSecondLine));
			}
		}
		///////////////////////
		// if not intersect
		if (CheckIntersection(p1
							, data.startSecondLine
							, data.endSecondLine))
		{
			return GetLineLength(p1, data.startFirstLine);
		}
		else if (CheckIntersection(p2
								, data.startSecondLine
								, data.endSecondLine))
		{
			return GetLineLength(p2, data.endFirstLine);
		}
		
	}
	else
	{

		float near = SearchFromNearPoints(data);


		if (pointIntersection == NO_POINT)
			
		{
			return near;
		}

		/*
		if (CheckIntersection(pointIntersection
							, data.startFirstLine
							, data.endFirstLine))
		{
			SPoint nearPoint = GetNearPoint(pointIntersection
											, data.startSecondLine
											, data.endSecondLine);

			return std::min(GetLineLength(pointIntersection, nearPoint), near);
		}

		if (CheckIntersection(pointIntersection
			, data.startSecondLine
			, data.endSecondLine))
		{
			SPoint nearPoint = GetNearPoint(pointIntersection
											, data.startFirstLine
											, data.endSecondLine);
			return std::min(GetLineLength(pointIntersection, nearPoint), near);
		}
		*/

		// L1 - length Perdendicular From First To Second
		float L1 = GetLengthPerdendicular(pointIntersection
										, data.startFirstLine
										, data.endFirstLine
										, data.startSecondLine
										, data.endSecondLine);

		// L2 - length Perdendicular From Second To First
		float L2 = GetLengthPerdendicular(pointIntersection
										, data.startSecondLine
										, data.endSecondLine
										, data.startFirstLine
										, data.endFirstLine);

		if (L1 > ACCURACY)
		{
			return std::min(near, L1);
		}
		else if (L2 > ACCURACY)
		{
			return std::min(near, L2);
		}

		return near;
	}
	return 0.0f;
}

float CSolver::GetLengthPerdendicular(SPoint intersectionPoint
									, SPoint startFirstLine
									, SPoint endFirstLine
									, SPoint startSecondLine
									, SPoint endSecondLine)
{
	if (CheckIntersection(intersectionPoint
						, startFirstLine
						, endFirstLine))
	{
		SPoint nearPoint = GetNearPoint(intersectionPoint
										, startSecondLine
										, endSecondLine);

		return GetLineLength(intersectionPoint, nearPoint);
	}
}

bool CSolver::IsParallel(const SCoefficientForLineEquation & firstLineEquation
						, const SCoefficientForLineEquation & secondLineEquation)
{
	float firstProportion = firstLineEquation.A / secondLineEquation.A;
	float secondProportion = firstLineEquation.B / secondLineEquation.B;

	return IsEqual(firstProportion, secondProportion);// && (aHaveEqualSign && bHaveEqualSign);
}


bool CSolver::IsNotPerdendiculars(SPoint firstSourceNormal
								, SPoint secondSourceNormal
								, SPoint startCheckLine
								, SPoint endCheckLine)
{
	bool result = CheckIntersection(firstSourceNormal, startCheckLine, endCheckLine);
	result |= CheckIntersection(secondSourceNormal, startCheckLine, endCheckLine);

	return !result;
}

bool CSolver::IsIntersectionpoint(SPoint intersectionPoint
								, SPoint startFirstLine
								, SPoint endFirstLine
								, SPoint startSecondLine
								, SPoint endSecondLine)
{
	bool result = CheckIntersection(intersectionPoint, startFirstLine, endFirstLine);
	result &= CheckIntersection(intersectionPoint, startSecondLine, endSecondLine);

	return result;
}

float CSolver::SearchFromNearPoints(const SDataForSolver & data)
{
	SPoint nearPointToFirst = GetNearPoint(data.startFirstLine, data.startSecondLine, data.endSecondLine);
	SPoint nearPointToSecond = GetNearPoint(data.endFirstLine, data.startSecondLine, data.endSecondLine);

	float distanseFromFirst = GetLineLength(data.startFirstLine, nearPointToFirst);
	float distanseFromSecond = GetLineLength(data.endFirstLine, nearPointToSecond);

	return std::min(distanseFromFirst, distanseFromSecond);
}

bool CSolver::CheckIntersection(const SPoint & point
								, const SPoint & startLine
								, const SPoint & endLine)
{
	SCoefficientForLineEquation lineEquation = GetLineEquation(startLine, endLine);

	float result = (lineEquation.A * point.x) + (lineEquation.B * point.y) + lineEquation.C;
	

	bool intersectX = IsBetween(point.x, startLine.x, endLine.x);
	bool intersectY = IsBetween(point.y, startLine.y, endLine.y);

	return (result == 0.f)
			&& intersectY
			&& intersectX;
}


SCoefficientForLineEquation CSolver::GetLineEquation(const SPoint &firstPosition, const SPoint & secondPosition)
{
	SCoefficientForLineEquation result;

	if (secondPosition.x != firstPosition.x)
	{
		if (secondPosition.y != firstPosition.y)
		{
			result.C = -firstPosition.x / (secondPosition.x - firstPosition.x);
			result.C *= (secondPosition.y - firstPosition.y);
			result.C -= -firstPosition.y / (secondPosition.y - firstPosition.y)
				*  (secondPosition.x - firstPosition.x);

			result.A = secondPosition.y - firstPosition.y;
			result.B = firstPosition.x - secondPosition.x;
		}
		else
		{
			result.B = 1;
			result.C = -secondPosition.y;
		}
	}
	else
	{
		result.A = 1;
		result.C = -secondPosition.x;		
	}

	if (result.B != 0.f)
	{
		result.A /= abs(result.B);
		result.B /= abs(result.B);
		result.C /= abs(result.B);
	}

	return result;
}


SCoefficientForLineEquation CSolver::GetLineEquationForPerpendicular(const SPoint &point
																	, const SCoefficientForLineEquation & equation)
{
	SCoefficientForLineEquation result;

	result.A = -equation.B;
	result.B = equation.A;
	result.C = (equation.A + equation.B) * point.x;
	
	result.C += (equation.B - equation.A) * point.y;
	//result.C += equation.C;
	
	return result;
}



float GetDiscriminant(float A, float B, float C)
{
	return sqrt((B * B) - (4.f * A * C));
}


float CSolver::GetLineLength(const SPoint & firstPosition, const SPoint & secondPosition)
{
	float differenceX = firstPosition.x - secondPosition.x;
	float differenceY = firstPosition.y - secondPosition.y;

	return sqrt(differenceX * differenceX + differenceY * differenceY);
}


float CSolver::GetLineLength(const std::pair<SPoint, SPoint>& pair)
{
	return GetLineLength(pair.first, pair.second);
}


// —кал€рное умножение
float Dot(const SPoint & firstPosition, const SPoint & secondPosition)
{
	return (firstPosition.x * secondPosition.x) + (firstPosition.y * secondPosition.y);
}


SPoint CSolver::GetNearPoint(const SPoint & point, const std::pair<SPoint, SPoint> &linePoints)
{
	return GetNearPoint(point, linePoints.first, linePoints.second);
}

SPoint CSolver::GetNearPoint(const SPoint & point, const SPoint & startPointLine, const SPoint & endPointLine)
{
	float firstDistance = GetLineLength(point, startPointLine);
	float secondDistance = GetLineLength(point, endPointLine);

	SPoint result;

	if (firstDistance > secondDistance)
	{
		result = endPointLine;
	}
	else
	{
		result = startPointLine;
	}

	return result;
}

SPoint CSolver::GetPointIntersectionByPerpendicular(const SPoint & point
													, const SPoint & startPointLine
													, const SPoint & endPointLine)
{
	SCoefficientForLineEquation lineEquation = GetLineEquation(startPointLine, endPointLine);
	SCoefficientForLineEquation lineEquationForPerpendicular = GetLineEquationForPerpendicular(point, lineEquation);

	return GetPointIntersection(lineEquation, lineEquationForPerpendicular);
}


float CSolver::GetAngleBetweenVectors(SPoint startFirst
									, SPoint endFirst
									, SPoint startSecond
									, SPoint endSecond)
{
	float lenthFirst = GetLineLength(startFirst, endFirst);
	float lenthSecond = GetLineLength(startSecond, endSecond);

	// p1 - coordinate end vector in system in start coordinate system
	SPoint p1 = SPoint(endFirst.x - startFirst.x, endFirst.y - startFirst.y);
	SPoint p2 = SPoint(endSecond.x - startSecond.x, endSecond.y - startSecond.y);

	return Dot(p1, p2) / (lenthFirst * lenthSecond);
}

SPoint CSolver::GetPointIntersection(const SCoefficientForLineEquation & first
									, const SCoefficientForLineEquation & second)
{

	if ((first.A == second.A) && (first.B == second.B))
	{
		return NO_POINT;
	}
	float y = -((first.C * second.A) - (second.C * first.A));

	float denumerator = ((first.B * second.A) - (first.A * second.B));
	if (denumerator == 0.f)
	{
		y = denumerator;
	}
	else
	{
		y /= denumerator;
	}

	float x = (first.C + first.B * y);
	denumerator = -first.A;
	if (denumerator != 0.f)
	{
		x /= denumerator;
	}
	else
	{
		return NO_POINT;
	}

	return SPoint(x, y);
}

SCoefficientForLineEquation::SCoefficientForLineEquation()
{
}

SCoefficientForLineEquation::SCoefficientForLineEquation(float a, float b, float c)
{
	A = a;
	B = b;
	C = c;
}
