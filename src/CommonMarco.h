#ifndef CommonMarco_h__
#define CommonMarco_h__
/********************************************************************
	created:	2014/08/20
	created:	20:8:2014   20:08
	file base:	CommonMarco
	file ext:	h
	author:		leozzyzheng
	
	purpose:	����һ��궨���ö�٣�����ȫ�ֵ���
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

enum ROLE {Monkey, Pig, Puffer};   //���ӣ�������
enum STATUS {NoAnyAction, LeftWalk, RightWalk, Jump, Die, Attack, Fly};    //û���κζ���״̬���ߵ�״̬����Ծ��״̬��������״̬
enum DIR {Left, Right, NoMoveLeft, NoMoveRight};   //��Creature�ķ���


#endif // CommonMarco_h__
