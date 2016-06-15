#pragma once

#include <SFML\Graphics.hpp>



struct SPoint
{
	SPoint();
	SPoint(float x, float y);
	float x;
	float y;

	operator sf::Vector2f() const;
};
bool const operator ==(SPoint const& first, SPoint const& second);
bool const operator !=(SPoint const& first, SPoint const& second);
