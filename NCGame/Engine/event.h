#pragma once
#include "id.h"
#include "variant.h"

class Entity;

struct Event 
{
	ID eventID;
	Entity* sender;
	Entity* receiver;
	Variant variants[3];

	Event() {}
};