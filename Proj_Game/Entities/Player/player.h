#pragma once

#include "../Character/character.h"

namespace Characters
{
	class Player : public Character
	{
	public:
		Player();
		Player(float* elapsed_timeRef);
		~Player();

		void PlayerInputHandler(const sf::Event& _event);
		void Initialize();
		void Execute();
		void SelfPrint(sf::RenderWindow& context_window);
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