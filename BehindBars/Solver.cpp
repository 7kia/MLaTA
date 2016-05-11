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

	if ((IsEqual(firstLineEquation.A, secondLineEquation.A))
		&&
		(IsEqual(firstLineEquation.B, secondLineEquation.B)))
	{
		//
		if (IsEqual(firstLineEquation.C, secondLineEquation.C))
		{
			return 0.f;
		}
		// if is parallel

		// first point is point start first line
		// second point is point end first line
		SPoint nearPointToFirst = GetNearPoint(data.startFirstLine, data.startSecondLine, data.endSecondLine);
		SPoint nearPointToSecond = GetNearPoint(data.endFirstLine, data.startSecondLine, data.endSecondLine);

		float distanseFromFirst = GetLineLength(data.startFirstLine, nearPointToFirst);
		float distanseFromSecond = GetLineLength(data.endFirstLine, nearPointToSecond);

		return std::min(distanseFromFirst, distanseFromSecond);
	}
	else
	{

	}
	return 0.0f;
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
