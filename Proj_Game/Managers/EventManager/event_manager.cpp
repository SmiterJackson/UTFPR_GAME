#include "event_manager.h"
#include "../Traits/Observer/observer.h"
#include "../GraphicManager/graphic_manager.h"
using namespace Manager;
using namespace Trait;

EventManager::InputSubject* EventManager::InputSubject::inpSubInstance	= nullptr;
bool						EventManager::InputSubject::stopWarning		= false;

EventManager::InputSubject* EventManager::InputSubject::GetInstance(std::list<Observer*>* _observers)
{
	if(inpSubInstance == nullptr)
	{
		inpSubInstance = new EventManager::InputSubject(_observers);
		if (inpSubInstance == nullptr)
			std::cerr << "Nao foi possivel instanciar o InputSubject: event_manager." << std::endl;
	}

	return inpSubInstance;
};
void EventManager::InputSubject::DeconstructInstance()
{
	if (inpSubInstance != nullptr)
		delete inpSubInstance;
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

EventManager*		EventManager::eventInstance	= nullptr;
sf::RenderWindow*	EventManager::pWindow		= nullptr;

EventManager* EventManager::GetInstance()
{
	if(eventInstance == nullptr)
	{
		eventInstance = new EventManager();
		if (eventInstance == nullptr)
			std::cerr << "Nao foi possivel cria um gerenciador de eventos." << std::endl;
	}

	return eventInstance;
};
void EventManager::DeconstructInstance()
{
	if (eventInstance != nullptr)
		delete eventInstance;
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