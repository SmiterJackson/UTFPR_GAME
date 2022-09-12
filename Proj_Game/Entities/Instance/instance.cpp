#include "instance.h"

unsigned int Instance::counter = 0;

Instance::Instance(): 
	id(counter++), type(Instance::UNDEFINED)
{};
Instance::Instance(const unsigned int _type): 
	id(counter++), type(_type)
{};
Instance::~Instance()
{};