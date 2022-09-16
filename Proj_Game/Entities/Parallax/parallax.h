#pragma once

#include "../Player/player.h"

typedef std::pair<sf::Texture, sf::Sprite> Background;

class ParallaxBackground : public Ente
{
public:
	ParallaxBackground();
	ParallaxBackground(sf::View* _view, float* elapsed_timeRef, const std::vector<std::string>& paths = std::vector<std::string>(), const float size_coefficient = 1.f);
	~ParallaxBackground();

	void Execute();
	void SelfPrint(sf::RenderWindow& context_window);

	void SetBackgrounds(const std::vector<std::string>& paths);
	unsigned int GetBackgroundListSize();

	float GetSizeCoefficient() { return this->size_coeff; };
	void SetSizeCoefficient(float _size_coeff) 
	{ 
		std::vector<Background>::iterator it;
		this->size_coeff = _size_coeff; 

		if (this->backGrounds.size() > 0)
		{
			for (it = this->backGrounds.begin(); it != this->backGrounds.end(); it++)
			{
				it->second.setScale(_size_coeff, _size_coeff);
			}
		}
	};
	
private:
	std::vector<Background> backGrounds;
	sf::View* visionReference;
	sf::Vector2f lastPosition;

	float layers_spd_proportion;
	float size_coeff;
};