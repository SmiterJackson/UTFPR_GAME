#pragma once

#include "../Character/character.h"

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
		
		void Execute(const float& pElapsedTime);
		void InputHandle(const sf::Event& _event);

	protected:
		virtual void InCollision(Entity* _other, const sf::Vector2f& intersection);
		virtual void OfCollision(const sf::FloatRect& ofBounds, const unsigned short int colType);

	private:
		enum Actions { IDLE = 0, WALKING, KICK, DAMAGED, CROUCHING };

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