#include "stdafx.h"
#include "LineSegment.h"


CLineSegment::CLineSegment()
	: CShape("Line", DEFAULT_COLOR)
{
}


CLineSegment::CLineSegment(sf::Vector2f firstPoint
							, sf::Vector2f secondPoint
							, sf::Color color)
	: CShape("Line", color)
	, m_firstPoint(firstPoint)
	, m_secondPoint(secondPoint)
{
}

CLineSegment::~CLineSegment()
{
}

float CLineSegment::GetPerimeter() const
{
	
	return sqrtf(std::powf((m_firstPoint.x - m_secondPoint.x), 2.f)
					+
				std::powf((m_firstPoint.y - m_secondPoint.y), 2.f));
}

float CLineSegment::GetArea() const
{
	return 0.0f;
}

void CLineSegment::SetPositionFirstPoint(sf::Vector2f position)
{
	m_firstPoint = position;
}

void CLineSegment::SetPositionFirstPoint(float x, float y)
{
	m_firstPoint = sf::Vector2f(x, y);
}

sf::Vector2f CLineSegment::GetPositiionFirstPoint() const
{
	return m_firstPoint;
}

void CLineSegment::SetPositionSecondPoint(sf::Vector2f position)
{
	m_secondPoint = position;
}

void CLineSegment::SetPositionSecondPoint(float x, float y)
{
	m_secondPoint = sf::Vector2f(x, y);
}

sf::Vector2f CLineSegment::GetPositiionSecondPoint() const
{
	return m_secondPoint;
}

void CLineSegment::AppendProperties(std::ostream & strm) const
{
	strm << "\tPosition first point = (" << m_firstPoint.x << ", "
										<< m_firstPoint.y << ")" << std::endl
		<< "\tPosition second point = (" << m_secondPoint.x << ", " 
										<< m_secondPoint.y << ")" << std::endl;
}

void CLineSegment::Accept(IVisitor & visitor)
{
	visitor.Convert(*this);
}