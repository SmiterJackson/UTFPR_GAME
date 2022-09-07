#pragma once

#include "../../stdafx.h"

class Ente
{
public:
	Ente();
	Ente(const unsigned int _type);
	~Ente();

	virtual void Execute(const float elapsedTime) = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window, const float elapsedTime) = 0;

	unsigned int const GetId() const { return this->id; };
	unsigned int const GetType() const { return this->type; };

	enum EnteType { UNDEFINED = 0, CAMERA, BACKGROUND, OBSTACLE, PROJECTILE, CHARACTER, ENEMY, MENU };

protected:
	const unsigned int id;
	const unsigned int type;

private:
	static unsigned int counter;
};