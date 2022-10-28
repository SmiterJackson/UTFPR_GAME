#pragma once

#include "../Character/character.h"

namespace Characters
{
	class Player : public Character
	{
	public:
		Player(float size_proportion = 1.0f);
		~Player();

		static unsigned int const GetNumberOfPlayers() { return playerCounter; };

		void Initialize();

		void InputHandle(const sf::Event& _event);
		void Execute(const float& pElapsedTime);
		void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);

		enum Actions { IDLE = 0, WALKING, KICK, DAMAGED, CROUCHING };

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