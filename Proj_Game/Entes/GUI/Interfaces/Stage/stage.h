#pragma once

#include "../Interface/interface.h"
#include "../Traits/Observer/observer.h"
#include "../Entes/Characters/Player/player.h"
#include "../Entes/Obstacles/staticTile/staticTile.h"
#include "../Managers/ColisionManager/colision_manager.h"
#include "../Entes/Characters/Enemies/EnemyMelee/enemyMelee.h"
#include "../Entes/Characters/Enemies/EnemyRanged/enemyRanged.h"
#include "../../Parallax/parallax.h"
#include "../List/entitiesLista.h"

namespace GUI
{
	class Stage : public GUI::Interface, public Trait::Observer
	{
	public:
		Stage();
		Stage(const sf::Vector2u worldSize_grid, const std::vector<std::string>& BackgroundPaths, const float proportion = 1.f);
		~Stage();

		static const std::vector<std::vector<bool>>& GetGridStatus() { return worldGrid; };

		static void SetWorldSize(const sf::Vector2f worldSize) { return world.setSize(worldSize); };
		static const sf::Vector2f GetWorldSize() { return world.getSize() * world.getScale().x; };
		static const sf::Vector2f GetWorldPosition() { return world.getPosition(); };
		static const sf::FloatRect GetWorldBounds()
		{
			sf::Vector2f size(Stage::GetWorldSize() / 2.f);

			sf::FloatRect bounds(
				-size.x, -size.y,
				size.x, size.y
			);

			return bounds;
		};

		virtual void Initalize() = 0;
		void VerifyGridOcupation();

		void UpdateObsever(const sf::Event& _event);
		void SelfPrint();
		void Execute();

		void AddPlayer();
		void RemovePlayer();

	protected:
		void EntityCreated(Entity* pEntity);

	protected:
		static sf::RectangleShape world;
		static std::vector<std::vector<bool>> worldGrid;

		Manager::ColisionManager* colision_manager;
		Parallax background;

		EntitiesLista entities;

	#ifdef _DEBUG
		typedef std::vector<std::vector<std::pair<sf::RectangleShape, sf::Text>>> GridBlocks;

		static void printGrid(sf::IntRect bounds);
		static GridBlocks worldGridBlocks;
	#endif
	};
}