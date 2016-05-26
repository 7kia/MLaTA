#include "stdafx.h"
#include "Button.h"

using namespace sf;
using namespace featureCheckBox;

Button::Button(Vector2f const& position
				, const std::string & buttonText
				, sf::Vector2f const& sizeBox)
{
	font.loadFromFile("sansation.ttf");

	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setString(buttonText);
	text.setCharacterSize(SIZE_TEXT);
	text.setPosition(sizeBox.x / 2.f, sizeBox.y / 2.f);

	BoxInitialize(position, sizeBox);
}

void Button::BoxInitialize(sf::Vector2f const& position, sf::Vector2f const& sizeBox)
{
	box.setSize(sizeBox);
	box.setFillColor(BACK_COLOR_NOT_CHANGED);

	box.setOutlineThickness(THIKNESS);
	box.setOutlineColor(BORDER_COLOR_NOT_CHANGED);
	box.setPosition(position);
}

bool Button::DoesHit(sf::Vector2f const& point) const
{
	return box.getGlobalBounds().contains(point);
}

void Button::Draw(RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}

bool Button::mouseButtonHits(Event const& event)
{
	Vector2f mousePoint(float(event.mouseButton.x), float(event.mouseButton.y));
	return (event.mouseButton.button == sf::Mouse::Left) && DoesHit(mousePoint);
}

bool Button::mouseMoveHits(Event const& event)
{
	Vector2f mousePoint(float(event.mouseMove.x), float(event.mouseMove.y));
	return DoesHit(mousePoint);
}

bool Button::OnEvent(const Event& event)
{
	switch (event.type) {
		/*
		case Event::MouseMoved:
		if (state != Changed && state != HoveredChanged) {
			SetState(mouseMoveHits(event) ? Hovered : NotChanged);
		}
		else {
			SetState(mouseMoveHits(event) ? HoveredChanged : Changed);
		}
		break;
		*/
	
	case Event::MouseButtonReleased:
		if (mouseButtonHits(event)) {
			handler(true);
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

void Button::SetState(State newState)
{
	state = newState;
	switch (newState) {
	case NotChanged:
		box.setFillColor(BACK_COLOR_NOT_CHANGED);
		box.setOutlineColor(BORDER_COLOR_NOT_CHANGED);
		handler(IsChecked());
		break;
	case Hovered:
		box.setFillColor(BACK_COLOR_HOVERED);
		box.setOutlineColor(BORDER_COLOR_HOVERED);
		break;
	case Changed:
		box.setFillColor(BACK_COLOR_CHANGED);
		box.setOutlineColor(BORDER_COLOR_CHANGED);
		handler(IsChecked());
		break;
	case HoveredChanged:
		box.setFillColor(BACK_COLOR_HOVERED_CHANGED);
		box.setOutlineColor(BORDER_COLOR_HOVERED_CHANGED);
		break;
	}
}

bool Button::IsChecked() const
{
	if (state == Changed || state == HoveredChanged)
	{
		return true;
	}
	return false;
}