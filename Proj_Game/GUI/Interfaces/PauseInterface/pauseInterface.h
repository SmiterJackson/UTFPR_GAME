#pragma once

#include "../Interface/interface.h"

class Game;
class Stage;

namespace GUI 
{
	class PauseInterface : public Interface
	{
	public:
		PauseInterface();
		PauseInterface(Mouse* _pMouse, Stage* _pStage);
		~PauseInterface();

		void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
		void InputHandle(const sf::Event& _event);
		void Execute(const float& pElapsedTime);

	private:
		void VerifyButtons();
		void ButtonActive(std::vector<Button>::iterator buttonIt);

	private:
		std::vector<Button> buttons;

		Stage* pStage;
	};
}