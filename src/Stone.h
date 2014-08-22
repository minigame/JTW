#ifndef __STONE__H
#define __STONE__H 1

#include "Gear.h"

class PlayerSprite;

class Stone: public Gear
{
public:
    Stone();
    ~Stone();

public:
    static bool contactEdgeHandler(PlayerSprite  * player,   Stone * stone);
    static bool contactGroundHandler(PlayerSprite  * player, Stone * stone);
};

#endif
