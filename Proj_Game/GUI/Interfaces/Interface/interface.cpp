#include "interface.h"

GUI::Interface::Interface(const unsigned short int GameStateType, Interface* _previousGState) :
	Ente(GameStateType, Manager::PrintPriority::interfaces),
	GameState(_previousGState == nullptr ? true : false),
	previousGState(_previousGState)
{};
GUI::Interface::~Interface()
{};

void GUI::Interface::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	this->PrintPreviousInterface(context_window, pElapsedTime);
};
void GUI::Interface::PrintPreviousInterface(sf::RenderWindow& context_window, const float& pElapsedTime)
{
	if(this->previousGState != nullptr)
		this->previousGState->SelfPrint(context_window, pElapsedTime);
};