#pragma once

#include "stdafx.h"

const enum Type
{
	CHARACTER = 0,
	ENEMY,
	PROJECTILE,
	OBSTACLE,
	STAGE,
	CAMERA,
	MOUSE,
	BACKGROUND,
	INTERFACE,
	BUTTON,
	UNDEFINED
};

//Classe base para todas as intâncias do jogo, para cada qual ter definido seu 'executar'
class Ente
{
public:
	Ente(const unsigned int _type = UNDEFINED);
	virtual ~Ente();

	unsigned long long int const GetId() const { return this->id; };
	unsigned int const GetType() const { return this->type; };

	virtual void Execute(const float& pElapsedTime) = 0;

	bool operator== (const Ente& other)
	{
		return this->type == other.type;
	};
	bool operator!= (const Ente& other)
	{
		return this->type != other.type;
	};
	bool operator> (const Ente& other)
	{
		return this->type > other.type;
	};
	bool operator>= (const Ente& other)
	{
		return this->type >= other.type;
	};
	bool operator< (const Ente& other)
	{
		return this->type < other.type;
	};
	bool operator<= (const Ente& other)
	{
		return this->type <= other.type;
	};

protected:
	const unsigned long long int id;
	const unsigned short int type;

private:
	static unsigned long long int counter;
};