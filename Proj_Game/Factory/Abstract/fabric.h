#pragma once

namespace Factory
{
	template<class T>
	class Fabric
	{
	public:
		virtual T* Create() = 0;
	};
}