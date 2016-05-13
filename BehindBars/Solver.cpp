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

bool CSolver::IsPerpendicularLines(const SCoefficientForLineEquation & firstLineEquation
									, const SCoefficientForLineEquation & secondLineEquation)
{
	return ((firstLineEquation.A == -secondLineEquation.B) && (firstLineEquation.B == secondLineEquation.B))
		||
		((firstLineEquation.B == -secondLineEquation.A) && (firstLineEquation.A == secondLineEquation.A));
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

	return (result == 0.f) && intersectY
				&& intersectX;
}


SCoefficientForLineEquation CSolver::GetLineEquation(const SPoint &firstPosition, const SPoint & secondPosition)
{
	SCoefficientForLineEquation result;
	///*
	if (secondPosition.x != firstPosition.x)
	{
		if (secondPosition.y != firstPosition.y)
		{
			
			
			
						//result.A = (secondPosition.y - firstPosition.y) / (secondPosition.x - firstPosition.x);

				///*
			result.C = -firstPosition.x / (secondPosition.x - firstPosition.x);
			result.C *= (secondPosition.y - firstPosition.y);
			result.C -= -firstPosition.y / (secondPosition.y - firstPosition.y)
				*  (secondPosition.x - firstPosition.x);
			//*/
			//result.B = -1.f / result.A;

			//result.C = firstPosition.x * (firstPosition.y - secondPosition.y);
			//result.C += firstPosition.y * (firstPosition.x - secondPosition.x);


			result.A = secondPosition.y - firstPosition.y;
			result.B = firstPosition.x - secondPosition.x;

			//result.C = -firstPosition.x * secondPosition.y;
			//result.C += firstPosition.x * firstPosition.y;
			//result.C -= firstPosition.y * secondPosition.x;
			//result.C += firstPosition.y * firstPosition.x;

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
	//*/
	if (result.B != 0.f)
	{
		result.A /= abs(result.B);
		result.B /= abs(result.B);
		result.C /= abs(result.B);
	}

	//result.C = GetPointIntersection(result, SCoefficientForLineEquation(0.f, 1.f, 0.f)).y;
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

	if ((first.A == second.A) && (first.B == second.B))
	{
		return NO_POINT;
	}
	float y = -((first.C * second.A) - (second.C * first.A));//((first.C * second.A) - (second.C * first.A));

	float denumerator = ((first.B * second.A) - (first.A * second.B));//((second.B * first.A) - (first.B * second.A));
	if (denumerator == 0.f)
	{
//return NO_POINT;
		y = denumerator;
	}
	else
	{
		y /= denumerator;
		//
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
		x = denumerator;
		//
	}
	///*
	//float x2 = -(second.C + second.B * y);
	//x2 /= second.A;
	//assert(x != x2);

	//*/
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
