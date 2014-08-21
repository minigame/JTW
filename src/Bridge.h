#pragma once
#include "Gear.h"
#include "Tag.h"
class Bridge :
	public Gear
{
public:
	Bridge(void);
	~Bridge(void);

	void initBridgeWithName(char* name);
};

