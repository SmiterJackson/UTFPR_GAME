#pragma once

#include "../Character/character.h"

namespace Manager
{
	class GraphicManager;
}

namespace Characters
{
	class Player : public Character
	{
	public:
		Player(float size_proportion = 1.0f);
		~Player();

		static const std::list<Player*>& GetPlayerList() { return playerList; };
		static const unsigned int GetNumberOfPlayers() { return playerList.size(); };

		const unsigned int GetPlayerId() const { return this->playerId; };
		
		void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
		void Execute(const float& pElapsedTime);
		void InputHandle(const sf::Event& _event);

		enum Actions { IDLE = 0, WALKING, KICK, DAMAGED, CROUCHING };

	private:
		static std::list<Player*> playerList;

		bool onGround;
		bool crouching;
		bool jump;
		bool walkLeft;
		bool walkRight;

		bool walking;
		bool done;

		unsigned int playerId;
	};
}