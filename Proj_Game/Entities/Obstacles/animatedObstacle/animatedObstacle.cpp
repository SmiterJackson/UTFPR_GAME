#include "animatedObstacle.h"

Obstacles::AnimatedObstacle::AnimatedObstacle():
	Entity(), Animated()
{};
Obstacles::AnimatedObstacle::AnimatedObstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, 
	const std::vector<std::pair<int, Animation>> _animations, const std::string textureRef, const sf::IntRect sheetCut):
	Entity(Type::OBSTACLE, _hitBox, elapsed_timeRef, textureRef, sheetCut), Animated(_animations, &this->texture, &this->body)
{};
Obstacles::AnimatedObstacle::AnimatedObstacle(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, 
	const std::list<std::pair<int, Animation>> _animations,	const std::string textureRef, const sf::IntRect sheetCut):
	Entity(Type::OBSTACLE, _hitBox, elapsed_timeRef, textureRef, sheetCut), Animated(_animations, &this->texture, &this->body)
{};
Obstacles::AnimatedObstacle::~AnimatedObstacle()
{};

void Obstacles::AnimatedObstacle::Execute()
{};
void Obstacles::AnimatedObstacle::SelfPrint(sf::RenderWindow& context_window)
{
	if (this->next_ani != this->last_ani)
	{
		this->animations[this->last_ani].ResetAnimation();
		this->last_ani = this->next_ani;
	}

	this->body.setTextureRect(this->animations[this->next_ani].update(this->elapsed_time, this->looking_right));
	context_window.draw(this->body);

#ifdef _DEBUG
	this->hitBox.setOutlineColor(sf::Color::Red);
	this->hitBox.setOutlineThickness(1.5f);
	context_window.draw(this->hitBox);
#endif
};
void Obstacles::AnimatedObstacle::Collided(Entity* _other)
{};