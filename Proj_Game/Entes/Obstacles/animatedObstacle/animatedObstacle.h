#pragma once

#include "../obstacle/obstacle.h"
#include "../../../Traits/Animated/animated.h"

namespace Obstacles
{
	class AnimObstacle : public Obstacle, public Trait::Animated
	{
	public:
		AnimObstacle();
		AnimObstacle(const sf::Vector2f _size, const sf::Vector2f _position, const std::string path,
					 const AnimationSheet _animations, const float size_coeff = 1.0f,
					 const bool isStatic = true, const bool repeated = false);
		~AnimObstacle();

		virtual void SelfPrint(const float& pElapsedTime);
	};
}