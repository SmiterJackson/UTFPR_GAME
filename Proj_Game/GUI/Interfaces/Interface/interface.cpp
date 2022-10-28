#include "interface.h"

GUI::Interface::Interface(short int* _pGameState):
	Ente(Ente::Type::INTERFACE, nullptr), pGameState(_pGameState)
{};
GUI::Interface::~Interface()
{};