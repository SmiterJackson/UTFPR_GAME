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
	context_window.draw(this->hitBox);
	context_window.draw(this->origin);
#endif
};

void Characters::Character::InCollision(const Entity* _other, const sf::Vector2f& intersection)
{
	sf::Vector2f distance(
		_other->GetPosition().x - this->GetPosition().x,
		_other->GetPosition().y - this->GetPosition().y
	);

	if (intersection.y >= intersection.x)
	{
		if (distance.y > 0.f)
			this->MovePosition(0.f, (intersection.y));
		else
			this->MovePosition(0.f, -(intersection.y));
	}
	else
	{
		if (distance.x > 0.f)
			this->MovePosition(intersection.x, 0.f);
		else
			this->MovePosition(-(intersection.x), 0.f);
	}
};
void Characters::Character::OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType)
{
	sf::FloatRect bounds(this->GetBounds());
	sf::Vector2f offSet(0.f, 0.f);

	if (bounds.left < ofBounds.left)
		offSet.x += ofBounds.left - bounds.left;
	else if(bounds.width > ofBounds.width)
		offSet.x += ofBounds.width - bounds.width;

	if (colType == CollisionType::MapColl)
	{
		if (bounds.top < ofBounds.top)
			offSet.y += ofBounds.top - bounds.top;
		else if (bounds.height > ofBounds.height)
			offSet.y += ofBounds.height - bounds.height;
	}

	this->MovePosition(offSet);
};