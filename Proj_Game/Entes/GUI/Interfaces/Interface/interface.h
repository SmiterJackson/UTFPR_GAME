#pragma once

#include "../../Button/button.h"

namespace GUI
{
	class Interface : public Ente
	{
	public:
		Interface(const unsigned short int GameStateType = 0ULL, Interface* _previousGState = nullptr);
		virtual ~Interface();

		const bool FullOverlay() const { return this->fullOverlay; };

		virtual void SelfPrint();
		virtual void Execute() = 0;

	protected:
		void PrintPreviousInterface();

	protected:
		const bool fullOverlay;
		Interface* previousGState;
	};
}