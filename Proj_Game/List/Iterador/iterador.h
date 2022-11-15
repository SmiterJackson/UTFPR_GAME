#pragma once

#include "stdafx.h"

template<typename T>
class AbstractIterator
{
public:
	AbstractIterator() :
		listPosition(0)
	{};
	~AbstractIterator()
	{};

	unsigned int& ListPosition() { return this->listPosition; };

	virtual void Next() = 0;
	virtual void Previous() = 0;
	virtual bool IsDone() = 0;
	virtual T& Current() = 0;

protected:
	unsigned long long int listPosition;
};