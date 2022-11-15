#pragma once

#include "fabric.h"

namespace Factory
{
	template<class T>
	class GeneralizedFabric : public Fabric<T>
	{
	public:
		virtual T* Create() { return new T(); };
	};
}