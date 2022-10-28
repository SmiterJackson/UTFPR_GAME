#pragma once

#include "stdafx.h"

const enum PrintPriority
{
	UNDEFINED = 0,
	BACKGROUND,
	OBSTACLE,
	CHARACTER,
	PROJECTILE,
	INTERFACE,
	BUTTON
};

namespace Trait
{
	class BasePrintable 
	{
	public:
		BasePrintable(const unsigned short int printPriority = PrintPriority::UNDEFINED);
		virtual ~BasePrintable();

		const unsigned short int const GetPrintPriorityValue() { return this->printPriority; };

		virtual void SelfPrint(sf::RenderWindow& context_window, const float& pElapsedTime) = 0;

		bool operator<(BasePrintable& other)
		{
			return this->printPriority < other.printPriority;
		};
		bool operator<=(BasePrintable& other)
		{
			return this->printPriority <= other.printPriority;
		};
		bool operator>(BasePrintable& other)
		{
			return this->printPriority > other.printPriority;
		};
		bool operator>=(BasePrintable& other)
		{
			return this->printPriority >= other.printPriority;
		};

	protected:
		const unsigned short int printPriority;
	};
}