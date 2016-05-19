#pragma once

#include <SFML\Graphics.hpp>
#include "TaskCGW.h"

static const int AMOUNT_ARGUMENTS = 3;
static const std::string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";

static const sf::Color CLEAR_DEFAULT_COLOR = sf::Color(0, 0, 120);

void CheckParametrs(int argc);

class CApplication
{
public:
	CApplication();

	void				Run();

private:
	const int WIDTH_WINDOW = 600;
	const int HEIGHT_WINDOW = 600;

	const std::string TITLE_WINDOW = "CGW for lab \"Circle and line\"";

private:
	void							AcceptShape(const ListShape & list);

	void							Render();
	void							ProcessEvents();

	void							ProcessGUI(sf::Event& event);// TODO delete if not need
private:
	sf::RenderWindow				m_window;

	ListShape						m_renderShape;
};