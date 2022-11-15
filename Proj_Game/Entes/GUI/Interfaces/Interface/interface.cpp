#include "interface.h"
#include "../Managers/GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace GUI;

Interface::Interface(const unsigned short int GameStateType, Interface* _previousGState) :
	Ente(GameStateType, PrintPriority::interfaces),
	fullOverlay(_previousGState == nullptr ? false : true), 
	previousGState(_previousGState)
{};
Interface::~Interface()
{};

void Interface::SelfPrint(const float& pElapsedTime)
{
	this->PrintPreviousInterface(pElapsedTime);
};
void Interface::PrintPreviousInterface(const float& pElapsedTime)
{
	if(this->previousGState != nullptr)
		this->previousGState->SelfPrint(pElapsedTime);
};