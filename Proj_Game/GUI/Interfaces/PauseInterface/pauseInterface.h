#pragma once

#include "../Entities/StageClass/stage.h"
#include "../Interface/interface.h"
#include "../game/game.h"

namespace GUI 
{
	class PauseInterface : public Interface
	{
	public:
		PauseInterface(float* _pElapsedTime = nullptr, short int* _pGameState = nullptr, Camera* _pCamera = nullptr, Mouse* pMouse = nullptr,
					   Stage* _pStage = nullptr, std::vector<Ente*>* _pStateEnte = nullptr, const std::string fontPath = "");
		~PauseInterface();

		void Execute();
		void SelfPrint(sf::RenderWindow& context_window);
		void InputHandle(const sf::Event& _event);

	private:
		void VerifyButtons();
		void ButtonActive(std::vector<Button>::iterator buttonIt);

	private:
		sf::RectangleShape background;
		std::vector<Button> buttons;

		Stage* pStage;
		std::vector<Ente*>* pStateEnte;

		float acummulator;
	};
}