#include "ente.h"

unsigned int Ente::counter = 0;

Ente::Ente() :
	id(counter++), type(Type::UNDEFINED), elapsed_time(nullptr)
{};
Ente::Ente(const unsigned int _type, float* elapsed_timeRef) :
	id(counter++), type(_type), elapsed_time(elapsed_timeRef)
{};
Ente::~Ente()
{};