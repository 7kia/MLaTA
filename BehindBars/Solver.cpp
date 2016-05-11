#include "stdafx.h"
#include "Solver.h"

using namespace boost::numeric::ublas;

// TODO delete
/*
void CSolver::CheckAmountStrings()
{
	if (m_amountStrings < 1)
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_SIZE);
	}
}


void CSolver::CheckStringsCounters()
{
	if ((static_cast<int>(m_countStrings) > m_amountStrings))
	{
		throw std::invalid_argument(MESSAGE_WIDTH_MORE_EXPECTED);
	}
}


std::vector<std::string> CSolver::SplitWords(std::string const& text)
{
	std::string trimmed = boost::trim_copy(text);

	std::vector<std::string> words;
	boost::split(words, trimmed, boost::is_space(), boost::token_compress_on);
	return words;
}


SDataForSolver CSolver::ExtractData(const std::string & inputString)
{
	SDataForSolver result;
	Words arguments = SplitWords(inputString);

	if (arguments.size() == AMOUNT_ARGUMENTS)
	{
		result.firstPoint.x = stof(arguments[0]);
		result.firstPoint.y = stof(arguments[1]);

		result.secondPoint.x = stof(arguments[2]);
		result.secondPoint.y = stof(arguments[3]);

		result.radiusCircle = stof(arguments[4]);
	}
	else
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS);
	}

	return result;
}



std::pair<SPoint, SPoint> CSolver::GetPointsIntersection(const SDataForSolver & data)
{
SCoefficientForLineEquation lineEquation = GetLineEquation(data.firstPoint, data.secondPoint);

float A = lineEquation.B * lineEquation.B + lineEquation.A * lineEquation.A;
float B = 2.f * lineEquation.A * lineEquation.C;
float C = lineEquation.C * lineEquation.C;
C -= lineEquation.B * lineEquation.B * data.radiusCircle * data.radiusCircle;

float discriminant = GetDiscriminant(A, B, C);
float firstRoot = 0.f;
float secondRoot = 0.f;

SPoint firstPoint;
SPoint secomdPoint;

if (discriminant >= 0)
{
float denumerator = 2.f * A;

firstRoot = -(B * B) + discriminant;
firstRoot /= denumerator;

secondRoot = -(B * B) - discriminant;
secondRoot /= denumerator;

firstPoint.x = firstRoot;
firstPoint.y = -(lineEquation.A * firstRoot + lineEquation.C) / lineEquation.B;

secomdPoint.x = secondRoot;
secomdPoint.y = -(lineEquation.A * secondRoot + lineEquation.C) / lineEquation.B;
}

return std::pair<SPoint, SPoint>(firstPoint, secomdPoint);// TOOD : event when points no
}


float CSolver::GetCircleArcLength(const std::pair<SPoint, SPoint>& pair, float radius)
{
return GetCircleArcLength(pair.first, pair.second, radius);
}


float CSolver::GetCircleArcLength(const SPoint & firstPosition, const SPoint & secondPosition, float radius)
{
float lenthFirst = radius;
float lenthSecond = radius;

float cosinus = Dot(firstPosition, secondPosition) / (lenthFirst * lenthSecond);

return abs(acosf(cosinus)) * radius;
}


float  CSolver::GetDistanseBetweenPointAndTangent(const SPoint & point, const float radius)
{
float distanseBetweenPointAndCenter = GetLineLength(SPoint(), point);

return sqrt(distanseBetweenPointAndCenter * distanseBetweenPointAndCenter
- radius * radius);
}


float CSolver::GetAngleBetweenCathetusAndHypotenuse(float cathetus, float hypotenuse)
{
return abs(acosf(cathetus / hypotenuse));
}


matrix<float> CSolver::GetRotationMatrix(float angle, bool consideredÑounterclockwise)
{
float coefficient = 1.f;

if (consideredÑounterclockwise)
{
coefficient *= -1.f;
}

matrix<float> result(2, 2);
result.at_element(0, 0) = cos(angle);
result.at_element(1, 1) = cos(angle);

result.at_element(0, 1) = coefficient * sin(angle);
result.at_element(1, 0) = coefficient  * -sin(angle);

return result;
}


SPoint CSolver::GetPointTangent(const SPoint & point, const SPoint & pointIntersection, const float radius)
{
float hypotenuse = GetLineLength(SPoint(), point);
// R -radiuse circle
float angleBetweenRAndCathtus = GetAngleBetweenCathetusAndHypotenuse(radius, hypotenuse);

// ïðîòèâ÷àñîâîé
bool consideredÑounterclockwise = point.x < 0.f;

matrix<float> vector(1, 2);
vector.at_element(0, 0) = pointIntersection.x;
vector.at_element(0, 1) = pointIntersection.y;

matrix<float> rotationMatrix = GetRotationMatrix(angleBetweenRAndCathtus, consideredÑounterclockwise);
vector = prod(vector, rotationMatrix);// prod - multiply

return SPoint(vector.at_element(0, 0), vector.at_element(0, 1));
}


float CSolver::GetDistanseLineConectTwoPoints(const std::string & inputString)
{
SDataForSolver data = ExtractData(inputString);

std::pair<SPoint, SPoint> pointsIntersection = GetPointsIntersection(data);

SPoint nearAboutFirst = GetNearPoint(data.firstPoint, pointsIntersection);
SPoint nearAboutSecond = GetNearPoint(data.secondPoint, pointsIntersection);

SPoint firstPointTangent = GetPointTangent(data.firstPoint, nearAboutFirst, data.radiusCircle);
SPoint secondPointTangent = GetPointTangent(data.secondPoint, nearAboutSecond, data.radiusCircle);

float result = 0.f;

if ((pointsIntersection.first != SPoint()) && (pointsIntersection.second != SPoint()))
{
result += GetLineLength(data.firstPoint, firstPointTangent);
result += GetLineLength(data.secondPoint, secondPointTangent);

result += GetCircleArcLength(firstPointTangent, secondPointTangent, data.radiusCircle);
}
else
{
result = GetLineLength(data.firstPoint, data.secondPoint);
}

return result;
}

*/


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

	// TODO transfer high
	//if (IsEqual(firstLineEquation.C, secondLineEquation.C))
	//{
	//	return 0.f;
	//}

	//////////////////////////////////////////////////////////
	// if is parallel
	if ((IsEqual(firstLineEquation.A, secondLineEquation.A))
		&&
		(IsEqual(firstLineEquation.B, secondLineEquation.B)))
	{


		// p1 - point intersection by perpendicular by first point
		SPoint p1 = GetPointIntersectionByPerpendicular(data.startFirstLine, data.startSecondLine, data.endSecondLine);
		SPoint p2 = GetPointIntersectionByPerpendicular(data.endFirstLine, data.startSecondLine, data.endSecondLine);

		///////////////////////
		// try on second line
		if (!CheckIntersection(p1, data.startSecondLine, data.endSecondLine)
			&& !CheckIntersection(p2, data.startSecondLine, data.endSecondLine))
		{
			p1 = GetPointIntersectionByPerpendicular(data.startSecondLine, data.startFirstLine, data.endFirstLine);
			p2 = GetPointIntersectionByPerpendicular(data.endSecondLine, data.startFirstLine, data.endFirstLine);

			///////////////////////
			// try on second line
			if (!CheckIntersection(p1, data.startSecondLine, data.endSecondLine)
				&& !CheckIntersection(p2, data.startSecondLine, data.endSecondLine))
			{
				return SearchFromNearPoints(data);
			}
			///////////////////////
			else if (p1 != NO_POINT)
			{
				return GetLineLength(p1, data.startFirstLine);
			}
			else if (p2 != NO_POINT)
			{
				return GetLineLength(p2, data.endFirstLine);
			}
		}
		///////////////////////
		else if (p1 != NO_POINT)
		{
			return GetLineLength(p1, data.startFirstLine);
		}
		else if (p2 != NO_POINT)
		{
			return GetLineLength(p2, data.endFirstLine);
		}





		
	}
	else
	{
		return SearchFromNearPoints(data);
	}
	return 0.0f;
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

	float y = -((lineEquation.A * point.x) + lineEquation.C);
	y /= lineEquation.B;

	return (y == point.y) && (y <= endLine.y) && (y >= startLine.y);
}

