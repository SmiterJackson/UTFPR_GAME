#include "animatedObstacle.h"

Obstacles::AnimObstacle::AnimObstacle():
	Obstacle(), Animated()
{};
Obstacles::AnimObstacle::AnimObstacle(const sf::RectangleShape& _hitBox, const std::string textureRef,
									  const AnimationSheet _animations, const float size_proportion,
									  const bool repeated):
	Obstacle(_hitBox, textureRef, sf::IntRect(), size_proportion, repeated),
	Animated(_animations, &this->texture, &this->body)
{};
Obstacles::AnimObstacle::~AnimObstacle()
{};

void Obstacles::AnimObstacle::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	this->UpdateAnimation(pElapsedTime);
	context_window.draw(this->body);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
	context_window.draw(this->hitBox);
#endif
};