#pragma once

#include "../Entity/entity.h"
#include "../../Traits/Animated/animated.h"

namespace Characters
{
	class Character : public Entity, public Animated
	{
	public:
		Character();
		Character(const unsigned int _type, float* pElapsedTime, const sf::RectangleShape& _hitBox, const std::string textureRef = "",
				  const sf::IntRect sheetCut = sf::IntRect(), const AnimationSheet _animations = AnimationSheet(),
				  const unsigned int _lifeAmount = 0, float invcFramDuration = 0.f, float _size_coeff = 1.0f);
		~Character();

		virtual void Execute() = 0;
		virtual void Collided(Ente* _other) = 0;

	protected:
		bool invencible;

		float invcFrames;
		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical

		unsigned int life_counter;
	};
}