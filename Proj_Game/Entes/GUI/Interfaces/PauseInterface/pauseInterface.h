#pragma once

#include "../Traits/Observer/observer.h"
#include "../Interface/interface.h"

namespace GUI
{
	class Stage;

	enum Text
	{
		VOLTAR = 0,
		INCLUIR,
		EXCLUIR,
		MENU,
		NO_TEXT
	};
	typedef std::unordered_map<std::string, Text> StringToValue;

	class PauseInterface : public Interface, public Trait::Observer
	{
	public:
		PauseInterface();
		PauseInterface(Stage* _pStage);
		~PauseInterface();

		void SelfPrint(const float& pElapsedTime);
		void UpdateObsever(const sf::Event& _event);
		void Execute(const float& pElapsedTime);

	private:
		void VerifyButtons();

	private:
		static StringToValue stringToValue;

		sf::RectangleShape background;
		std::vector<Button> buttons;
		Stage* pStage;
	};
}