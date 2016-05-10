#pragma once

struct SPoint
{
	SPoint();
	SPoint(float x, float y);
	float x;
	float y;

};
bool const operator ==(SPoint const& first, SPoint const& second);
bool const operator !=(SPoint const& first, SPoint const& second);
