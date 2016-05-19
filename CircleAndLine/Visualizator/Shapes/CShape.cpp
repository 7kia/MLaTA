#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const std::string & type, sf::Color color)
	: m_fillColor(color)
{
}


CShape::~CShape()
{
}

void CShape::SetFillColor(const sf::Color color)
{
	m_fillColor = color;
}

void CShape::SetFillColor(const uint8_t r
						, const uint8_t g
						, const uint8_t b)
{
	m_fillColor.r = r;
	m_fillColor.g = g;
	m_fillColor.b = b;
}

sf::Color CShape::GetFillColor() const
{
	return m_fillColor;
}

SColor::SColor(uint8_t r, uint8_t g, uint8_t b)
{
	red = r;
	green = g;
	blue = b;
}

SColor::SColor(const std::string & value)
{
	if ((value[0] == '#') && (value.size() == 7))
	{
		std::istringstream valueRed(value.substr(1, 2));
		std::istringstream valueGreen(value.substr(3, 2));
		std::istringstream valueBlue(value.substr(5, 2));
		int inputValue;
		valueRed >> std::hex >> inputValue;
		red = static_cast<uint8_t>(inputValue);

		valueGreen >> std::hex >> inputValue;
		green = static_cast<uint8_t>(inputValue);

		valueBlue >> std::hex >> inputValue;
		blue = static_cast<uint8_t>(inputValue);
	}
	else
	{
		throw std::invalid_argument(MESSAGE_INCORRECT_VALUE);
	}
}

bool SColor::operator==(const SColor & other) const
{
	return (red == other.red) && (blue == other.blue) && (green == other.green);
}

SColor::operator sf::Color() const
{
	return sf::Color(red, green, blue);
}

std::ostream& operator<<(std::ostream& stream, SColor const& color)
{
	stream << "#" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.red)
		<< std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.green)
		<< std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(color.blue);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, sf::Vector2f const & vector)
{
	stream << "(" << vector.x << ", " << vector.x << ")";
	return stream;
}