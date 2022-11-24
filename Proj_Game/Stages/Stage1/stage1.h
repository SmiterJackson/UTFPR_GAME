#pragma once

#include "../Entes/GUI/Interfaces/Stage/stage.h"

namespace Stages
{
	class Stage1 : public GUI::Stage
	{
	public:
		Stage1();
		~Stage1();

		void Initalize();

	private:
		static const std::vector<std::string> backgroundPaths;
	};
}