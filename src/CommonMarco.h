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

const int MAX_MAP = 4;
const int MAX_BACKROLLLAYER = 4;
const int MAX_BACKROLLSPLIT = 99;
const int MAP_SIZE[MAX_MAP][MAX_BACKROLLLAYER] = { { 17, 18, 1, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

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

#define CC_CALLBACK_4(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

#define DEFAULT_ATTACK_MAX_COUNT 1

#define PIG_ATTACK_BEGIN_FRAME_EVENT_NAME "Attack_Begin"
#define PIG_ATTACK_END_FRAME_EVENT_NAME "Attack_End"
#define PIG_ATTACK_MAX_COUNT 3

#define A2B 4
#define TOO_SMALL_FLOAT 0.001f
#define MONSTER_AI_SHOOT_DISTANCE 500.0f

enum ROLE {NONE, Monkey, Pig, Puffer, Monster_1, Monster_2};   //猴子，猪，河豚

//生物的各种状态
enum STATUS 
{
	NONESTATUS = 0,
	NoAnyAction = 1, 
	LeftWalk = 2, 
	RightWalk = 4, 
	Jump = 8, 
	Die = 16, 
	Attack = 32, 
	Fly = 64, 
	Push = 128,
	AttackAnimation = 256,
	Hurt = 512,
	ContinueAttack = 1024
};

enum DIR {Left, Right};   //该Creature的方向


#endif // CommonMarco_h__
