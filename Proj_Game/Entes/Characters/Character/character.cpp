#include "character.h"

Characters::Character::Character():
	Entity(Type::UNDEFINED), 
	Printable(PrintPriority::CHARACTER), 
	Animated(AnimationSheet(), &this->texture, &this->body),
	invencible(false), invcFrames(0.f), speedH(0.f), speedV(0.f), life_counter(0)
{};
Characters::Character::Character(const unsigned int _type, const sf::RectangleShape& _hitBox, const std::string textureRef,
								 const sf::IntRect sheetCut, const AnimationSheet _animations, const unsigned int _lifeAmount, 
								 const float invcFramDuration, const float size_proportion):
	Entity(_type, _hitBox, size_proportion, false), 
	Printable(PrintPriority::CHARACTER, textureRef, sheetCut, size_proportion),
	Animated(_animations, &this->texture, &this->body), 
	invencible(false), invcFrames(invcFramDuration), speedH(0.f), speedV(0.f), life_counter(_lifeAmount)
{};
Characters::Character::~Character()
{};