#pragma once

#include "../../Entities/Ente/ente.h"

class GraphicManager 
{
public:
	GraphicManager();
	GraphicManager(sf::RenderWindow* windowRef, const std::list<Ente*>& _entes = std::list<Ente*>());
	~GraphicManager();

	void AddEnte(Ente* ente);
	void RemoveEnte(const unsigned int enteId);
	void Draw(const float elapsedTime);

private:
	std::list<Ente*> entes;
	sf::RenderWindow* windowRef;
};