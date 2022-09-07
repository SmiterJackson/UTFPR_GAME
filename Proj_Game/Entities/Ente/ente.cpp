#include "ente.h"

unsigned int Ente::counter = 0;

Ente::Ente():
	id(counter++), type(EnteType::UNDEFINED)
{}
Ente::Ente(const unsigned int _type):
	id(counter++), type(_type)
{}
Ente::~Ente()
{}