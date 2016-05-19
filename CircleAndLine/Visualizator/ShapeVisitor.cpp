#include "stdafx.h"
#include "ShapeVisitor.h"

void CShapeConverter::Convert(const CLineSegment & data)
{
	std::shared_ptr<sf::RectangleShape> line(new sf::RectangleShape);

	line->setFillColor(data.GetFillColor());
	line->setSize(sf::Vector2f(THIKNESS_LINE, data.GetPerimeter()));
	line->setOrigin(ORIGIN_LINE);
	line->setPosition(data.GetPositiionFirstPoint());

	sf::Vector2f coordinateSecondPointInZeroSystemCoordinates = data.GetPositiionSecondPoint();//
	coordinateSecondPointInZeroSystemCoordinates -= data.GetPositiionFirstPoint();

	float angle = (atan2(coordinateSecondPointInZeroSystemCoordinates.x,
						coordinateSecondPointInZeroSystemCoordinates.y)) 
					* 180.f 
					/ static_cast<float>(M_PI) ;// TODO
	if (angle < 0) {
		angle *= -1.f;
	}

	line->setRotation(angle);

	m_convertShape = std::move(line);
}


std::shared_ptr<sf::Shape> CShapeConverter::GetConvertShape()
{
	return m_convertShape;
}
