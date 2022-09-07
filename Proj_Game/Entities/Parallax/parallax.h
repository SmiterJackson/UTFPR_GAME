#pragma once

#include "../Player/player.h"

class ParallaxBackground : public Ente
{
public:
	ParallaxBackground(sf::View* _view = nullptr, const std::vector<std::string>& paths = std::vector<std::string>(), const float size_coefficient = 1.f);
	~ParallaxBackground();

	void Execute(const float elapsedTime);
	void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime);

	typedef std::pair<sf::Texture, sf::RectangleShape> Background;

private:
	std::list<Background> backGrounds;
	sf::View* visionReference;
	sf::Vector2f lastPosition;

	float layers_spd_proportion;
	float size_coeff;
};