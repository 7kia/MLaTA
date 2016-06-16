#include "stdafx.h"
#include "TaskCGW.h"

using namespace std;
using namespace sf;

TaskCGW::TaskCGW()
{
}

TaskCGW::~TaskCGW()
{
}

ListShape TaskCGW::GetRenderShape(const string & namedataFile)
{
	ListShape result;

	DataForDraw dataForDraw = ExtractDataForDraw(namedataFile);
	AddCircle(result, dataForDraw);


	if (dataForDraw.tangentPointFromFirst != NOT_POINT)
	{
		AddTangentLines(result, dataForDraw);
		AddArc(result, dataForDraw);
	}
	else
	{
		AddLine(result, dataForDraw);
	}
	//result.push_back(CreateRenderLine(dataForDraw.firstPoint, dataForDraw.tangentPointFromFirst));

	return result;
}

TaskCGW::DataForDraw TaskCGW::ExtractDataForDraw(const std::string & namedataFile)
{
	SetInputFile(namedataFile);

	SDataForSolver dataForSolver = ExtractData(m_inputFile);

	return ExtractDataForDraw(dataForSolver);// TODO might incorrect optimization
}

TaskCGW::DataForDraw TaskCGW::ExtractDataForDraw(const SDataForSolver & dataForSolver)
{
	DataForDraw result;

	result.firstPoint = dataForSolver.firstPoint;
	result.secondPoint = dataForSolver.secondPoint;
	result.radius = dataForSolver.radiusCircle;

	auto pointsIntersection = GetPointsIntersection(dataForSolver);

	if (pointsIntersection != std::pair<SPoint, SPoint>(NOT_POINT, NOT_POINT))
	{
		result.tangentPointFromFirst = GetPointTangent(result.firstPoint
			, pointsIntersection.first
			, result.radius);

		result.tangentPointFromSecond = GetPointTangent(result.secondPoint
			, pointsIntersection.second
			, result.radius);
	}
	else
	{
		result.tangentPointFromFirst = NOT_POINT;
		result.tangentPointFromSecond = NOT_POINT;
	}

	return result;
}

void TaskCGW::AddTangentLines(ListShape & list, const DataForDraw & dataForDraw)
{
	CShapeConverter shapeConverter;

	CLineSegment firstLine(Vector2f(dataForDraw.firstPoint) * SCALING_FACTOR
							, Vector2f(dataForDraw.tangentPointFromFirst)  * SCALING_FACTOR
							, INTERSECTION_COLOR);

	shapeConverter.Convert(firstLine);
	list.push_back(shapeConverter.GetConvertShape());


	CLineSegment secondSine(Vector2f(dataForDraw.secondPoint) * SCALING_FACTOR
							, Vector2f(dataForDraw.tangentPointFromSecond) * SCALING_FACTOR
							, INTERSECTION_COLOR);

	shapeConverter.Convert(secondSine);
	list.push_back(shapeConverter.GetConvertShape());
}

void TaskCGW::AddArc(ListShape & list, const DataForDraw & dataForDraw)
{
	SPoint startPoint = dataForDraw.tangentPointFromFirst;
	SPoint endPoint = dataForDraw.tangentPointFromSecond;

	CShapeConverter shapeConverter;

	float step = (startPoint.x - endPoint.x) / AMOUNT_POINT_IN_ARC;
	sf::Vector2f startLine = startPoint;
	for (size_t index = 1; index <= AMOUNT_POINT_IN_ARC; index++)
	{
		float currentX = startPoint.x - (step * index);
		float currentY =  (dataForDraw.radius * dataForDraw.radius) - (currentX * currentX);
		currentY = sqrt(currentY);
		bool isSign = (endPoint.y < 0);

		if (isSign)
		{
			currentY *= -1.f;
		}

		sf::Vector2f endLine = Vector2f(currentX, currentY);

		CLineSegment partArc(startLine  * SCALING_FACTOR//
							, endLine * SCALING_FACTOR
							, INTERSECTION_COLOR);

		shapeConverter.Convert(partArc);
		list.push_back(shapeConverter.GetConvertShape());

		startLine = endLine;
	}
}

void TaskCGW::AddCircle(ListShape & list, const DataForDraw & dataForDraw)
{
	shared_ptr<CircleShape> circle = make_shared<CircleShape>();

	circle->setRadius(dataForDraw.radius  * SCALING_FACTOR);
	circle->setOutlineThickness(THIKNESS_LINE);

	circle->setFillColor(sf::Color::Black);
	circle->setOutlineColor(NOT_INTERSECTION_COLOR);

	circle->setPosition(sf::Vector2f());
	circle->setOrigin(Vector2f(circle->getRadius() , circle->getRadius() ));

	list.push_back(circle);
}

void TaskCGW::AddLine(ListShape & list, const DataForDraw & dataForDraw)
{
	CShapeConverter shapeConverter;

	CLineSegment firstLine(Vector2f(dataForDraw.firstPoint) * SCALING_FACTOR
							, Vector2f(dataForDraw.secondPoint)  * SCALING_FACTOR
							, INTERSECTION_COLOR);

	shapeConverter.Convert(firstLine);
	list.push_back(shapeConverter.GetConvertShape());
}