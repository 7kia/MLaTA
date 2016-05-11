#pragma once

#include <limits>

struct SPoint
{
	SPoint();
	SPoint(float x, float y);
	float x;
	float y;

};

static const SPoint NO_POINT = SPoint(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

bool const operator ==(SPoint const& first, SPoint const& second);
bool const operator !=(SPoint const& first, SPoint const& second);
