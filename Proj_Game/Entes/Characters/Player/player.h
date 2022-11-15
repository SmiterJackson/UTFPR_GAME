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
	public:
		enum Actions
		{
			IDLE = 0,
			WALKING,
			KICK,
			DAMAGED,
			CROUCHING
		};
		enum ActionMap
		{
			WALK_LEFT = 0,
			WALK_RIGHT,
			JUMP,
			CROUCH
		};
		typedef std::map<sf::Keyboard::Key, ActionMap> keyToAction;

	public:
		Player();
		~Player();

		static const std::list<Player*>& GetPlayerList() { return playerList; };
		static const unsigned int GetNumberOfPlayers() { return playerList.size(); };

		void UpdateObsever(const sf::Event& _event);
		void SelfPrint(const float& pElapsedTime);
		void Execute(const float& pElapsedTime);

	protected:
		void InCollision(Entity* _other, const sf::Vector2f& intersection);
		void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType);

		static keyToAction GetKeyMap(unsigned int size);

	private:
		static std::vector<std::pair<int, Animation>> playersAnimations;
		static std::list<Player*> playerList;

		keyToAction keyToActions;

		bool onGround;
		bool crouching;
		bool jump;
		bool walkLeft;
		bool walkRight;
	};
}