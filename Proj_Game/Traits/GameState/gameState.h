#pragma once

#include "stdafx.h"

namespace Trait
{
	const enum GameStateType
	{
		MAIN_MENU = 0,
		IN_GAME,
		PAUSE_MENU,
		SUB_MENU
	};

	class GameState
	{
	public:
		GameState(const bool _fullOverlay = true);
		virtual ~GameState();

		const bool FullOverlay() const { return this->fullOverlay; };

		virtual void InputHandle(const sf::Event& _event) = 0;

	protected:
		const bool fullOverlay;
	};
}