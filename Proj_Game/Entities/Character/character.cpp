#include "character.h"

Characters::Character::Character():
	Entity(), Animated(AnimationSheet(), &this->texture, &this->body),
	invencible(false), invcFrames(0.f), speedH(0.f), speedV(0.f), life_counter(0)
{};
Characters::Character::Character(const unsigned int _type, float* pElapsedTime, const sf::RectangleShape& _hitBox, const std::string textureRef,
								 const sf::IntRect sheetCut, const AnimationSheet _animations, const unsigned int _lifeAmount, float invcFramDuration):
	Entity(_type, pElapsedTime, _hitBox, textureRef, sheetCut), Animated(_animations, &this->texture, &this->body),
	invencible(false), invcFrames(invcFramDuration), speedH(0.f), speedV(0.f), life_counter(_lifeAmount)
{};
Characters::Character::~Character()
{};