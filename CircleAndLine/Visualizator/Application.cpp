#include "stdafx.h"
#include "tinyfiledialogs.h"
#include "Application.h"

using namespace std;
using namespace sf;

CApplication::CApplication()
	: m_window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), TITLE_WINDOW, sf::Style::Close)
	, m_button(featureCheckBox::SIZE_CHECKBOX / 2.f, "Open", featureCheckBox::SIZE_CHECKBOX)
{
	m_button.handler = [&](bool cheked) {
		if (cheked) {
			TaskCGW task;

			AcceptShape(task.GetRenderShape(AskOpenInput()));
		}
		else {
			
		}
	};

}

void CApplication::Run()
{
	TaskCGW task;

	AcceptShape(task.GetRenderShape(AskOpenInput()));

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

const char* CApplication::AskOpenInput()
{
	const char *filters[] = { "*.txt" };
	char const *result = tinyfd_openFileDialog("Select input file", "", 1, filters, "", false);
	// Пользователь отменил выбор файла.
	if (result == nullptr)
	{
		return "";
	}

	return result;
}

void CApplication::Render()
{
	m_window.clear(CLEAR_DEFAULT_COLOR);

	for (const auto & shape : m_renderShape)
	{
		m_window.draw(*shape);
	}

	m_button.Draw(m_window);
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
	if (m_button.OnEvent(event)) {
		m_button.handler(m_button.IsChecked());
	}
}