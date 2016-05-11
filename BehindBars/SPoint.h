#pragma once

struct SPoint
{
	SPoint();
	SPoint(float x, float y);
	float x;
	float y;

};

static const SPoint NO_POINT = SPoint(-INFINITY, -INFINITY);

bool const operator ==(SPoint const& first, SPoint const& second);
bool const operator !=(SPoint const& first, SPoint const& second);
