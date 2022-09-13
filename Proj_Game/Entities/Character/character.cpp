#include "character.h"

Characters::Character::Character():
	Entity(), Animated(
	), invencible(false), invcFrames(0.f), speedH(0.f), speedV(0.f), life_counter(0)
{};
Characters::Character::Character(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef,
	const std::vector<std::pair<int, Animation>> _animations, const sf::IntRect sheetCut, const unsigned int _lifeAmount, float invcFramDuration):
	Entity(_type, _hitBox, elapsed_timeRef, textureRef, sheetCut), Animated(_animations, &this->texture, &this->body),
	invencible(false), invcFrames(invcFramDuration), speedH(0.f), speedV(0.f), life_counter(_lifeAmount)
{};
Characters::Character::Character(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef,
	const std::list<std::pair<int, Animation>> _animations, const sf::IntRect sheetCut, const unsigned int _lifeAmount, float invcFramDuration):
	Entity(_type, _hitBox, elapsed_timeRef, textureRef, sheetCut), Animated(_animations, &this->texture, &this->body),
	invencible(false), invcFrames(invcFramDuration), speedH(0.f), speedV(0.f), life_counter(_lifeAmount)
{};
Characters::Character::~Character()
{};