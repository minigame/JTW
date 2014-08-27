#ifndef __PHYCONST_H__
#define __PHYCONST_H__

#include "cocos2d.h"
/* 定义与物理属性相关的常数 */

// 各类物体的碰撞bitflag

// 这里加入新物体的类型bitmask，新增的都直接按照规律加一个
#define PLAYER_CATEGORYBITMASK  (1u << 1) 
#define NPC_CATEGORYBITMASK     (1u << 2) 
#define GROUND_CATEGORYBITMASK  (1u << 3) 
#define ITEM_CATEGORYBITMASK    (1u << 4) 
#define STONE_CATEGORYBITMASK   (1u << 5) 
#define ELEVATOR_CATEGORYBITMASK (1u << 6) 
#define DEATH_CATEGORYBITMASK   (1u << 7)
#define ATTACT_REGION_CATEGORYBITMASK (1u << 8)


//下面加入contact和conllision的bitmask

//例如：
//这里Player设定成和Ground&Stone碰撞时会调用回调函数，也就是碰撞监听器所指回掉函数
#define PLATER_CONTACTTESTBITMASK (GROUND_CATEGORYBITMASK | STONE_CATEGORYBITMASK | ELEVATOR_CATEGORYBITMASK) 

//这里是Player设定成河Ground物理上是碰撞的
#define PLAYER_COLLISIONBITMASK   (GROUND_CATEGORYBITMASK | ELEVATOR_CATEGORYBITMASK) 

#define  ELEVATOR_CONTACTTESTBITMASK (PLAYER_CATEGORYBITMASK)
#define  ELEVATOR_COLLISIONBITMASK (PLAYER_CATEGORYBITMASK)


#define GROUND_CONTACTTESTBITMASK (PLAYER_CATEGORYBITMASK | ITEM_CATEGORYBITMASK)
#define GROUND_COLLISIONBITMASK   (PLAYER_CATEGORYBITMASK | NPC_CATEGORYBITMASK\
                                   | GROUND_CATEGORYBITMASK | STONE_CATEGORYBITMASK)

#define NPC_CONTACTTESTBITMASK    (ITEM_CATEGORYBITMASK | ATTACT_REGION_CATEGORYBITMASK) 
#define NPC_COLLISIONBITMASK      (GROUND_CATEGORYBITMASK | ELEVATOR_CATEGORYBITMASK) 

#define ITEM_CONTACTTESTBITMASK    (GROUND_CATEGORYBITMASK | NPC_CATEGORYBITMASK)
#define ITEM_COLLISIONBITMASK      (0)

#define ATTACT_REGION_CONTACTTESTBITMASK (NPC_CATEGORYBITMASK)
#define ATTACT_REGION_COLLISIONBITMASK (0)

#define STONE_CONTACTTESTBITMASK    (PLAYER_CATEGORYBITMASK)
#define STONE_COLLISIONBITMASK      (GROUND_CATEGORYBITMASK)

#define DEATH_CONTACTTESTBITMASK  (0x00000000)
#define DEATH_COLLISIONBITMASK    (0x00000000)

#define ALL_CATEGORYBITMASK       (0xffffffff)
#define ALL_CONTACTTESTBITMASK    (0xffffffff)
#define ALL_COLLISIONBITMASK      (0xffffffff)

const cocos2d::PhysicsMaterial MY_PHYSICSBODY_MATERIAL_DEFAULT(0.0f, 0.0f, 0.0f);
const cocos2d::PhysicsMaterial MY_PHYSICSBODY_MATERIAL_FRICTION(0.0f, 0.0f, 100.0f);


/* 定义各类子弹的飞行速度 */
#define MONKEY_BO_BULLET_SPEED  (800)
#define FORT_BULLET_SPEED       (600)


#define AUDIO_BRIDGE           "audio/bridge.ogg"
#define AUDIO_BULLET           "audio/bullet.ogg"
#define AUDIO_BUTTON_CLICK           "audio/button_click.ogg"
#define AUDIO_CHANGE_CHARACTER           "audio/change_character.ogg"
#define AUDIO_GAME_OVER          "audio/game_over.ogg"
#define AUDIO_GATE         "audio/gate.ogg"
#define AUDIO_JUMP         "audio/jump.ogg"
#define AUDIO_LOGO         "audio/logo.ogg"
#define AUDIO_MONKEY_2ND_JUMP         "audio/monkey_2nd_jump.ogg"
#define AUDIO_MONKEY_FIGHT         "audio/monkey_fight.ogg"
#define AUDIO_PIG_FIGHT          "audio/pig_fight.ogg"
#define AUDIO_PIG_PUSH          "audio/pig_push.ogg"
#define AUDIO_STONE          "audio/stone.ogg"
#define AUDIO_SUCCESS          "audio/success.ogg"



#endif