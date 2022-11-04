#pragma once

#include "../Interface/interface.h"

class Stage;

namespace GUI 
{
	enum Text
	{
		VOLTAR = 0,
		INCLUIR,
		EXCLUIR,
		MENU
	};

	typedef std::map<unsigned short int, std::string> IntToText;
	typedef std::unordered_map<std::string, void(*)()> StringToFunc;

	class PauseInterface : public Interface
	{
	public:
		PauseInterface();
		PauseInterface(Stage* _pStage);
		~PauseInterface();

		void SelfPrint(const float& pElapsedTime);
		void InputHandle(const sf::Event& _event);
		void Execute(const float& pElapsedTime);

	private:
		void VerifyButtons();

		static void ChangeGameState();
		static void AddPlayer();
		static void RemovePlayer();
		static void ReturnToMainMenu();

	private:
		static const IntToText buttonsTxt;
		static StringToFunc funcMap;
		static Stage* pStage;

		sf::RectangleShape background;
		std::vector<Button> buttons;
	};
}