#include "projectile.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Projectiles;
using namespace Characters;
using namespace Manager;

Projectile::Projectile():
	Entity(
		Type::PROJECTILE, PrintPriority::projectiles, sf::Vector2f(0.f,0.f),
		sf::Vector2f(0.f, 0.f), std::string(""), sf::IntRect(0,0,0,0)
	),
	origin(nullptr), speedH(0.f)
{};
Projectile::Projectile(Character* _charOrigin, const sf::Vector2f _size, const sf::Vector2f _position, const float arrowSpeed,
					   const std::string path, const sf::IntRect sheetCut, const float size_coeff):
	Entity(
		Type::PROJECTILE, PrintPriority::projectiles, _size, 
		_position, path, sheetCut, false, size_coeff
	),
	origin(_charOrigin), speedH(arrowSpeed)
{};
Projectile::~Projectile()
{};

void Projectile::SelfPrint(const float& pElapsedTime)
{
	GraphicManager::Draw(this->body);

#ifdef _DEBUG
	GraphicManager::Draw(this->hitBox);
	GraphicManager::Draw(this->originCircle);
#endif
};