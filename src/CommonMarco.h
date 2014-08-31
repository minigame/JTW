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

extern int MAP_ID;
const int MAX_MAP = 4;
const int MAX_BACKROLLLAYER = 4;
const int MAX_BACKROLLSPLIT = 99;
const int MAP_SIZE[MAX_MAP][MAX_BACKROLLLAYER] = { { 10, 5, 1, 0 }, { 1, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };

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

#define MONKEY_BODY_WIDTH 55.0f
#define PIG_BODY_WIDTH 115.0f

#define CC_CALLBACK_4(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

#define DEFAULT_ATTACK_MAX_COUNT 1

#define PIG_ATTACK_BEGIN_FRAME_EVENT_NAME "Attack_Begin"
#define PIG_ATTACK_END_FRAME_EVENT_NAME "Attack_End"
#define PIG_ATTACK_MAX_COUNT 3

#define A2B 4
#define TOO_SMALL_FLOAT 0.001
#define MONSTER_AI_SHOOT_DISTANCE 500.0f
#define DEATH_DISTANCE	50.0f

#define UI_ICON_SCALE_SMALL 0.618

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

#if defined(WIN32) or defined(__OSX__)
#define AUDIO_BRIDGE			"audio/wav/bridge.wav"
#define AUDIO_BULLET			"audio/wav/bullet.wav"
#define AUDIO_BUTTON_CLICK		"audio/wav/button_click.wav"
#define AUDIO_CHANGE_CHARACTER	"audio/wav/change_character.wav"
#define AUDIO_GAME_OVER			"audio/wav/game_over.wav"
#define AUDIO_GATE				"audio/wav/gate.wav"
#define AUDIO_JUMP				"audio/wav/jump.wav"
#define AUDIO_LOGO				"audio/wav/logo.wav"
#define AUDIO_MONKEY_2ND_JUMP   "audio/wav/monkey_2nd_jump.wav"
#define AUDIO_MONKEY_FIGHT      "audio/wav/monkey_fight.wav"
#define AUDIO_PIG_FIGHT_LIGHT   "audio/wav/pig_fight_light.wav"
#define AUDIO_PIG_FIGHT_HEAVY   "audio/wav/pig_fight_heavy.wav"
#define AUDIO_PIG_PUSH          "audio/wav/pig_push.wav"
#define AUDIO_STONE				"audio/wav/stone.wav"
#define AUDIO_SUCCESS			"audio/wav/success.wav"
#define AUDIO_BACK_MISSION_1	"audio/wav/mission_1_MIX.wav"
#define AUDIO_BACK_MISSION_2	"audio/wav/mission_2_MIX.wav"
#define AUDIO_BACK_TITLE		"audio/wav/title_MIX.wav"
#else
#define AUDIO_BRIDGE			"audio/ogg/bridge.ogg"
#define AUDIO_BULLET			"audio/ogg/bullet.ogg"
#define AUDIO_BUTTON_CLICK		"audio/ogg/button_click.ogg"
#define AUDIO_CHANGE_CHARACTER	"audio/ogg/change_character.ogg"
#define AUDIO_GAME_OVER			"audio/ogg/game_over.ogg"
#define AUDIO_GATE				"audio/ogg/gate.ogg"
#define AUDIO_JUMP				"audio/ogg/jump.ogg"
#define AUDIO_LOGO				"audio/ogg/logo.ogg"
#define AUDIO_MONKEY_2ND_JUMP   "audio/ogg/monkey_2nd_jump.ogg"
#define AUDIO_MONKEY_FIGHT      "audio/ogg/monkey_fight.ogg"
#define AUDIO_PIG_FIGHT_LIGHT   "audio/ogg/pig_fight_light.ogg"
#define AUDIO_PIG_FIGHT_HEAVY   "audio/ogg/pig_fight_heavy.ogg"
#define AUDIO_PIG_PUSH          "audio/ogg/pig_push.ogg"
#define AUDIO_STONE				"audio/ogg/stone.ogg"
#define AUDIO_SUCCESS			"audio/ogg/success.ogg"
#define AUDIO_BACK_MISSION_1	"audio/ogg/mission_1_MIX.ogg"
#define AUDIO_BACK_MISSION_2	"audio/ogg/mission_2_MIX.ogg"
#define AUDIO_BACK_TITLE		"audio/ogg/title_MIX.ogg"
#endif





#endif // CommonMarco_h__
