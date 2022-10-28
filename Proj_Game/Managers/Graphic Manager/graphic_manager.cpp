#include "graphic_manager.h"
using namespace Manager;
using namespace Trait;

GraphicManager* GraphicManager::pGraphManagerInstance = nullptr;
std::list<BasePrintable*> GraphicManager::entes = std::list<BasePrintable*>();
sf::RenderWindow* GraphicManager::context_window = nullptr;

GraphicManager::GraphicManager()
{};
GraphicManager::~GraphicManager()
{};

void GraphicManager::AddEnte(BasePrintable* ente)
{
	std::list<BasePrintable*>::const_iterator cIt;

	if (ente != nullptr)
	{
		for (cIt = entes.cbegin(); cIt != entes.cend(); cIt++)
		{
			if(*ente >= (**cIt))
			{
				entes.emplace(cIt, ente);
				break;
			}
		};
		entes.sort();
	}
};
void GraphicManager::RemoveEnte(const unsigned int enteId)
{
	std::list<BasePrintable*>::const_iterator cIt;
	Ente* aux = nullptr;

	for (cIt = entes.cbegin(); cIt != entes.cend(); cIt++)
	{
		aux = static_cast<Ente*>(*cIt);

		if()
		{
			entes.erase(cIt);
			break;
		}
	};
};
void GraphicManager::Draw(const float& pElapsedTime)
{
	std::list<BasePrintable*>::const_iterator cIt;

	context_window->clear();
	for (cIt = entes.cbegin(); cIt != entes.cend(); cIt++)
	{
		(*cIt)->SelfPrint(*context_window, pElapsedTime);
	}
};