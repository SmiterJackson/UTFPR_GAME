#include "baseProjectile.h"
using namespace Projectiles;
using namespace Characters;

BaseProjectile::BaseProjectile(Character* charOrigin, const sf::Vector2f _size, const sf::Vector2f _position,
							   const std::string path, const sf::IntRect sheetCut, const float size_coeff):
	Entity(Type::PROJECTILE, PrintPriority::projectiles, _size, _position, true, size_coeff),
	PrintableBody(path, sheetCut, size_coeff),
	charOrigin(charOrigin), collided(false), speed(0.f)
{};
BaseProjectile::~BaseProjectile()
{};

void BaseProjectile::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	context_window.draw(this->body);
#ifdef _DEBUG
	context_window.draw(this->hitBox);
	context_window.draw(this->origin);
#endif
};
void BaseProjectile::Execute(const float& pElapsedTime)
{
	this->MovePosition(sf::Vector2f(this->speed * pElapsedTime, 0));
};

void BaseProjectile::InCollision(Entity* _other, const sf::Vector2f& intersection)
{
	unsigned short int type = _other->GetType();

	if((type == Type::ENEMY  || type == Type::PLAYER) && type != this->charOrigin->GetType())
		//static_cast<Characters::Character*>(_other)->;

	this->collided = true;
};
void BaseProjectile::OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType)
{
	this->collided = true;
};