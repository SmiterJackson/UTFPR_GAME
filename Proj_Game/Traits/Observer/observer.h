#pragma once

#include "../Managers/EventManager/event_manager.h"

namespace Trait
{
	class Observer
	{
	public:
		Observer(const unsigned long long int& _idRef);
		virtual ~Observer();

		const unsigned long long int GetIdRef() const { return this->idRef; };

		virtual void UpdateObsever(const sf::Event& _event) = 0;

	protected:
		static Manager::EventManager::InputSubject* pInputSubject;

		const unsigned long long int idRef;
	};
}