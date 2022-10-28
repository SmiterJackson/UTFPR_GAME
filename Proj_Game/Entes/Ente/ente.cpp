#include "ente.h"

unsigned long long int Ente::counter = 0;

Ente::Ente(const unsigned int _type) :
	id(counter++), type(_type)
{};
Ente::~Ente()
{};

void Ente::InputHandle(const sf::Event& _event)
{};