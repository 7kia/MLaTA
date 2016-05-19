#include "stdafx.h"
#include "SPoint.h"


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

SPoint::operator sf::Vector2f() const
{
	return sf::Vector2f(x, y);
}


bool const operator ==(SPoint const & first, SPoint const & second)
{
	return ((first.x == second.x) && (first.y == second.y));
}


bool const operator!=(SPoint const & first, SPoint const & second)
{
	return !(first == second);
}