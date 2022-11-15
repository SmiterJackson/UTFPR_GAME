#pragma once

#include "../Entes/Characters/Player/player.h"
#include "Abstract/generalizedFabric.h"

namespace Factory
{
	class PlayerFabric : public GeneralizedFabric<Characters::Player> {};
}