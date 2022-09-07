#pragma once

#include "../Character/character.h"

namespace Characters
{
	class Player : public Character
	{
	public:
		Player();
		~Player();

		void PlayerInputHandler(const sf::Event& _event);
		void Execute(const float elapsedTime);
		void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime);
		void Collided(const int type, const sf::Vector2f& movement);

		static unsigned int const GetNumberOfPlayers() { return playerCounter; };

	private:
		bool onGround;
		bool crouching;
		bool jump;
		bool walkLeft;
		bool walkRight;

		bool walking;
		bool done;

		unsigned int playerId;
		static unsigned int playerCounter;
	};
}