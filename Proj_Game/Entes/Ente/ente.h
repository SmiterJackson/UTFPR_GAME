#pragma once

#include "stdafx.h"

const enum PrintPriority
{
	undefined = 0,
	background,
	obstacles,
	characters,
	projectiles,
	interfaces,
	buttons
};
const enum Type
{
	PLAYER = 0, 
	ENEMY,
	PROJECTILE,
	OBSTACLE,
	STAGE,
	MOUSE,
	BACKGROUND,
	INTERFACE,
	BUTTON,
	UNDEFINED
};

/*
Classe base para todas as intâncias do jogo, para cada qual
ter definido seu 'executar', e 'desenhar-se'.
*/
class Ente
{
public:
	Ente(const unsigned short int _type = Type::UNDEFINED,
		 const unsigned short int _printPriority = PrintPriority::undefined);
	virtual ~Ente();

	const unsigned long long int GetId() const { return this->id; };
	const unsigned short int GetType() const { return this->type; };
	const unsigned short int GetPrintPriority() const { return this->printPriority; };

	virtual void SelfPrint(const float& pElapsedTime) = 0;
	virtual void Execute(const float& pElapsedTime) = 0;

	virtual bool operator> (const Ente& other)
	{
		return this->type > other.type;
	};
	virtual bool operator< (const Ente& other)
	{
		return this->type < other.type;
	};
	virtual bool operator!= (const Ente& other)
	{
		return this->id != other.id;
	};

protected:
	const unsigned long long int id;
	const unsigned short int type;
	const unsigned short int printPriority;

private:
	static unsigned long long int counter;
};