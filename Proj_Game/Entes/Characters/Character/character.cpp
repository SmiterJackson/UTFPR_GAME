#include "character.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Characters;
using namespace Manager;

Character::Character():
	Entity(Type::UNDEFINED, PrintPriority::characters, 
		sf::Vector2f(), sf::Vector2f(), true, 1.f
	),
	Animated(),
	invcFrames(0.f), invecTimer(0.f),
	speedH(0.f), speedV(0.f), speedCoeff(1.f), life_counter(0)
{};
Character::Character(const unsigned short int _type, const sf::Vector2f _size, const sf::Vector2f _position,
					 const std::string path, const AnimationSheet _animations, const unsigned int _lifeAmount, 
					 const float invcFramDuration, const bool isStatic, const float size_coeff):
	Entity(_type, PrintPriority::characters, _size, _position, isStatic, size_coeff),
	Animated(path, _animations, size_coeff),
	invcFrames(invcFramDuration), invecTimer(0.f),
	speedH(0.f), speedV(0.f), speedCoeff(1.f), life_counter(_lifeAmount)
{};
Character::~Character()
{};

//void SelfPrint(const float& pElapsedTime)
//{
//	this->UpdateAnimation(pElapsedTime);
//	GraphicManager::Draw(this->body);
//
//#ifdef _DEBUG
//	GraphicManager::Draw(this->hitBox);
//	GraphicManager::Draw(this->origin);
//#endif
//};
//void Execute(const float& pElapsedTime)
//{
//	if(this->invecTimer > 0.f)
//	{
//		this->invecTimer -= pElapsedTime;
//	}
//};
//
//void InCollision(Entity* _other, const sf::Vector2f& intersection)
//{
//	sf::Vector2f distance(
//		_other->GetPosition().x - this->GetPosition().x,
//		_other->GetPosition().y - this->GetPosition().y
//	);
//
//	if (intersection.y >= intersection.x)
//	{
//		if (distance.y > 0.f)
//			this->MovePosition(0.f, (intersection.y));
//		else
//			this->MovePosition(0.f, -(intersection.y));
//	}
//	else
//	{
//		if (distance.x > 0.f)
//			this->MovePosition(intersection.x, 0.f);
//		else
//			this->MovePosition(-(intersection.x), 0.f);
//	}
//};
//void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType)
//{
//	sf::FloatRect bounds(this->GetBounds());
//	sf::Vector2f offSet(0.f, 0.f);
//
//	if (bounds.left < ofBounds.left)
//		offSet.x += ofBounds.left - bounds.left;
//	else if(bounds.width > ofBounds.width)
//		offSet.x += ofBounds.width - bounds.width;
//
//	if (colType == CollisionType::MapColl)
//	{
//		if (bounds.top < ofBounds.top)
//			offSet.y += ofBounds.top - bounds.top;
//		else if (bounds.height > ofBounds.height)
//			offSet.y += ofBounds.height - bounds.height;
//	}
//
//	this->MovePosition(offSet);
//};