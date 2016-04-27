#include "stdafx.h"
#include "SPoint.h"


SRange::SRange()
	: start(0.f)
	, end(0.f)
{
}

SRange::SRange(float start, float end)
	: start(start)
	, end(end)
{
}


bool const operator ==(SRange const & first, SRange const & second)
{
	return ((first.start == second.start) && (first.end == second.end));
}


bool const operator!=(SRange const & first, SRange const & second)
{
	return !(first == second);
}