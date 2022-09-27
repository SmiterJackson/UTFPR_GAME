#include "animatedObstacle.h"

Obstacles::AnimatedObstacle::AnimatedObstacle():
	Entity(), Animated()
{};
Obstacles::AnimatedObstacle::AnimatedObstacle(const unsigned int _type, float* elapsed_timeRef, const sf::RectangleShape& _hitBox,
	const AnimationSheet _animations, const std::string textureRef, const sf::IntRect sheetCut):
	Entity(Type::OBSTACLE, elapsed_timeRef, _hitBox, textureRef, sheetCut), Animated(_animations, &this->texture, &this->body)
{};
Obstacles::AnimatedObstacle::~AnimatedObstacle()
{};

void Obstacles::AnimatedObstacle::Execute()
{};
void Obstacles::AnimatedObstacle::SelfPrint(sf::RenderWindow& context_window)
{
	this->UpdateAnimation(this->elapsedTime);
	context_window.draw(this->body);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
	context_window.draw(this->hitBox);
#endif
};
void Obstacles::AnimatedObstacle::Collided(Ente* _other)
{};