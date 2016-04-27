#include "stdafx.h"
#include "Solver.h"

using namespace boost::numeric::ublas;

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
		result.firstPoint.start = stof(arguments[0]);
		result.firstPoint.end = stof(arguments[1]);

		result.secondPoint.start = stof(arguments[2]);
		result.secondPoint.end = stof(arguments[3]);

		result.radiusCircle = stof(arguments[4]);
	}
	else
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS);
	}

	return result;
}


SCoefficientForLineEquation CSolver::GetLineEquation(const SRange &firstPosition, const SRange & secondPosition)
{
	SCoefficientForLineEquation result;

	result.A = (secondPosition.end - firstPosition.end) / (secondPosition.start - firstPosition.start);

	result.B = -1.f / result.A;

	result.C = -firstPosition.start / (secondPosition.start - firstPosition.start);
	result.C *= (secondPosition.end - firstPosition.end);

	result.C -= -firstPosition.end / (secondPosition.end - firstPosition.end)
									*  (secondPosition.start - firstPosition.start);

	return result;
}


float GetDiscriminant(float A, float B, float C)
{
	return sqrt((B * B) - (4.f * A * C));
}


std::pair<SRange, SRange> CSolver::GetPointsIntersection(const SDataForSolver & data)
{
	SCoefficientForLineEquation lineEquation = GetLineEquation(data.firstPoint, data.secondPoint);

	float A = lineEquation.B * lineEquation.B + lineEquation.A * lineEquation.A;
	float B = 2.f * lineEquation.A * lineEquation.C;
	float C = lineEquation.C * lineEquation.C;
	C -= lineEquation.B * lineEquation.B * data.radiusCircle * data.radiusCircle;

	float discriminant = GetDiscriminant(A, B, C);
	float firstRoot = 0.f;
	float secondRoot = 0.f;

	SRange firstPoint;
	SRange secomdPoint;

	if (discriminant >= 0)
	{
		float denumerator = 2.f * A;

		firstRoot = -(B * B) + discriminant;
		firstRoot /= denumerator;

		secondRoot = -(B * B) - discriminant;
		secondRoot /= denumerator;

		firstPoint.start = firstRoot;
		firstPoint.end = -(lineEquation.A * firstRoot + lineEquation.C) / lineEquation.B;

		secomdPoint.start = secondRoot;
		secomdPoint.end = -(lineEquation.A * secondRoot + lineEquation.C) / lineEquation.B;
	}

	return std::pair<SRange, SRange>(firstPoint, secomdPoint);// TOOD : event when points no
}


float CSolver::GetLineLength(const SRange & firstPosition, const SRange & secondPosition)
{
	float differenceX = firstPosition.start - secondPosition.start;
	float differenceY = firstPosition.end - secondPosition.end;

	return sqrt(differenceX * differenceX + differenceY * differenceY);
}


float CSolver::GetLineLength(const std::pair<SRange, SRange>& pair)
{
	return GetLineLength(pair.first, pair.second);
}


float CSolver::GetCircleArcLength(const std::pair<SRange, SRange>& pair, float radius)
{
	return GetCircleArcLength(pair.first, pair.second, radius);
}


// Ñêàëÿðíîå óìíîæåíèå
float Dot(const SRange & firstPosition, const SRange & secondPosition)
{
	return (firstPosition.start * secondPosition.start) + (firstPosition.end * secondPosition.end);
}


float CSolver::GetCircleArcLength(const SRange & firstPosition, const SRange & secondPosition, float radius)
{
	float lenthFirst = radius;
	float lenthSecond = radius;

	float cosinus = Dot(firstPosition, secondPosition) / (lenthFirst * lenthSecond);

	return abs(acosf(cosinus)) * radius;
}


float  CSolver::GetDistanseBetweenPointAndTangent(const SRange & point, const float radius)
{
	float distanseBetweenPointAndCenter = GetLineLength(SRange(), point);

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


SRange CSolver::GetPointTangent(const SRange & point, const SRange & pointIntersection, const float radius)
{
	float hypotenuse = GetLineLength(SRange(), point);
	// R -radiuse circle
	float angleBetweenRAndCathtus = GetAngleBetweenCathetusAndHypotenuse(radius, hypotenuse);

	// ïðîòèâ÷àñîâîé
	bool consideredÑounterclockwise = point.start < 0.f;

	matrix<float> vector(1, 2);
	vector.at_element(0, 0) = pointIntersection.start;
	vector.at_element(0, 1) = pointIntersection.end;

	matrix<float> rotationMatrix = GetRotationMatrix(angleBetweenRAndCathtus, consideredÑounterclockwise);
	vector = prod(vector, rotationMatrix);// prod - multiply

	return SRange(vector.at_element(0, 0), vector.at_element(0, 1));
}


SRange CSolver::GetNearPoint(const SRange & point, const std::pair<SRange, SRange> &pointsIntersection)
{
	float firstDistance = GetLineLength(point, pointsIntersection.first);
	float secondDistance = GetLineLength(point, pointsIntersection.second);

	SRange result;

	if (firstDistance > secondDistance)
	{
		result = pointsIntersection.second;
	}
	else
	{
		result = pointsIntersection.first;
	}

	return result;
}


float CSolver::GetDistanseLineConectTwoPoints(const std::string & inputString)
{
	SDataForSolver data = ExtractData(inputString);

	std::pair<SRange, SRange> pointsIntersection = GetPointsIntersection(data);

	SRange nearAboutFirst = GetNearPoint(data.firstPoint, pointsIntersection);
	SRange nearAboutSecond = GetNearPoint(data.secondPoint, pointsIntersection);

	SRange firstPointTangent = GetPointTangent(data.firstPoint, nearAboutFirst, data.radiusCircle);
	SRange secondPointTangent = GetPointTangent(data.secondPoint, nearAboutSecond, data.radiusCircle);

	float result = 0.f;

	if ((pointsIntersection.first != SRange()) && (pointsIntersection.second != SRange()))
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
