#ifndef CommonMarco_h__
#define CommonMarco_h__
/********************************************************************
	created:	2014/08/20
	created:	20:8:2014   20:08
	file base:	CommonMarco
	file ext:	h
	author:		leozzyzheng
	
	purpose:	包含一般宏定义和枚举，方便全局调用
*********************************************************************/


#define WALK_TAG "run"
#define JUMP_TAG "jump"
#define DIE_TAG  "die"
#define NOANYACTION_TAG "noaction"
#define FLY_TAG "noaction"
#define ATTACK_TAG "fight"
#define MONKEY_TAG "monkey"
#define PIG_TAG "pig"
#define PUFFER_TAG	"puffer"

enum ROLE {Monkey, Pig, Puffer};   //猴子，猪，河豚
enum STATUS {NoAnyAction, LeftWalk, RightWalk, Jump, Die, Attack, Fly};    //没有任何动作状态，走的状态，跳跃的状态，死亡的状态
enum DIR {Left, Right, NoMoveLeft, NoMoveRight};   //该Creature的方向


#endif // CommonMarco_h__
