#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <functional>

namespace featureCheckBox {
	const sf::Vector2f SIZE_CHECKBOX = { 75.f, 25.f };
	const float THIKNESS = 3.f;

	const size_t SIZE_TEXT = 16u;

	const sf::Color BACK_COLOR_NOT_CHANGED(255, 255, 255, 255);
	const sf::Color BORDER_COLOR_NOT_CHANGED(0, 200, 0, 255);

	const sf::Color BACK_COLOR_HOVERED(255, 200, 200, 255);
	const sf::Color BORDER_COLOR_HOVERED(200, 200, 0, 255);

	const sf::Color BACK_COLOR_CHANGED(255, 255, 255, 255);
	const sf::Color BORDER_COLOR_CHANGED(200, 0, 0, 255);

	const sf::Color BACK_COLOR_HOVERED_CHANGED(255, 255, 255, 255);
	const sf::Color BORDER_COLOR_HOVERED_CHANGED(255, 100, 100, 255);


	const sf::Vector2f SIZE_CROSS = { 5.f, 20.f };
	const sf::Color CROSS_COLOR(200, 0, 0, 255);
	const float CROSS_ANGLE = 45.f;

	const float SCALE_CROSS_X = 0.2f;
	const float SCALE_CROSS_Y = 0.8f;

}

struct Button {
	enum State {
		NotChanged,
		Hovered,
		Changed,
		HoveredChanged
	};

private:
	sf::RectangleShape box;
	void BoxInitialize(sf::Vector2f const& position
						, sf::Vector2f const& sizeBox);

	sf::Font font;
	sf::Text text;

public:
	Button(sf::Vector2f const& position
		, const std::string & buttonText
		, sf::Vector2f const& sizeBox);
	bool DoesHit(sf::Vector2f const& point) const;

	void Draw(sf::RenderWindow &window);

	bool mouseButtonHits(sf::Event const& event);
	bool mouseMoveHits(sf::Event const & event);
	bool OnEvent(sf::Event const& event);
	void SetState(State newState);

	bool IsChecked() const;
	std::function<void(bool cheked)> handler;
	State state;
};