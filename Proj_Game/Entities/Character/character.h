#pragma once

#include "../Entity/entity.h"
#include "../../Traits/Animated/animated.h"

namespace Characters
{
	class Character : public Entity, public Animated
	{
	public:
		Character();
		Character(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef = "",
			const std::vector<std::pair<int, Animation>> _animations = std::vector<std::pair<int, Animation>>(), 
			const sf::IntRect sheetCut = sf::IntRect(), const unsigned int _lifeAmount = 0, float invcFramDuration = 0.f);
		Character(const unsigned int _type, const sf::RectangleShape& _hitBox, float* elapsed_timeRef, const std::string textureRef = "",
			const std::list<std::pair<int, Animation>> _animations = std::list<std::pair<int, Animation>>(),
			const sf::IntRect sheetCut = sf::IntRect(), const unsigned int _lifeAmount = 0, float invcFramDuration = 0.f);
		~Character();

		virtual void Execute() = 0;
		virtual void SelfPrint(sf::RenderWindow& context_window) = 0;
		virtual void Collided(const int type, const sf::Vector2f& movement) = 0;

	protected:
		bool invencible;

		float invcFrames;
		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical

		unsigned int life_counter;
	};
}