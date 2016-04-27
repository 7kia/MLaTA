#pragma once

struct SRange
{
	SRange();
	SRange(float start, float end);
	float start;
	float end;

};
bool const operator ==(SRange const& first, SRange const& second);
bool const operator !=(SRange const& first, SRange const& second);
