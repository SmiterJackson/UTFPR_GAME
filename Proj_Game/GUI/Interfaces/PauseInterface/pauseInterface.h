#pragma once

#include "../Interface/interface.h"

class Stage;

namespace Manager
{
	class GraphicManager;
}

namespace GUI 
{
	class PauseInterface : public Interface
	{
	public:
		PauseInterface();
		PauseInterface(unsigned short int* _pGameState, Mouse* _pMouse, Stage* _pStage);
		~PauseInterface();

		void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime);
		void InputHandle(const sf::Event& _event);
		void Execute(const float& pElapsedTime);

	private:
		void VerifyButtons();
		void ButtonActive(std::vector<Button>::iterator buttonIt);

	private:
		std::vector<Button> buttons;

		unsigned short int* pGameState;
		Stage* pStage;
	};
}