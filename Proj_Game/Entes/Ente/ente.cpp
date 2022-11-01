#include "ente.h"

unsigned long long int Ente::counter = 0;

Ente::Ente(const unsigned short int _type,
		   const unsigned short int printPriority) :
	id(counter++), type(_type), printPriority(printPriority)
{};
Ente::~Ente() 
{};

void Ente::SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime)
{};