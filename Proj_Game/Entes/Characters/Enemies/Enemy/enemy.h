#pragma once

#include "../../Player/player.h"

namespace Enemies
{
	typedef std::vector<Characters::Player*> PlayerVec;
	class Enemy : public Characters::Character
	{
	public:
		Enemy();
		~Enemy();

	protected:
		static PlayerVec players;
	};
}