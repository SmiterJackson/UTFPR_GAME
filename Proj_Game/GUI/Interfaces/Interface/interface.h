#pragma once

#include "../Traits/GameState/gameState.h"
#include "../../Button/button.h"

namespace GUI
{
	class Interface : public Ente, public Trait::GameState
	{
	public:
		Interface(const unsigned short int GameStateType = 0ULL, Interface* _previousGState = nullptr);
		virtual ~Interface();

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
		virtual void InputHandle(const sf::Event& _event) = 0;
		virtual void Execute(const float& pElapsedTime) = 0;

	protected:
		void PrintPreviousInterface(sf::RenderWindow& context_window, const float& pElapsedTime);

	protected:
		Interface* previousGState;
	};
}