#include "stdafx.h"
#include "Solver.h"

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

SCoefficientForLineEquation CSolver::GetLineEquation(const SPoint &firstPosition, const SPoint & secondPosition)
{
	SCoefficientForLineEquation result;

	result.A = (secondPosition.y - firstPosition.y) / (secondPosition.x - firstPosition.x);

	result.B = -1.f / result.A;

	result.C = -firstPosition.x / (secondPosition.x - firstPosition.x);
	result.C *= (secondPosition.y - firstPosition.y);

	result.C -= -firstPosition.y / (secondPosition.y - firstPosition.y)
									*  (secondPosition.x - firstPosition.x);

	return result;
}

float CSolver::GetDiscriminant(const float A, const float B, const float C) const
{
	return sqrt((B * B) - (4.f * A * C));
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
	if (discriminant >= 0)
	{
		float denumerator = 2.f * A;

		firstRoot = -(B * B) + discriminant;
		firstRoot /= denumerator;

		secondRoot = -(B * B) - discriminant;
		secondRoot /= denumerator;
	}

	SPoint firstPoint;
	firstPoint.x = firstRoot;
	firstPoint.y = -(lineEquation.A * firstRoot + lineEquation.C) / lineEquation.B;

	SPoint secomdPoint;
	secomdPoint.x = secondRoot;
	secomdPoint.y = -(lineEquation.A * secondRoot + lineEquation.C) / lineEquation.B;

	return std::pair<SPoint, SPoint>(firstPoint, secomdPoint);
}

float CSolver::GetLengthLineConectTwoPoints(const std::string & inputString)
{
	SDataForSolver data = ExtractData(inputString);

	std::pair<SPoint, SPoint> pointsIntersection = GetPointsIntersection(data);


	return 0.0f;
}

SPoint::SPoint()
	: x(0.f)
	, y(0.f)
{
}

SPoint::SPoint(float x, float y)
	: x(x)
	, y(y)
{
}
