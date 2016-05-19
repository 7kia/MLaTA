#pragma once

#include "../../SPoint.h"

class CLineSegment;

class IVisitor
{
public:
	virtual void	Convert(const CLineSegment & data) = 0;
	virtual			~IVisitor() = default;
};
