#pragma once

#include "../../stdafx.h"

class Ente
{
public:
	Ente();
	Ente(const unsigned int _type, float* elapsed_timeRef);
	~Ente();

	virtual void Execute() = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window) = 0;

	void SetElapsedTimeRef(float* elapsed_timeRef) { this->elapsed_time = elapsed_timeRef; };
	unsigned int const GetId() const { return this->id; };
	unsigned int const GetType() const { return this->type; };

	enum Type { UNDEFINED = 0, CAMERA, BACKGROUND, OBSTACLE, PROJECTILE, CHARACTER, ENEMY, MENU };

protected:
	const unsigned int id;
	const unsigned int type;
	float* elapsed_time;

private:
	static unsigned int counter;
};