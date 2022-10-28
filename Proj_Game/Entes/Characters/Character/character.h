#pragma once

#include "../../Entity/entity.h"
#include "../../../Traits/Animated/animated.h"
#include "../../../Traits/Printable/printable.h"

namespace Characters
{
	class Character : public Entity, public Trait::Printable, public Trait::Animated
	{
	public:
		Character();
		Character(const unsigned int _type, const sf::RectangleShape& _hitBox, const std::string textureRef = "",
				  const sf::IntRect sheetCut = sf::IntRect(), const AnimationSheet _animations = AnimationSheet(),
				  const unsigned int _lifeAmount = 0, const float invcFramDuration = 0.f, const float size_proportion = 1.0f);
		virtual ~Character();

		const unsigned int const GetLifeCount() { return this->life_counter; };

		void MovePosition(const sf::Vector2f _newPosition) 
		{ 
			this->hitBox.move(_newPosition);
			this->SetTexturePosition(this->hitBox.getPosition());
		};
		void MovePosition(const float X_axis, const float Y_axis) 
		{
			this->hitBox.move(X_axis, Y_axis); 
			this->SetTexturePosition(this->hitBox.getPosition());
		};

		void SetProportion(const float proportion) 
		{
			this->hitBox.setScale(proportion, proportion);
			this->SetTextureProportion(proportion);
		};

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime) = 0;
		virtual void Execute(const float& pElapsedTime) = 0;

	protected:
		bool invencible;

		float invcFrames;
		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical

		unsigned int life_counter;
	};
}