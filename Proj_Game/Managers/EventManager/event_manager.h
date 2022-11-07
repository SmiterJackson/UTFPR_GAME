#pragma once

#include "stdafx.h"

namespace Trait
{
	class Observer;
}

namespace Manager
{
	class EventManager
	{
	public:
		class InputSubject
		{
		public:
			static InputSubject* GetInstance(std::list<Trait::Observer*>* _observers = nullptr);
			static void DeconstructInstance();

			static void InvertStopWarning() { stopWarning = !stopWarning; };

			void AttachObeserver(Trait::Observer* pOberserver);
			void DetachObeserver(const unsigned long long int id);
			void AttachObeserverRange(std::list<Trait::Observer*>& _observers);
			void DetachObeserverRange(const std::list<unsigned long long int>& ids);

			void WarnObservers(const sf::Event& inputEvent);

		private:
			InputSubject(std::list<Trait::Observer*>* _observers = nullptr);
			~InputSubject();

		private:
			static InputSubject* inpSubInstance;
			static bool stopWarning;

			std::list<Trait::Observer*> observers;
		};

	public:
		static EventManager* GetInstance();
		static void DeconstructInstance();

		void Update();

	private:
		EventManager();
		~EventManager();

	private:
		static EventManager* eventInstance;
		static sf::RenderWindow* pWindow;

		InputSubject* pInputSubject;
	};
}