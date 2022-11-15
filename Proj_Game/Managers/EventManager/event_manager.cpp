#include "event_manager.h"
#include "../Traits/Observer/observer.h"
#include "../GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Trait;

EventManager::InputSubject* EventManager::InputSubject::instance	= nullptr;
bool						EventManager::InputSubject::stopWarning		= false;

EventManager::InputSubject* EventManager::InputSubject::GetInstance(std::list<Observer*>* _observers)
{
	if(instance == nullptr)
	{
		instance = new EventManager::InputSubject(_observers);
		if (instance == nullptr)
			std::cerr << "Nao foi possivel instanciar o InputSubject: event_manager." << std::endl;
	}

	return instance;
};
void EventManager::InputSubject::DeconstructInstance()
{
	if (instance != nullptr)
		delete instance;
};

EventManager::InputSubject::InputSubject(std::list<Observer*>* _observers):
	observers()
{
	if(_observers != nullptr)
	{
		observers = *_observers;
	}
};
EventManager::InputSubject::~InputSubject()
{};

void EventManager::InputSubject::AttachObeserver(Observer* pOberserver)
{
	if(pOberserver != nullptr)
		this->observers.emplace_back(pOberserver);
};
void EventManager::InputSubject::DetachObeserver(const unsigned long long int id)
{
	std::list<Observer*>::iterator it;

	for (it = this->observers.begin(); it != this->observers.end(); it++)
	{
		if ((*it)->GetIdRef() == id)
		{
			this->observers.erase(it);
			break;
		}
	}
};
void EventManager::InputSubject::AttachObeserverRange(std::list<Observer*>& _observers)
{
	std::list<Trait::Observer*>::iterator cIt;

	for (cIt = _observers.begin(); cIt != _observers.end(); cIt++)
	{
		if (*cIt != nullptr)
			this->observers.emplace_back(*cIt);
	}
};
void EventManager::InputSubject::DetachObeserverRange(const std::list<unsigned long long int>& ids)
{
	std::list<unsigned long long int>::const_iterator cIt;
	std::list<Observer*>::iterator it;

	for (cIt = ids.cbegin(); cIt != ids.cend(); cIt++)
	{
		for (it = this->observers.begin(); it != this->observers.end(); it++)
		{
			if ((*it)->GetIdRef() == (*cIt))
			{
				this->observers.erase(it);
				break;
			}
		}
	}
};

void EventManager::InputSubject::WarnObservers(const sf::Event& inputEvent)
{
	std::list<Trait::Observer*>::iterator it;

	for(it = this->observers.begin(); it != this->observers.end() && !stopWarning; it++)
		(*it)->UpdateObsever(inputEvent);

	if (stopWarning)
		EventManager::InputSubject::InvertStopWarning();
};

EventManager*		EventManager::instance	= nullptr;
sf::RenderWindow*	EventManager::pWindow		= nullptr;

EventManager* EventManager::GetInstance()
{
	if(instance == nullptr)
	{
		instance = new EventManager();
		if (instance == nullptr)
			std::cerr << "Nao foi possivel cria um gerenciador de eventos." << std::endl;
	}

	return instance;
};
void EventManager::DeconstructInstance()
{
	if (instance != nullptr)
		delete instance;
};

EventManager::EventManager():
	pInputSubject(InputSubject::GetInstance())
{
	pWindow = &GraphicManager::GetWindow();
};
EventManager::~EventManager()
{};

void EventManager::Update()
{
	sf::Event event;
	while(pWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			GraphicManager::CloseWindow();
			break;
		case sf::Event::Resized:
			GraphicManager::GetInstance()->WindowResize();
			break;
		default:
			this->pInputSubject->WarnObservers(event);
			break;
		}
	};
};