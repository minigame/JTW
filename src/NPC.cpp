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
	//目前没有任何其他的动作，只有一个动画文件
	switch (s)
	{
	case NONESTATUS:
		return "";
		break;
	default:
		return WALK_TAG;
		break;
	}
}

void NPC::init(ROLE r)
{
	CCASSERT(r == Monster_1 || r == Monster_2, "you cannot use NPC to create non-npc creatrue!");

	Creature::init(r);
	changeDir(Right);
}

void NPC::deadCompleted()
{
	Node* sprite = getPhyBody()->getNode();
	Node* layer = sprite->getParent();
	layer->removeChild(sprite);
}
