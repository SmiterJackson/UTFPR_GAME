#pragma once

#include "../obstacle/obstacle.h"
#include "../../../Traits/Animated/animated.h"

namespace Obstacles
{
	class AnimObstacle : public Obstacle, public Trait::Animated
	{
	public:
		AnimObstacle();
		AnimObstacle(const sf::RectangleShape& _hitBox, const std::string textureRef,
					 const AnimationSheet _animations, const float size_proportion = 1.0f,
					 const bool repeated = false);
		~AnimObstacle();

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
	};
}