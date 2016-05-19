#pragma once
#include "IVisitor.h"

class IAccepter {
public:
	virtual void Accept(IVisitor & visitor) = 0;
	virtual ~IAccepter() = default;
};