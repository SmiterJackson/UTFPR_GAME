#pragma once

#include "../../../Entities/Camera/camera.h"
#include "../../Button/button.h"

namespace GUI
{
	class Interface : public Ente
	{
	public:
		Interface(short int* _pGameState = nullptr);
		virtual ~Interface();

		virtual void Execute() = 0;
		
		void SetGameStateReference(short int* _pGameState) { this->pGameState = _pGameState; };

	protected:
		short int* pGameState;
	};
}