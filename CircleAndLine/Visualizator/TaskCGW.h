#pragma once

#include <SFML\Graphics.hpp>
#include "../SPoint.h"
#include "../FileManager.h"
#include "../Solver.h"

#include "ShapeVisitor.h"

typedef std::vector<std::shared_ptr<sf::Shape>> ListShape;

class TaskCGW
	: public CFileManager
	, public CSolver
{
public:
	TaskCGW();
	TaskCGW(const std::string & namedataFile);
	~TaskCGW();
	
	ListShape		GetRenderShape(const std::string & namedataFile);// TODO : rename
public:
	struct DataForDraw
	{
		SPoint firstPoint;
		SPoint secondPoint;
		SPoint tangentPointFromFirst;
		SPoint tangentPointFromSecond;
		float radius;
	};
private:
	const float					THIKNESS_LINE = 5;
	const sf::Vector2f			ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float					RADIUS_POINT = 2.f;

	const sf::Color				INTERSECTION_COLOR = sf::Color(0, 255, 0, 255);
	const sf::Color				NOT_INTERSECTION_COLOR = sf::Color(255, 0, 0, 255);
	const int					AMOUNT_POINT_IN_ARC = 20;
	const float					SCALING_FACTOR = 50.f;
private:
	DataForDraw				ExtractDataForDraw(const std::string & namedataFile);
	DataForDraw				ExtractDataForDraw(const SDataForSolver & dataForSolver);
	void					AddTangentLines(ListShape & list, const DataForDraw & dataForDraw);
	void					AddArc(ListShape & list, const DataForDraw & dataForDraw);
	void					AddCircle(ListShape & list, const DataForDraw & dataForDraw);
protected:
};