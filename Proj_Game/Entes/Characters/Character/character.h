#pragma once

#include "../Entes/Entity/entity.h"
#include "../Traits/Animated/animated.h"

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
		Character(const unsigned short int _type, const sf::Vector2f _size, const sf::Vector2f _position, const std::string path, 
				  const AnimationSheet _animations = AnimationSheet(), const unsigned int _lifeAmount = 0U, const float invcDuration = 0.f,
				  const float deathTime = 1.f, const bool isStatic = true, const float proportion = 1.0f);
		virtual ~Character();

		void SetSpeedCoeff(const float _coeff) { this->speedCoeff = _coeff; };

		const unsigned int GetLifeCount() const { return this->life_counter; };
		void Damaged() 
		{
			if(this->life_counter > 0 && this->invecTimer <= 0.f)
			{
				this->life_counter--;
				this->invecTimer = this->invcFrames;
			}
		};

		virtual void SelfPrint() = 0;
		virtual void Attack() = 0;
		virtual void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType) = 0;

	protected:
		virtual void Move();
		virtual void Died() = 0;

	protected:
		const float invcFrames; // Tempo de invencibilidade quando recebe dano

		float speedH; // Velocidade horizontal
		float speedV; // Velocidade vertical
		float speedCoeff;

		float invecTimer;
		float deathTimer;
		float damagedTimer;
		unsigned int life_counter;
	};
}