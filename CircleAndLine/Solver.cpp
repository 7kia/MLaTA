#include "stdafx.h"
#include "Solver.h"

using namespace boost::numeric::ublas;
using namespace std;

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

SDataForSolver CSolver::ExtractData(std::ifstream & file)
{
	string inputString;
	getline(file, inputString);

	return ExtractData(inputString);
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


float GetDiscriminant(float A, float B, float C)
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

	if (!CheckIntersection(firstPoint, data.firstPoint, data.secondPoint)
		|| !CheckIntersection(secomdPoint, data.firstPoint, data.secondPoint))
	{
		return  std::pair<SPoint, SPoint>(NOT_POINT, NOT_POINT);
	}

	return std::pair<SPoint, SPoint>(firstPoint, secomdPoint);// TOOD : event when points no
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


float CSolver::GetCircleArcLength(const std::pair<SPoint, SPoint>& pair, float radius)
{
	return GetCircleArcLength(pair.first, pair.second, radius);
}


// ��������� ���������
float Dot(const SPoint & firstPosition, const SPoint & secondPosition)
{
	return (firstPosition.x * secondPosition.x) + (firstPosition.y * secondPosition.y);
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


matrix<float> CSolver::GetRotationMatrix(float angle, bool considered�ounterclockwise)
{
	float coefficient = 1.f;

	if (considered�ounterclockwise)
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

	// �������������
	bool considered�ounterclockwise = point.x < 0.f;

	matrix<float> vector(1, 2);
	vector.at_element(0, 0) = pointIntersection.x;
	vector.at_element(0, 1) = pointIntersection.y;

	matrix<float> rotationMatrix = GetRotationMatrix(angleBetweenRAndCathtus, considered�ounterclockwise);
	vector = prod(vector, rotationMatrix);// prod - multiply

	return SPoint(vector.at_element(0, 0), vector.at_element(0, 1));
}


SPoint CSolver::GetNearPoint(const SPoint & point, const std::pair<SPoint, SPoint> &pointsIntersection)
{
	float firstDistance = GetLineLength(point, pointsIntersection.first);
	float secondDistance = GetLineLength(point, pointsIntersection.second);

	SPoint result;

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

	std::pair<SPoint, SPoint> pointsIntersection = GetPointsIntersection(data);

	SPoint nearAboutFirst = GetNearPoint(data.firstPoint, pointsIntersection);
	SPoint nearAboutSecond = GetNearPoint(data.secondPoint, pointsIntersection);

	SPoint firstPointTangent = GetPointTangent(data.firstPoint, nearAboutFirst, data.radiusCircle);
	SPoint secondPointTangent = GetPointTangent(data.secondPoint, nearAboutSecond, data.radiusCircle);

	float result = 0.f;

	if ((pointsIntersection.first != NOT_POINT) && (pointsIntersection.second != NOT_POINT))
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
