#include "animatedObstacle.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Obstacles;
using namespace Manager;

AnimObstacle::AnimObstacle():
	Obstacle(), 
	Animated()
{};
AnimObstacle::AnimObstacle(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
									  const AnimationSheet _animations, const float size_coeff, const bool isStatic, const bool repeated):
	Obstacle(_size, _position, path, sf::IntRect(), size_coeff, isStatic, repeated),
	Animated(_animations, this->texture, &this->body)
{};
AnimObstacle::~AnimObstacle()
{};

void AnimObstacle::SelfPrint(const float& pElapsedTime)
{
	this->UpdateAnimation(pElapsedTime);
	GraphicManager::Draw(this->body);
	//context_window.draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->origin);
	//context_window.draw(this->hitBox);
	//context_window.draw(this->origin);
#endif
};