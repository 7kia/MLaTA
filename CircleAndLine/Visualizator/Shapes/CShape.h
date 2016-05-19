#pragma once

#include <boost/math/constants/constants.hpp>

#include "IShape.h"

class CShape :
	public IShape
{
public:
	CShape(const std::string & type, sf::Color color);
	~CShape();

	void						SetFillColor(const sf::Color color);
	void						SetFillColor(const uint8_t r
											, const uint8_t g
											, const uint8_t b);
	sf::Color					GetFillColor() const;
protected:
	sf::Color					m_fillColor;
};