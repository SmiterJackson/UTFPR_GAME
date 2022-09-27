#include "ente.h"

unsigned long long int Ente::counter = 0;

Ente::Ente() :
	id(counter++), type(Type::UNDEFINED), elapsedTime(nullptr)
{};
Ente::Ente(const unsigned int _type, float* pElapsedTime) :
	id(counter++), type(_type), elapsedTime(pElapsedTime)
{};
Ente::~Ente()
{};

void Ente::SelfPrint(sf::RenderWindow& context_window)
{};