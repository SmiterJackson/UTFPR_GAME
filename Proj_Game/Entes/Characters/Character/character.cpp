#include "character.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Characters;
using namespace Manager;

#define DAMAGE_FLICK_TIMER 1.f

Character::Character():
	Entity(
		Type::UNDEFINED, PrintPriority::characters, sf::Vector2f(0.f, 0.f),
		sf::Vector2f(0.f, 0.f), std::string(""), sf::IntRect(0,0,0,0)
	),
	Animated(this->body),
	invcFrames(0.3f), speedH(0.f), speedV(0.f), speedCoeff(1.f),
	invecTimer(0.f), deathTimer(1.f), damagedTimer(DAMAGE_FLICK_TIMER), life_counter(5U)
{};
Character::Character(const unsigned short int _type, const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
					 const AnimationSheet _animations, const unsigned int _lifeAmount, const float invcDuration,
					 const float deathTime, const bool isStatic, const float proportion):
	Entity(
		_type, PrintPriority::characters, _size, _position, 
		path, sf::IntRect(0,0,0,0),	isStatic, proportion
	),
	Animated(this->body, _animations),
	invcFrames(invcDuration), speedH(0.f), speedV(0.f), speedCoeff(1.f),
	invecTimer(0.f), deathTimer(deathTime), damagedTimer(DAMAGE_FLICK_TIMER), life_counter(_lifeAmount)
{};
Character::~Character()
{};