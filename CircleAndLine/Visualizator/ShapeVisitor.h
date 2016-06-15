#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#define _USE_MATH_DEFINES 
#include "Shapes\IShape.h"
#include "Shapes\LineSegment.h"


typedef std::vector<std::shared_ptr<sf::Shape>> ListRenderShapes;

class CShapeConverter : public IVisitor
{
public:
	const float					THIKNESS_LINE = 3;
	const sf::Vector2f			ORIGIN_LINE = { THIKNESS_LINE / 2.f, 0.f };
	const float					RADIUS_POINT = 2.f;
	const sf::Color				DEFAULT_COLOR = sf::Color(255, 255, 25, 255);
public:
	void						Convert(const CLineSegment & data) override;

	std::shared_ptr<sf::Shape>	GetConvertShape();
private:
	std::shared_ptr<sf::Shape>	m_convertShape;
};