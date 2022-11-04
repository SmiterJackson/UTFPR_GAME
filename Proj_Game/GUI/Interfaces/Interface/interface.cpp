#include "interface.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace GUI;

Interface::Interface(const unsigned short int GameStateType, Interface* _previousGState) :
	Ente(GameStateType, PrintPriority::interfaces),
	GameState(_previousGState == nullptr ? true : false),
	previousGState(_previousGState)
{};
Interface::~Interface()
{};

void Interface::SelfPrint(const float& pElapsedTime)
{
	this->PrintPreviousInterface(pElapsedTime);
	//this->PrintPreviousInterface(context_window, pElapsedTime);
};
void Interface::PrintPreviousInterface(const float& pElapsedTime)
{
	if(this->previousGState != nullptr)
		this->previousGState->SelfPrint(pElapsedTime);
		//this->previousGState->SelfPrint(context_window, pElapsedTime);
};