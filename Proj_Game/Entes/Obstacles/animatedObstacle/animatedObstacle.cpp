#include "animatedObstacle.h"

Obstacles::AnimObstacle::AnimObstacle():
	Obstacle(), 
	Animated()
{};
Obstacles::AnimObstacle::AnimObstacle(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
									  const AnimationSheet _animations, const float size_coeff, const bool isStatic, const bool repeated):
	Obstacle(_size, _position, path, sf::IntRect(), size_coeff, isStatic, repeated),
	Animated(_animations, this->texture, &this->body)
{};
Obstacles::AnimObstacle::~AnimObstacle()
{};

void Obstacles::AnimObstacle::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	this->UpdateAnimation(pElapsedTime);
	context_window.draw(this->body);

#ifdef _DEBUG
	context_window.draw(this->origin);
#endif
};