SCoefficientForLineEquation CSolver::GetLineEquation(const SPoint &firstPosition, const SPoint & secondPosition)
{
	SCoefficientForLineEquation result;

	if (secondPosition.x != firstPosition.x)
	{
		if (secondPosition.y != firstPosition.y)
		{
			result.A = (secondPosition.y - firstPosition.y) / (secondPosition.x - firstPosition.x);

			result.C = -firstPosition.x / (secondPosition.x - firstPosition.x);
			result.C *= (secondPosition.y - firstPosition.y);
			result.C -= -firstPosition.y / (secondPosition.y - firstPosition.y)
				*  (secondPosition.x - firstPosition.x);

			result.B = -1.f / result.A;
		}
		else
		{
			result.B = 1;
			result.C = secondPosition.y;
		}
	}
	else
	{
		result.A = 1;
		result.C = secondPosition.x;		
	}
	return result;
}


SCoefficientForLineEquation CSolver::GetLineEquationForPerpendicular(const SPoint &point
																	, const SCoefficientForLineEquation & equation)
{
	SCoefficientForLineEquation result;

	result.A = -equation.B;
	result.B = equation.A;
	result.C = (equation.A * point.x) - (point.y * equation.B);
	
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


// Ñêàëÿðíîå óìíîæåíèå
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

	/*
		SPoint nearLinePointToSourcePoint = GetNearPoint(point, startPointLine, endPointLine);
	SPoint farLinePointToSourcePoint = (nearLinePointToSourcePoint == startPointLine) ? endPointLine : startPointLine;
	float hypotenuse = GetLineLength(point, nearLinePointToSourcePoint);

	// cosinus - angle between hypotenuse and cathtus
	float cosinus = GetAngleBetweenVectors(point
											, nearLinePointToSourcePoint
											, nearLinePointToSourcePoint
											, farLinePointToSourcePoint);
	float sinAngle = sqrt(1.f - cosinus * cosinus);

	*/

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
	float y = ((first.C * second.A) - (second.C * first.A));

	float denumerator = ((second.B * first.A) - (first.B * second.A));
	if (denumerator != std::numeric_limits<float>::min())
	{
		y /= ((second.B * first.A) - (first.B * second.A));
	}
	else
	{
		return NO_POINT;
	}

	float x = (first.C + first.B * y);
	denumerator = -first.A;
	if (denumerator != std::numeric_limits<float>::min())
	{
		x /= denumerator;
	}
	else
	{
		return NO_POINT;
	}
	///*
	//float x2 = -(second.C + second.B * y);
	//x2 /= second.A;
	//assert(x != x2);

	//*/
	return SPoint(x, y);
}