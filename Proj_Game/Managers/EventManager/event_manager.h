#pragma once

#include "../GraphicManager/graphic_manager.h"

namespace Manager
{
	class EventManager
	{
	public:
		static EventManager* GetEventInstance();
		static void DesconstructEventInstance();

	private:
		EventManager();
		~EventManager();


	private:
		static EventManager* eventInstance;
		static sf::RenderWindow* pWindow;


	};
}