#pragma once

#include "../Interface/interface.h"
#include "../Traits/Observer/observer.h"
#include "../Entes/Obstacles/Road/road.h"
#include "../Entes/Characters/Player/player.h"
#include "../Managers/ColisionManager/colision_manager.h"
#include "../../Parallax/parallax.h"

namespace GUI
{
	class Stage : public GUI::Interface, public Trait::Observer
	{
	public:
		Stage();
		Stage(const sf::Vector2f worldSize, const std::vector<std::string>& BackgroundPaths, const float proportion = 1.f);
		~Stage();

		static const sf::Vector2f GetWorldSize() { return world.getSize() * world.getScale().x; };
		static void SetWorldSize(const sf::Vector2f worldSize) { return world.setSize(worldSize); };
		static const sf::FloatRect GetWorldBounds()
		{
			sf::Vector2f size(Stage::GetWorldSize() / 2.f);

			sf::FloatRect bounds(
				-size.x, -size.y,
				size.x, size.y
			);

			return bounds;
		};

		virtual void Initalize(const float size_coefficient);
		void UpdateObsever(const sf::Event& _event);

		void SelfPrint(const float& pElapsedTime);
		void Execute(const float& pElapsedTime);

		void AddEntity(Entity* entity);
		void AddRange(std::list<Entity*>* _entities);
		void RemoveEntity(const unsigned long long int entityId);
		void RemoveRange(const std::vector<unsigned long long int> entityId);

		void AddPlayer();
		void RemovePlayer();

	protected:
		static sf::RectangleShape world;

		Manager::ColisionManager* colision_manager;
		Parallax background;

		Lista<Entity*> entities;
	};
}