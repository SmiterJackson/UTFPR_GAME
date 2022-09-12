#include "ente.h"

Ente::Ente():
	Instance(), elapsed_time(nullptr)
{}
Ente::Ente(const unsigned int _type, float* elapsed_timeRef):
	Instance(_type), elapsed_time(elapsed_timeRef)
{}
Ente::~Ente()
{}

void Ente::SetElapsedTimeRef(float* elapsed_timeRef)
{
	if (elapsed_timeRef != nullptr)
		this->elapsed_time = elapsed_timeRef;
};