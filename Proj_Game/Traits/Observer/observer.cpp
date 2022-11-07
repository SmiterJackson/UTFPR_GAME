#include "observer.h"
using namespace Manager;
using namespace Trait;

EventManager::InputSubject* Observer::pInputSubject = EventManager::InputSubject::GetInstance();

Observer::Observer(const unsigned long long int& _idRef):
	idRef(_idRef)
{
	if (pInputSubject != nullptr)
		pInputSubject->AttachObeserver(this);
};
Observer::~Observer()
{
	if(pInputSubject != nullptr)
		pInputSubject->DetachObeserver(this->idRef);
};