#include "NPC.h"
#include "PhyConst.h"

NPC::NPC()
{
}


NPC::~NPC()
{
}

std::string NPC::getStatusTag(STATUS s)
{
	switch (s)
	{
	case NONESTATUS:
		break;
	case NoAnyAction:
		break;
	case LeftWalk:
		break;
	case RightWalk:
		break;
	case Jump:
		break;
	case Die:
		break;
	case Attack:
		break;
	case Fly:
		break;
	case PUSH:
		break;
	case AttackAnimation:
		break;
	case Hurt:
		break;
	default:
		break;
	}

	return "";
}
