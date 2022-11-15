#pragma once

#include "../Interface/interface.h"
#include "../Traits/Observer/observer.h"
#include "../Entes/Characters/Player/player.h"
#include "../Entes/Obstacles/mossRoad/mossRoad.h"
#include "../Managers/ColisionManager/colision_manager.h"
#include "../../Parallax/parallax.h"

namespace GUI
{
	class Stage : public GUI::Interface, public Trait::Observer
	{
	public:
		Stage();
		Stage(const sf::FloatRect bounds, const std::string& stagePath,
			  const std::vector<std::string>& BackgroundPaths, const float size_coefficient);
		~Stage();

		const sf::FloatRect GetBounds() const { return this->worldBounds; };

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
		sf::FloatRect worldBounds;

		Manager::ColisionManager* colision_manager;
		Parallax background;

		Lista<Entity*> entities;
	};
}