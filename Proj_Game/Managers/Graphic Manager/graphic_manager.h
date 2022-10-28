#pragma once

#include "../Traits/BasePrintable/basePrintable.h"
#include "../Entes/Ente/ente.h"

namespace Manager
{
	class GraphicManager
	{
	public:
		static void SetWindowReference() {};
		static void AddEnte(Trait::BasePrintable* ente);
		static void RemoveEnte(const unsigned int enteId);

		static void Draw(const float& pElapsedTime);

	private:
		GraphicManager();
		~GraphicManager();

	private:
		static GraphicManager* pGraphManagerInstance;

		static std::list<Trait::BasePrintable*> entes;
		static sf::RenderWindow* context_window;
	};
}