#include "stdafx.h"
#include "Application.h"

using namespace std;
using namespace sf;

CApplication::CApplication()
	: m_window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), TITLE_WINDOW, sf::Style::Close)
{
}

void CApplication::Run()
{
	TaskCGW task;
	AcceptShape(task.GetRenderShape("input2.txt"));

	while (m_window.isOpen())
	{
		ProcessEvents();

		Render();			
	}

}


void CApplication::AcceptShape(const ListShape & list)
{
	m_renderShape = list;

	for (auto & shape : m_renderShape)
	{
		shape->move(sf::Vector2f(WIDTH_WINDOW / 2.f, HEIGHT_WINDOW / 2.f ));
	}
}

void CApplication::Render()
{
	m_window.clear(CLEAR_DEFAULT_COLOR);

	for (const auto & shape : m_renderShape)
	{
		m_window.draw(*shape);
	}

	m_window.display();
}

void CApplication::ProcessEvents()
{
	Event event;
	while (m_window.pollEvent(event)) {

		ProcessGUI(event);

		switch (event.type) {
		case sf::Event::Resized:
			m_window.setSize(Vector2u(m_window.getSize()));
			break;
		case sf::Event::Closed:
			m_window.close();
			break;
		default:
			break;
		}

	}


}

void CApplication::ProcessGUI(Event& event)
{
	//if (m_slider.OnEvent(event)) {
	//	m_slider.handler(m_slider.IsChecked());
	//}
}