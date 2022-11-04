#include "event_manager.h"
using namespace Manager;



EventManager*		EventManager::eventInstance	= nullptr;
sf::RenderWindow*	EventManager::pWindow		= nullptr;

EventManager* EventManager::GetEventInstance()
{
	if(eventInstance == nullptr)
	{
		eventInstance = new EventManager();
		if (eventInstance == nullptr)
		{
			std::cerr << "Nao foi possivel cria um gerenciador de eventos." << std::endl;
			return nullptr;
		}
	}

	return eventInstance;
};
void EventManager::DesconstructEventInstance()
{
	if (eventInstance != nullptr)
		delete eventInstance;
};

EventManager::EventManager()
{
	pWindow = &GraphicManager::GetWindow();
};
EventManager::~EventManager()
{};

