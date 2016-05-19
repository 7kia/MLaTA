#pragma once

#include "SFML\Graphics.hpp"
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

#include "IAccepter.h"


static const float pi = boost::math::constants::pi<float>();
static const std::string MESSAGE_INCORRECT_VALUE = "Incorrect value!!!";
struct SColor
{
	SColor(uint8_t r, uint8_t g, uint8_t b);
	SColor(const std::string &value);
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;

	bool operator==(const SColor & other) const;
	operator sf::Color() const;
};
std::ostream& operator<<(std::ostream& stream, SColor const& color);

static const SColor DEFAULT_COLOR(0, 0, 0);
static const int AMOUNT_NUMBERS_FOR_OUTPUT = 3;

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f & vector);




class IShape
	: public IAccepter
{
public:
	virtual ~IShape();

	virtual float				GetPerimeter() const = 0;
	virtual float				GetArea() const = 0;
protected:
	virtual void				AppendProperties(std::ostream & strm) const = 0;
};

