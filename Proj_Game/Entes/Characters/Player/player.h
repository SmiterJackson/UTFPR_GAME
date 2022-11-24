#pragma once

#include "../Character/character.h"
#include "../Traits/Observer/observer.h"

/*
Classe que herda 'personagem' e 'observador', onde define-se o jogador de tal maneira em que
é um objeto interagível bem como aceita entrada de comandos para definir seus parâmetros.
*/
namespace Characters
{
	class Player : public Character, public Trait::Observer
	{
	private:
		enum Actions
		{
			IDLE = 0,
			IDLE_CROUCH,
			WALK,
			WALK_CROUCH,
			ATTACK,
			ATTACK_CROUCH,
			JUMP,
			FALL,
			DAMAGED,
			DIED
		};
		enum ActionMap
		{
			WALK_LEFT = 0,
			WALK_RIGHT,
			JUMPED,
			CROUCH
		};
		typedef std::map<sf::Keyboard::Key, ActionMap> keyToAction;

	public:
		Player();
		~Player();

		static std::list<Player*>& GetPlayerList() { return playerList; };
		static const unsigned int GetNumberOfPlayers() { return playerList.size(); };

		void UpdateObsever(const sf::Event& _event);
		void SelfPrint();
		void Execute();
		void Attack();
		void Collided(Entity* _other, const sf::Vector2f& intersection, CollisionType colType);

	protected:
		void Move();
		void Died();
		const sf::Vector2f EntityCollision(const Entity* other, const sf::Vector2f& intersection);

		static keyToAction GetKeyMap(unsigned int size);

	private:
		static std::vector<std::pair<int, Animation>> playersAnimations;
		static std::list<Player*> playerList;

		keyToAction keyToActions;

		bool shorter;
		bool onGround;
		bool crouching;
		bool jump;
		bool walkLeft;
		bool walkRight;
	};
}