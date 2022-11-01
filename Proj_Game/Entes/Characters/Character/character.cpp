#include "character.h"

Characters::Character::Character():
	Entity(Type::UNDEFINED, PrintPriority::characters, 
		sf::Vector2f(), sf::Vector2f(), true, 1.f
	),
	PrintableBody(),
	Animated(AnimationSheet(), this->texture, &this->body),
	invencible(false), invcFrames(0.f), speedH(0.f), speedV(0.f), life_counter(0)
{};
Characters::Character::Character(const unsigned short int _type, const sf::Vector2f _size, const sf::Vector2f _position,
								 const std::string path, const AnimationSheet _animations, const unsigned int _lifeAmount, 
								 const float invcFramDuration, const bool isStatic, const float size_coeff):
	Entity(_type, PrintPriority::characters, _size, _position, isStatic, size_coeff),
	PrintableBody(path, sf::IntRect(), size_coeff),
	Animated(_animations, this->texture, &this->body),
	invencible(false), invcFrames(invcFramDuration), speedH(0.f), speedV(0.f), life_counter(_lifeAmount)
{};
Characters::Character::~Character()
{};

void Characters::Character::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	this->UpdateAnimation(pElapsedTime);
	context_window.draw(this->body);

#ifdef _DEBUG
	context_window.draw(this->origin);
#endif
};