#pragma once

#include "../../stdafx.h"

class Instance
{
public:
	Instance();
	Instance(const unsigned int _type);
	~Instance();

	virtual void Execute() = 0;

	unsigned int const GetId() const { return this->id; };
	unsigned int const GetType() const { return this->type; };

	enum Type { UNDEFINED = 0, CAMERA, BACKGROUND, OBSTACLE, PROJECTILE, CHARACTER, ENEMY, MENU };

protected:
	const unsigned int id;
	const unsigned int type;

private:
	static unsigned int counter;
};