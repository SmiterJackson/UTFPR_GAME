#pragma once

#include "../Character/character.h"

class Camera;
class Stage;

namespace Characters
{
	class Player : public Character
	{
	public:
		Player();
		Player(float* elapsed_timeRef);
		~Player();

		void Execute();
		void Collided(Ente* _other);
		void SelfPrint(sf::RenderWindow& context_window);

		void PlayerInputHandler(const sf::Event& _event);
		void Initialize();

		static unsigned int const GetNumberOfPlayers() { return playerCounter; };

		enum Actions { IDLE = 0, WALKING, KICK, DAMAGED, CROUCHING };

	private:
		void ObstacleCollision(Entity* Obstacle) override;
		void CameraCollision(Camera* camera);
		void StageCollision(Stage* stage);

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