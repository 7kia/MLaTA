#pragma once

#include <SFML\Graphics.hpp>

#include <limits>

struct SPoint
{
	SPoint();
	SPoint(float x, float y);
	float x;
	float y;

	operator sf::Vector2f() const;
};

static const SPoint NOT_POINT = SPoint(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

bool const operator ==(SPoint const& first, SPoint const& second);
bool const operator !=(SPoint const& first, SPoint const& second);
