#pragma once

#include "../Entity/entity.h"
#include "../../Traits/Animated/animated.h"

class StaticObstacle : public Entity, public Animated
{
public:
	StaticObstacle();
	StaticObstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::vector<std::pair<int, Animation>> _animations, 
		const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
	StaticObstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::list<std::pair<int, Animation>> _animations,
		const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
	~StaticObstacle();
	
	void Execute();
	void SelfPrint(sf::RenderWindow& context_window);
	void Collided(const Entity* _other);

private:
	
};