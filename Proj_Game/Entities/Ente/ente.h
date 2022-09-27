#pragma once

#include "../../stdafx.h"

class Ente
{
public:
	Ente();
	Ente(const unsigned int _type, float* pElapsedTime);
	~Ente();

	virtual void Execute() = 0;
	virtual void SelfPrint(sf::RenderWindow& context_window);

	void SetElapsedTimeRef(float* pElapsedTime) { this->elapsedTime = pElapsedTime; };
	unsigned long long int const GetId() const { return this->id; };
	unsigned int const GetType() const { return this->type; };

	enum Type { UNDEFINED = 0, STAGE, BACKGROUND, OBSTACLE, PROJECTILE, CHARACTER, ENEMY, MENU, CAMERA };
	
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
	float* elapsedTime;

private:
	static unsigned long long int counter;
};