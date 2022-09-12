#pragma once

#include "../Instance/instance.h"

class Ente : public Instance
{
public:
	Ente();
	Ente(const unsigned int _type, float* elapsed_timeRef);
	~Ente();

	virtual void Execute() = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window) = 0;

	void SetElapsedTimeRef(float* elapsed_timeRef);

protected:
	float* elapsed_time;
};