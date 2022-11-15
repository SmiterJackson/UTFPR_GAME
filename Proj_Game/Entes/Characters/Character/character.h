#pragma once

#include "../Entes/Entity/entity.h"
#include "../Traits/Animated/animated.h"
#include "../Traits/PrintableBody/printableBody.h"

/*
Classe character que herda características para poder interagir com outras 
classes, bem como contém um corpo desenhavel e animado.
*/
namespace Characters
{
	class Character : public Entity, public Trait::Animated
	{
	public:
		Character();
		Character(const unsigned short int _type, const sf::Vector2f _size, const sf::Vector2f _position, const std::string path = "",
				  const AnimationSheet _animations = AnimationSheet(), const unsigned int _lifeAmount = 0, 
				  const float invcFramDuration = 0.f, const bool isStatic = true, const float size_coeff = 1.0f);
		virtual ~Character();

		void SetSpeedCoeff(const float _coeff) { this->speedCoeff = _coeff; };

		const unsigned int GetLifeCount() const { return this->life_counter; };
		void Damaged() 
		{
			this->life_counter--;
			this->invecTimer = this->invcFrames;
		};

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

		virtual void SelfPrint(const float& pElapsedTime) = 0;
		virtual void Execute(const float& pElapsedTime) = 0;

	protected:
		virtual void InCollision(Entity* _other, const sf::Vector2f& intersection) = 0;
		virtual void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType) = 0;

	protected:
		const float invcFrames; // Tempo de invencibilidade
		float invecTimer; // Acumulador para o tempo de invencibilidade

		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical
		float speedCoeff;

		unsigned int life_counter;
	};
}