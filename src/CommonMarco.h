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
#define FLY_TAG "jump"
#define ATTACK_TAG "fight"
#define MONKEY_TAG "monkey"
#define PIG_TAG "pig"
#define PUFFER_TAG	"puffer"
#define PUSH_TAG "push"
#define MONSTER1_TAG "monster1"
#define MONSTER2_TAG "monster2"

enum ROLE {NONE, Monkey, Pig, Puffer, Monster_1, Monster_2};   //猴子，猪，河豚

//生物的各种状态
enum STATUS 
{
	NoAnyAction = 1, 
	LeftWalk = 2, 
	RightWalk = 4, 
	Jump = 8, 
	Die = 16, 
	Attack = 32, 
	Fly = 64, 
	PUSH = 128,
	AttackAnimation = 256,
	Hurt = 512
};

enum DIR {Left, Right, NoMoveLeft, NoMoveRight};   //该Creature的方向


#endif // CommonMarco_h__
