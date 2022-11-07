#pragma once

#include "../Traits/Observer/observer.h"
#include "../Characters/Player/player.h"
#include "../Entes/Obstacles/obstacle/obstacle.h"
#include "../GUI/Interfaces/Interface/interface.h"
#include "../Managers/ColisionManager/colision_manager.h"

class Stage : public GUI::Interface, public Trait::Observer
{
public:
	typedef std::pair<sf::Texture*, std::vector<sf::Sprite>> Layer;
	class Parallax : public Ente
	{
	public:
		Parallax(const std::vector<std::string>& paths = std::vector<std::string>(), const float _size_coeff = 1.f);
		~Parallax();

		void SetBackgrounds(const std::vector<std::string>& paths);
		void ResetBackground();

		const unsigned int GetBackgroundListSize() const { return this->backGrounds.size(); };

		void SetSizeCoefficient(float _size_coeff)
		{
			std::vector<Layer>::iterator it;
			size_t i = 0;
			this->size_coeff = _size_coeff;

			for (it = this->backGrounds.begin(); it != this->backGrounds.end(); it++)
				for (i = 0; i < it->second.size(); i++)
					it->second[i].setScale(_size_coeff, _size_coeff);
		};

		void SelfPrint(const float& pElapsedTime);
		void Execute(const float& pElapsedTime);

	private:
		std::vector<Layer> backGrounds;

		sf::Vector2f lastPosition;

		float layers_spd_coeff;
		float size_coeff;
	};

public:
	Stage();
	Stage(const sf::FloatRect bounds, const std::string& stagePath,
		  const std::vector<std::string>& BackgroundPaths, const float size_coefficient);
	~Stage();

	const sf::FloatRect GetBounds() const { return this->worldBounds; };

	void Initalize(const float size_coefficient);
	void UpdateObsever(const sf::Event& _event);

	void SelfPrint(const float& pElapsedTime);
	void Execute(const float& pElapsedTime);
	void ReadArchive(const std::string path);

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