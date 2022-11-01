#pragma once

#include "../Entes/Entity/entity.h"
#include "../Traits/Animated/animated.h"
#include "../Traits/PrintableBody/printableBody.h"

/*
Classe characters que herda caracter�sticas de ser interag�vel bem como
tem um corpo para ser desenhavel e animado.
*/
namespace Characters
{
	class Character : public Entity, public Trait::PrintableBody, public Trait::Animated
	{
	public:
		Character();
		Character(const unsigned short int _type, const sf::Vector2f _size, const sf::Vector2f _position, 
				  const std::string path = "", const AnimationSheet _animations = AnimationSheet(),
				  const unsigned int _lifeAmount = 0, const float invcFramDuration = 0.f, const bool isStatic = true, 
				  const float size_coeff = 1.0f);
		virtual ~Character();

		const unsigned int GetLifeCount() const { return this->life_counter; };

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

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);

	protected:
		bool invencible;

		float invcFrames;
		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical

		unsigned int life_counter;
	};
}