#pragma once

#include "../Entity/entity.h"

namespace Characters
{
	class Character : public Entity
	{
	public:
		Character();
		Character(const unsigned int _type, const sf::RectangleShape& _hitBox, const sf::IntRect sheetCut = sf::IntRect(), const std::string textureRef = "", 
			const unsigned int _lifeAmount = 0, float invcFramDuration = 0.f);
		~Character();

		virtual void Execute(const float elapsedTime) = 0;
		virtual void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime) = 0;
		virtual void Collided(const int type, const sf::Vector2f& movement) = 0;

	protected:
		bool invencible;

		float invcFrames;
		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical

		unsigned int life_counter;
	};
}