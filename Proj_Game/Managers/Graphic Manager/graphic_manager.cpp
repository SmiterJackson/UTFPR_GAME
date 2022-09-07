#include "graphic_manager.h"

GraphicManager::GraphicManager():
	entes(), windowRef(nullptr)
{
	if (windowRef == nullptr)
	{
		std::cerr << "Nao foi possivel obter referencia para a janela de contexto: Graphic Manager." << std::endl;
		this->~GraphicManager();
	}
};
GraphicManager::GraphicManager(sf::RenderWindow* windowRef, const std::list<Ente*>& _entes) :
	entes(), windowRef(windowRef)
{
	std::list<Ente*>::const_iterator cIt;
	if (windowRef == nullptr)
	{
		std::cerr << "Nao foi possivel obter referencia para a janela de contexto: Graphic Manager." << std::endl;
		this->~GraphicManager();
	}

	for (cIt = _entes.cbegin(); cIt != _entes.cend(); cIt++)
	{
		entes.emplace_back(*cIt);
	};
	entes.sort();
};
GraphicManager::~GraphicManager()
{};

void GraphicManager::AddEnte(Ente* ente)
{
	std::list<Ente*>::const_iterator cIt;

	for (cIt = entes.cbegin(); cIt != entes.cend(); cIt++)
	{
		if ((*cIt)->GetType() >= ente->GetType())
		{
			entes.emplace(cIt, ente);
			break;
		}
	};
};
void GraphicManager::RemoveEnte(const unsigned int enteId)
{
	std::list<Ente*>::const_iterator cIt;

	for (cIt = entes.cbegin(); cIt != entes.cend(); cIt++)
	{
		if ((*cIt)->GetId() == enteId)
		{
			entes.erase(cIt);
			break;
		}
	};
};
void GraphicManager::Draw(const float elapsedTime)
{
	std::list<Ente*>::const_iterator cIt;

	windowRef->clear();
	for (cIt = entes.cbegin(); cIt != entes.cend(); cIt++)
	{
		(*cIt)->SelfPrint(*windowRef, elapsedTime);
	}
};