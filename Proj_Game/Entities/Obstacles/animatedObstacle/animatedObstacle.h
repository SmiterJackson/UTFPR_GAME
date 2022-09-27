#pragma once

#include "../../Entity/entity.h"
#include "../../../Traits/Animated/animated.h"

namespace Obstacles
{
	class AnimatedObstacle : public Entity, public Animated
	{
	public:
		AnimatedObstacle();
		AnimatedObstacle(const unsigned int _type, float* elapsed_timeRef, const sf::RectangleShape& _hitBox, const AnimationSheet _animations,
			const std::string textureRef = "", const sf::IntRect sheetCut = sf::IntRect());
		~AnimatedObstacle();

		virtual void Execute();
		virtual void SelfPrint(sf::RenderWindow& context_window);
		virtual void Collided(Ente* _other);
	};
}